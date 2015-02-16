#pragma once

#include <istream>

#include <fontio/model/cff/Cff.hpp>

namespace fontio { namespace logic { namespace cff
{
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
            auto topDicts = this->ReadTopDicts(stream, topDictIndex);

            auto stringIndex = this->ReadIndex(stream, topDictIndex.GetOffsets().back());
            auto strings = this->ReadStringIndex(stream, stringIndex);

            return Cff(header, names, std::move(topDicts), strings);
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
            auto offsetSize = this->ReadBigEndian<uint8_t>(stream);

            if (count == 0)
            {
                throw std::runtime_error("Index should have at least one offset");
            }

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

        std::vector<CffTopDict> ReadTopDicts(std::istream& stream, const CffIndex& index)
        {
            std::vector<CffTopDict> result;

            for (size_t i = 0; i < index.GetOffsets().size() - 1; i++)
            {
                auto dictStart = index.GetOffsets()[i];
                auto dictEnd = index.GetOffsets()[i + 1];

                result.push_back(this->ReadTopDict(stream, dictStart, dictEnd - dictStart));
            }

            return result;
        }

        CffTopDict ReadTopDict(std::istream& stream, uint32_t offset, uint32_t length)
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

            auto charstringsOffset = this->GetOffsetFromOperator(objects, CffOperatorType::CharStrings, false);
            auto charstringsIndex = this->ReadIndex(stream, charstringsOffset);

            auto charset = charstringsIndex.GetOffsets().size() > 0
                ? this->LoadCharset(objects, stream, charstringsIndex.GetOffsets().size() - 1)
                : std::unique_ptr<CffCharset>();

            return CffTopDict(std::move(objects), std::move(charset));
        }

        uint32_t GetOffsetFromOperator(
            const std::unordered_map<CffOperatorType, std::vector<CffObject>>& objects,
            CffOperatorType op,
            bool canDefaultToZero) const
        {
            auto pos = objects.find(op);
            if (pos == objects.end())
            {
                if (canDefaultToZero)
                {
                    return 0;
                }
                else
                {
                    throw std::runtime_error("Missing value for operator");
                }
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for offset operator: expected 1 integer.");
            }

            return (uint32_t)numbers[0].GetIntegerSafe();
        }

        std::unique_ptr<CffCharset> LoadCharset(
            const std::unordered_map<CffOperatorType, std::vector<CffObject>>& objects,
            std::istream& stream,
            size_t totalGlyphs)
        {
            auto charsetOffset = this->GetOffsetFromOperator(objects, CffOperatorType::Charset, true);
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

                    for (size_t i = 0; i < rangeLen; i++)
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
                auto number = -((int32_t)b0 - 247) * 256 - b1 - 108;
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
