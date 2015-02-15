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

            stream.seekg(header.GetHeaderSize(), std::ios_base::beg);

            auto nameIndex = this->ReadIndex(stream);
            auto names = this->ReadNameIndex(stream, nameIndex);

            stream.seekg(nameIndex.GetOffsets().back());

            auto topDictIndex = this->ReadIndex(stream);
            auto topDicts = this->ReadTopDicts(stream, topDictIndex);

            stream.seekg(topDictIndex.GetOffsets().back());

            auto stringIndex = this->ReadIndex(stream);
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

        CffIndex ReadIndex(std::istream& stream)
        {
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
                    objects[object.GetOperator()] = std::move(operands);
                    operands.clear();
                }
                else
                {
                    operands.push_back(object);
                }
            }

            return CffTopDict(std::move(objects));
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
