#pragma once

#include <istream>

#include <fontio/logic/type2/Type2CharstringReader.hpp>
#include <fontio/model/cff/Cff.hpp>
#include <fontio/model/cff/CffDict.hpp>
#include <fontio/model/cff/CffPrivateDict.hpp>
#include <fontio/model/cff/CffType2Charstrings.hpp>

namespace fontio { namespace logic { namespace cff
{
    using namespace fontio::logic::type2;
    using namespace fontio::model;
    using namespace fontio::model::cff;

    class CffReader
    {
    public:

        Cff ReadCff(std::istream& stream)
        {
            auto header = this->ReadHeader(stream);

            auto nameIndex = this->ReadIndex(stream, header.GetHeaderSize());
            auto names = this->ReadNameIndex(stream, nameIndex);

            auto topDictIndex = this->ReadIndex(stream, nameIndex.GetOffsets().back());

            auto stringIndex = this->ReadIndex(stream, topDictIndex.GetOffsets().back());
            auto strings = this->ReadStringIndex(stream, stringIndex);

            auto topDicts = this->ReadTopDicts(stream, topDictIndex, strings);

            std::unique_ptr<ICffCharstrings> globalSubroutines;
            auto globalSubroutineIndex = this->ReadIndex(stream, stringIndex.GetOffsets().back());
            if (!globalSubroutineIndex.IsEmpty())
            {
                globalSubroutines = this->ReadCharstrings(stream, globalSubroutineIndex, CffCharstringFormat::Type2);
            }

            return Cff(header, names, std::move(topDicts), strings, std::move(globalSubroutines));
        }

    private:

        CffHeader ReadHeader(std::istream& stream)
        {
            auto versionMajor = this->ReadBigEndian<uint8_t>(stream);
            auto versionMinor = this->ReadBigEndian<uint8_t>(stream);
            auto headerSize = this->ReadBigEndian<uint8_t>(stream);
            auto offsetSize = this->ReadBigEndian<uint8_t>(stream);

            return CffHeader(versionMajor, versionMinor, headerSize, offsetSize);
        }

        CffIndex ReadIndex(std::istream& stream, size_t offset)
        {
            stream.seekg(offset, std::ios_base::beg);

            auto count = this->ReadBigEndian<uint16_t>(stream);

            if (count == 0)
            {
                return CffIndex();
            }

            auto offsetSize = this->ReadBigEndian<uint8_t>(stream);

            std::vector<uint32_t> offsets;
            for (size_t i = 0; i <= (size_t)count; i++)
            {
                auto offset = this->ReadBigEndian<uint32_t>(stream, offsetSize);
                offsets.push_back(offset);
            }

            auto currentPos = (uint32_t)stream.tellg();
            for (auto& offset : offsets)
            {
                offset += currentPos - 1;
            }

            return CffIndex(offsets);
        }

        CffNameIndex ReadNameIndex(std::istream& stream, const CffIndex& index)
        {
            std::vector<std::string> names;

            for (size_t i = 0; i < index.GetOffsets().size() - 1; i++)
            {
                auto nameStart = index.GetOffsets()[i];
                auto nameEnd = index.GetOffsets()[i + 1];
                auto nameLength = nameEnd - nameStart;

                auto nameData = std::vector<char>(nameLength, '0');

                stream.seekg(nameStart, std::ios_base::beg);
                stream.read(nameData.data(), nameLength);

                names.emplace_back(nameData.data(), nameData.size());
            }

            return CffNameIndex(names);
        }

        std::vector<CffTopDict> ReadTopDicts(std::istream& stream, const CffIndex& index, const CffStringIndex& strings)
        {
            std::vector<CffTopDict> result;

            for (size_t i = 0; i < index.GetOffsets().size() - 1; i++)
            {
                auto dictStart = index.GetOffsets()[i];
                auto dictEnd = index.GetOffsets()[i + 1];

                result.push_back(this->ReadTopDict(stream, dictStart, dictEnd - dictStart, strings));
            }

            return result;
        }

        std::string GetDictString(const CffDict& dict, CffOperatorType op, const CffStringIndex& strings, const std::string& defaultValue = "")
        {
            if (dict.HasOperator(op))
            {
                auto valueSid = dict.GetAsSid(op);
                return strings.GetString(valueSid);
            }

            return defaultValue;
        }

        CffTopDict ReadTopDict(std::istream& stream, uint32_t offset, uint32_t length, const CffStringIndex& strings)
        {
            auto dict = this->ReadDict(stream, offset, length);

            auto charstringsOffset = dict.GetAsUint(CffOperatorType::CharStrings);
            auto charstringsIndex = this->ReadIndex(stream, charstringsOffset);
            auto charstringsFormat = dict.GetAsEnum<CffCharstringFormat>(CffOperatorType::CharstringType, CffCharstringFormat::Type2);
            auto charstrings = this->ReadCharstrings(stream, charstringsIndex, charstringsFormat);

            auto privateOffsetLength = dict.GetAsOffsetAndLength(CffOperatorType::Private);
            auto privateDict = this->ReadPrivateDict(stream, privateOffsetLength.first, privateOffsetLength.second);

            std::unique_ptr<ICffCharstrings> localSubroutines;
            if (privateDict.GetSubrsOffset() > 0)
            {
                auto localSubroutineIndex = this->ReadIndex(stream, privateDict.GetSubrsOffset());
                localSubroutines = this->ReadGlobalSubroutines(stream, localSubroutineIndex);
            }

            auto charsetOffset = dict.GetAsUint(CffOperatorType::Charset, 0);
            auto charset = charstringsIndex.GetOffsets().size() > 0
                ? this->LoadCharset(charsetOffset, stream, charstringsIndex.GetOffsets().size() - 1)
                : std::unique_ptr<CffCharset>();

            auto version = this->GetDictString(dict, CffOperatorType::Version, strings);
            auto notice = this->GetDictString(dict, CffOperatorType::Notice, strings);
            auto copyright = this->GetDictString(dict, CffOperatorType::Copyright, strings);
            auto fullName = this->GetDictString(dict, CffOperatorType::FullName, strings);
            auto familyName = this->GetDictString(dict, CffOperatorType::FamilyName, strings);
            auto weight = this->GetDictString(dict, CffOperatorType::Weight, strings, "Regular");

            auto fontMatrix = CffFontMatrix(
                dict.GetAsArray<double, 6>(
                    CffOperatorType::FontMatrix,
                    std::array<double, 6>({0.001, 0.0, 0.0, 0.001, 0.0, 0.0})));

            auto boundBox = BoundBox(
                dict.GetAsArray<int32_t, 4>(
                    CffOperatorType::FontBBox,
                    std::array<int32_t, 4>({0, 0, 0, 0})));

            return CffTopDict(
                version,
                notice,
                copyright,
                fullName,
                familyName,
                weight,
                fontMatrix,
                boundBox,
                privateDict.GetDefaultWidthX(),
                privateDict.GetNominalWidthX(),
                std::move(charstrings),
                std::move(charset),
                std::move(localSubroutines));
        }

        CffPrivateDict ReadPrivateDict(std::istream& stream, uint32_t offset, uint32_t length)
        {
            auto dict = this->ReadDict(stream, offset, length);

            return CffPrivateDict(
                (dict.HasOperator(CffOperatorType::Subrs) ? dict.GetAsUint(CffOperatorType::Subrs) + offset : 0),
                dict.GetAsInt(CffOperatorType::DefaultWidthX, 0),
                dict.GetAsInt(CffOperatorType::NominalWidthX, 0));
        }

        CffDict ReadDict(std::istream& stream, uint32_t offset, uint32_t length)
        {
            std::unordered_map<CffOperatorType, std::vector<CffObject>> objects;

            stream.seekg(offset, std::ios_base::beg);

            std::vector<CffObject> operands;
            while ((uint32_t)stream.tellg() < offset + length)
            {
                auto object = this->ReadObject(stream);

                if (object.IsOperator())
                {
                    objects[object.GetOperator()] = operands;
                    operands.clear();
                }
                else
                {
                    operands.push_back(object);
                }
            }

            return CffDict(std::move(objects));
        }

        std::unique_ptr<ICffCharstrings> ReadCharstrings(
            std::istream& stream,
            const CffIndex& index,
            CffCharstringFormat format)
        {
            if (format == CffCharstringFormat::Type2)
            {
                Type2CharstringReader type2Reader;

                std::vector<Type2Charstring> charstrings;

                for (size_t i = 0; i < index.GetOffsets().size() - 1; i++)
                {
                    auto start = index.GetOffsets()[i];
                    auto end = index.GetOffsets()[i + 1];

                    stream.seekg(start, std::ios_base::beg);

//                    std::cout << "\n\n\n" << i << ": ";

                    charstrings.emplace_back(type2Reader.ReadType2Charstring(stream, end - start));
                }

                return std::unique_ptr<ICffCharstrings>(new CffType2Charstrings(std::move(charstrings)));
            }
            else
            {
                throw std::logic_error("Not implemented");
            }
        }

        std::unique_ptr<CffCharset> LoadCharset(uint32_t charsetOffset, std::istream& stream, size_t totalGlyphs)
        {
            if (charsetOffset > 3)
            {
                stream.seekg(charsetOffset, std::ios_base::beg);
                return this->LoadCharsetTable(stream, totalGlyphs);
            }

            return std::unique_ptr<CffCharset>();
        }

        std::unique_ptr<CffCharset> LoadCharsetTable(std::istream& stream, size_t totalGlyphs)
        {
            std::unordered_map<uint16_t, uint16_t> gidToSid;

            gidToSid[0] = 0;

            auto format = this->ReadBigEndian<uint8_t>(stream);

            if (format == 0)
            {
                throw std::logic_error("Not implemented");
            }
            else if (format == 1)
            {
                size_t gid = 1;
                while (gid < totalGlyphs)
                {
                    auto sid = this->ReadBigEndian<uint16_t>(stream);
                    auto rangeLen = this->ReadBigEndian<uint8_t>(stream);

                    for (size_t i = 0; i <= rangeLen; i++)
                    {
                        gidToSid[gid++] = sid++;
                    }
                }
            }
            else if (format == 2)
            {
                throw std::logic_error("Not implemented");
            }
            else
            {
                throw std::runtime_error("Unknown charset format");
            }

            return std::unique_ptr<CffCharset>(new CffCharset(gidToSid));
        }

        CffStringIndex ReadStringIndex(std::istream& stream, const CffIndex& index)
        {
            std::vector<std::string> strings;

            for (size_t i = 0; i < index.GetOffsets().size() - 1; i++)
            {
                auto nameStart = index.GetOffsets()[i];
                auto nameEnd = index.GetOffsets()[i + 1];
                auto nameLength = nameEnd - nameStart;

                auto nameData = std::vector<char>(nameLength, '0');

                stream.seekg(nameStart, std::ios_base::beg);
                stream.read(nameData.data(), nameLength);

                strings.emplace_back(nameData.data(), nameData.size());
            }

            return CffStringIndex(strings);
        }

        std::unique_ptr<ICffCharstrings> ReadGlobalSubroutines(std::istream& stream, const CffIndex& index)
        {
            throw std::logic_error("Not implemented");
        }

        CffObject ReadObject(std::istream& stream)
        {
            auto b0 = this->ReadBigEndian<uint8_t>(stream);

            if ((b0 < 12) || ((b0 > 12) && (b0 < 22)))
            {
                auto operatorType = (CffOperatorType)b0;
                return CffObject(operatorType);
            }
            else if (b0 == 12)
            {
                auto b1 = this->ReadBigEndian<uint8_t>(stream);
                auto operatorType = (CffOperatorType)(((uint16_t)b0 << 8) | b1);
                return CffObject(operatorType);
            }
            else if ((b0 >= 32) && (b0 <= 246))
            {
                auto number = (int32_t)b0 - 139;
                return CffObject(number);
            }
            else if ((b0 >= 247) && (b0 <= 250))
            {
                auto b1 = this->ReadBigEndian<uint8_t>(stream);
                auto number = ((int32_t)b0 - 247) * 256 + b1 + 108;
                return CffObject(number);
            }
            else if ((b0 >= 251) && (b0 <= 254))
            {
                auto b1 = this->ReadBigEndian<uint8_t>(stream);
                auto number = -((int32_t)b0 - 251) * 256 - b1 - 108;
                return CffObject(number);
            }
            else if (b0 == 28)
            {
                auto b1 = this->ReadBigEndian<uint8_t>(stream);
                auto b2 = this->ReadBigEndian<uint8_t>(stream);
                auto number = ((int32_t)b1 << 8) | b2;
                return CffObject(number);
            }
            else if (b0 == 29)
            {
                auto b1 = this->ReadBigEndian<uint8_t>(stream);
                auto b2 = this->ReadBigEndian<uint8_t>(stream);
                auto b3 = this->ReadBigEndian<uint8_t>(stream);
                auto b4 = this->ReadBigEndian<uint8_t>(stream);
                auto number =
                    ((int32_t)b1 << 24) |
                    ((int32_t)b2 << 16) |
                    ((int32_t)b3 << 8) |
                    ((int32_t)b4);
                return CffObject(number);
            }
            else
            {
                throw std::runtime_error("Unknown value format");
            }
        }

        template<typename T>
        T ReadBigEndian(std::istream& stream, size_t size = sizeof(T))
        {
            T result = 0;

            for (size_t i = 0; i < size; i++)
            {
                char byte;
                stream.read(&byte, 1);

                result = (result << 8) | ((uint8_t)byte);
            }

            return result;
        }
    };
} } }
