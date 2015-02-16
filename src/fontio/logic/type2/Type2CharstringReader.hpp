#pragma once

#include <memory>
#include <vector>

#include <fontio/model/type2/Type2Object.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model::type2;

    class Type2CharstringReader
    {
    public:

        std::vector<Type2Object> ReadType2Charstring(std::istream& stream, uint32_t length)
        {
            std::vector<Type2Object> objects;

            auto start = (uint32_t)stream.tellg();
            while (((uint32_t)stream.tellg() - start) < length)
            {
                objects.push_back(this->ReadObject(stream));
            }

            return objects;
        }

    private:

        Type2Object ReadObject(std::istream& stream)
        {
            auto b0 = (uint8_t)stream.get();

            if ((b0 < 12) ||
                ((b0 > 12) && (b0 < 28)) ||
                ((b0 > 28) && (b0 < 32)))
            {
                auto operatorType = (Type2OperatorType)b0;
                return Type2Object(operatorType);
            }
            else if (b0 == 12)
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
                auto number = -((int32_t)b0 - 247) * 256 - b1 - 108;
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
    };
} } }
