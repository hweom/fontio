#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <fontio/logic/type2/Type2CharstringReaderState.hpp>
#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model::type2;

    class Type2CharstringReader
    {
    private:

        Type2CharstringReaderState& state;

        std::vector<uint8_t>::const_iterator cur;

        std::vector<uint8_t>::const_iterator end;

    public:

        Type2CharstringReader(Type2CharstringReaderState& state, const Type2Charstring& charstring)
            : state(state)
            , cur(charstring.GetBytes().begin())
            , end(charstring.GetBytes().end())
        {
        }

    public:

        bool GetNextObject(Type2Object& object)
        {
            if (!this->ReadObject(object))
            {
                return false;
            }

            if (object.IsOperator())
            {
                if ((object.GetType() == Type2ObjectType::HStem) ||
                    (object.GetType() == Type2ObjectType::VStem) ||
                    (object.GetType() == Type2ObjectType::HStemHM) ||
                    (object.GetType() == Type2ObjectType::VStemHM) ||
                    (object.GetType() == Type2ObjectType::HintMask) ||
                    (object.GetType() == Type2ObjectType::CntrMask))
                {
                    this->state.AddHintCount(this->state.GetStackDepth() / 2);
                }

                if ((object.GetType() == Type2ObjectType::HintMask) ||
                    (object.GetType() == Type2ObjectType::CntrMask))
                {
                    object = Type2Object(object.GetType(), this->ReadMask(this->state.GetHintCount()));
                }

                this->state.ChangeStackDepth(object.GetOperatorStackChange());
            }
            else
            {
                this->state.IncrementStackDepth();
            }

            return true;
        }

    private:

        uint64_t ReadMask(size_t bitCount)
        {
            uint64_t mask = 0;
            for (uint16_t i = 0; i < bitCount; i += 8)
            {
                if (this->IsAtEnd())
                {
                    return mask;
                }

                auto byte = *this->cur++;

                mask = (mask >> 8) | ((uint64_t)byte << 56);
            }

            return mask;
        }

        bool ReadObject(Type2Object& object)
        {
            if (this->IsAtEnd())
            {
                return false;
            }

            auto b0 = *this->cur++;

            if (this->IsOneByteOperator(b0))
            {
                auto operatorType = (Type2ObjectType)b0;
                object = Type2Object(operatorType);
            }
            else if (this->IsTwoByteOperator(b0))
            {
                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b1 = *this->cur++;

                // std::cout << std::hex << (uint32_t)b1 << " ";

                auto operatorType = (Type2ObjectType)(((uint16_t)b0 << 8) | b1);
                object = Type2Object(operatorType);
            }
            else if ((b0 >= 32) && (b0 <= 246))
            {
                auto number = (int32_t)b0 - 139;
                object = Type2Object(number);
            }
            else if ((b0 >= 247) && (b0 <= 250))
            {
                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b1 = *this->cur++;

                // std::cout << std::hex << (uint32_t)b1 << " ";

                auto number = ((int32_t)b0 - 247) * 256 + b1 + 108;
                object = Type2Object(number);
            }
            else if ((b0 >= 251) && (b0 <= 254))
            {
                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b1 = *this->cur++;

                // std::cout << std::hex << (uint32_t)b1 << " ";

                auto number = -((int32_t)b0 - 251) * 256 - b1 - 108;
                object = Type2Object(number);
            }
            else if (b0 == 28)
            {
                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b1 = *this->cur++;

                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b2 = *this->cur++;

                // std::cout << (uint32_t)b1 << " " << (uint32_t)b2 << " ";

                auto number = ((int32_t)b1 << 8) | b2;
                object = Type2Object(number);
            }
            else if (b0 == 255)
            {
                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b1 = *this->cur++;

                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b2 = *this->cur++;

                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b3 = *this->cur++;

                if (this->IsAtEnd())
                {
                    return false;
                }

                auto b4 = *this->cur++;

                // std::cout << std::hex << (uint32_t)b1 << " " << (uint32_t)b2 << " "<< (uint32_t)b3 << " "<< (uint32_t)b4 << " ";

                auto number =
                    ((int32_t)b1 << 24) |
                    ((int32_t)b2 << 16) |
                    ((int32_t)b3 << 8) |
                    ((int32_t)b4);

                object = Type2Object(number);
            }
            else
            {
                throw std::runtime_error("Unknown value format");
            }

            return true;
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

        bool IsAtEnd() const
        {
            return this->cur == this->end;
        }
    };
} } }
