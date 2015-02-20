#pragma once

#include <memory>
#include <vector>

#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model::type2;

    class Type2CharstringReader
    {
    private:

        int hintCount = 0;

    public:

        Type2Charstring ReadType2Charstring(std::istream& stream, uint32_t length)
        {
            std::vector<Type2Object> objects;

            this->Reset();

            auto stackDepth = 0;

            auto start = (uint32_t)stream.tellg();
            while (((uint32_t)stream.tellg() - start) < length)
            {
                auto object = this->ReadObject(stream);

                if (object.IsOperator())
                {
                    if ((object.GetOperator() == Type2OperatorType::HintMask) ||
                        (object.GetOperator() == Type2OperatorType::CntrMask))
                    {
                        this->ReadMask(stream, objects, object.GetArgCount());
                    }
                    else if ((object.GetOperator() == Type2OperatorType::HStem) ||
                        (object.GetOperator() == Type2OperatorType::VStem) ||
                        (object.GetOperator() == Type2OperatorType::HStemHM) ||
                        (object.GetOperator() == Type2OperatorType::VStemHM))
                    {
                        this->hintCount += stackDepth / 2;
                    }

                    stackDepth = 0;
                }
                else
                {
                    stackDepth++;
                }

                objects.push_back(object);
            }

            return Type2Charstring(std::move(objects));
        }

    private:

        void Reset()
        {
            this->hintCount = 0;
        }

        void ReadMask(std::istream& stream, std::vector<Type2Object>& objects, uint16_t bitCount)
        {
            uint32_t word = 0;
            int byteIndex = 0;

            for (uint16_t i = 0; i < bitCount; i += 8)
            {
                auto byte = (uint8_t)stream.get();

                word = word | ((uint32_t)byte << (3 - byteIndex) * 8);

                if (byteIndex == 3)
                {
                    objects.push_back(Type2Object(word));
                    word = 0;
                    byteIndex = 0;
                }
                else
                {
                    byteIndex++;
                }
            }

            if (byteIndex > 0)
            {
                objects.push_back(Type2Object(word));
            }
        }

        Type2Object ReadObject(std::istream& stream)
        {
            auto b0 = (uint8_t)stream.get();

            if (this->IsMaskOperator(b0))
            {
                auto operatorType = (Type2OperatorType)b0;
                return Type2Object(operatorType, this->hintCount);
            }
            else if (this->IsOneByteOperator(b0))
            {
                auto operatorType = (Type2OperatorType)b0;
                return Type2Object(operatorType);
            }
            else if (this->IsTwoByteOperator(b0))
            {
                auto b1 = (uint8_t)stream.get();
                auto operatorType = (Type2OperatorType)(((uint16_t)b0 << 8) | b1);
                return Type2Object(operatorType);
            }
            else if ((b0 >= 32) && (b0 <= 246))
            {
                auto number = (int32_t)b0 - 139;
                return Type2Object(number);
            }
            else if ((b0 >= 247) && (b0 <= 250))
            {
                auto b1 = (uint8_t)stream.get();
                auto number = ((int32_t)b0 - 247) * 256 + b1 + 108;
                return Type2Object(number);
            }
            else if ((b0 >= 251) && (b0 <= 254))
            {
                auto b1 = (uint8_t)stream.get();
                auto number = -((int32_t)b0 - 251) * 256 - b1 - 108;
                return Type2Object(number);
            }
            else if (b0 == 28)
            {
                auto b1 = (uint8_t)stream.get();
                auto b2 = (uint8_t)stream.get();
                auto number = ((int32_t)b1 << 8) | b2;
                return Type2Object(number);
            }
            else if (b0 == 255)
            {
                auto b1 = (uint8_t)stream.get();
                auto b2 = (uint8_t)stream.get();
                auto b3 = (uint8_t)stream.get();
                auto b4 = (uint8_t)stream.get();
                auto number =
                    ((int32_t)b1 << 24) |
                    ((int32_t)b2 << 16) |
                    ((int32_t)b3 << 8) |
                    ((int32_t)b4);
                return Type2Object(number);
            }
            else
            {
                throw std::runtime_error("Unknown value format");
            }
        }

        bool IsMaskOperator(uint8_t byte)
        {
            return
                ((uint16_t)byte == (uint16_t)Type2OperatorType::HintMask) ||
                ((uint16_t)byte == (uint16_t)Type2OperatorType::CntrMask);
        }

        bool IsTwoByteOperator(uint8_t byte)
        {
            return byte == 12;
        }

        bool IsOneByteOperator(uint8_t byte)
        {
            return
                (byte < 12) ||
                (byte > 12) && (byte < 28) ||
                (byte > 28) && (byte < 32);
        }
    };
} } }
