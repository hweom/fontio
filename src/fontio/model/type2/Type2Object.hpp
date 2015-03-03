#pragma once

#include <cinttypes>
#include <limits>
#include <unordered_map>

#include <fontio/model/type2/Type2ObjectType.hpp>

namespace fontio { namespace model { namespace type2
{
    class Type2Object
    {
    private:

        Type2ObjectType type;

        union
        {
            /// Bitmask for hint operators.
            uint64_t bitmask;

            /// Integer value if object is an operand.
            int32_t integerValue;
        };

    public:

        Type2Object()
        {
        }

        Type2Object(Type2ObjectType operatorType, uint64_t bitmask = 0)
            : type(operatorType)
            , bitmask(bitmask)
        {
        }

        Type2Object(int32_t integerValue)
            : type(Type2ObjectType::Operand)
            , integerValue(integerValue)
        {
        }

    public:

        bool IsOperator() const
        {
            return this->type != Type2ObjectType::Operand;
        }

        bool IsOperand() const
        {
            return this->type == Type2ObjectType::Operand;
        }

        Type2ObjectType GetType() const
        {
            return this->type;
        }

        uint64_t GetBitmask() const
        {
            return this->bitmask;
        }

        int32_t GetIntegerSafe() const
        {
            if (this->type == Type2ObjectType::Operand)
            {
                return this->integerValue;
            }
            else
            {
                throw std::runtime_error("Not an integer");
            }
        }

        int GetOperatorStackChange() const
        {
            assert (this->IsOperator());

            const auto& ops = GetStackChangeTable();

            auto pos = ops.find(this->type);

            if (pos == ops.end())
            {
                throw std::runtime_error("No record for operator in stack change table");
            }

            return pos->second;
        }

        bool IsStackClearingOperator() const
        {
            assert (this->IsOperator());

            const auto& ops = GetStackChangeTable();

            auto pos = ops.find(this->type);

            return (pos != ops.end() && (pos->second == std::numeric_limits<int>::min()));
        }

        friend inline std::ostream& operator << (std::ostream& out, const Type2Object& obj)
        {
            if (obj.IsOperator())
            {
                out << obj.type;

                auto mask = obj.GetBitmask();
                while (mask != 0)
                {
                    out << " ";

                    auto byte = (mask >> 56) & 0xff;

                    for (size_t i = 0; i < 8; i++)
                    {
                        if (byte & (0x80 >> i))
                        {
                            out << "1";
                        }
                        else
                        {
                            out << "0";
                        }
                    }

                    mask <<= 8;
                }
            }
            else
            {
                out << std::dec << obj.integerValue;
            }

            return out;
        }

    private:

        static const std::unordered_map<Type2ObjectType, int>& GetStackChangeTable()
        {
            auto clear = std::numeric_limits<int>::min();

            static std::unordered_map<Type2ObjectType, int> ops =
            {
                { Type2ObjectType::RMoveTo, clear },
                { Type2ObjectType::HMoveTo, clear },
                { Type2ObjectType::VMoveTo, clear },
                { Type2ObjectType::RLineTo, clear },
                { Type2ObjectType::HLineTo, clear },
                { Type2ObjectType::VLineTo, clear },
                { Type2ObjectType::RRCurveTo, clear },
                { Type2ObjectType::HHCurveTo, clear },
                { Type2ObjectType::HVCurveTo, clear },
                { Type2ObjectType::RCurveLine, clear },
                { Type2ObjectType::RLineCurve, clear },
                { Type2ObjectType::VHCurveTo, clear },
                { Type2ObjectType::VVCurveTo, clear },
                { Type2ObjectType::Flex, clear },
                { Type2ObjectType::HFlex, clear },
                { Type2ObjectType::HFlex1, clear },
                { Type2ObjectType::Flex1, clear },
                { Type2ObjectType::EndChar, clear },
                { Type2ObjectType::HStem, clear },
                { Type2ObjectType::VStem, clear },
                { Type2ObjectType::HStemHM, clear },
                { Type2ObjectType::VStemHM, clear },
                { Type2ObjectType::HintMask, clear },
                { Type2ObjectType::CntrMask, clear },
                { Type2ObjectType::CallGSubr, -1 },
                { Type2ObjectType::CallSubr, -1 },
                { Type2ObjectType::Return, 0 },
                { Type2ObjectType::EndChar, 0 },
                { Type2ObjectType::Blend, 0 },
                { Type2ObjectType::Abs, 0 },
                { Type2ObjectType::Add, -1 },
                { Type2ObjectType::Sub, -1 },
                { Type2ObjectType::Div, -1 },
                { Type2ObjectType::Neg, 0 },
                { Type2ObjectType::Random, 1 },
                { Type2ObjectType::Mul, -1 },
                { Type2ObjectType::Sqrt, 0 },
                { Type2ObjectType::Drop, -1 },
                { Type2ObjectType::Exch, 0 },
                { Type2ObjectType::Index, 1 },
                { Type2ObjectType::Roll, 0 },
                { Type2ObjectType::Dup, 1 },
                { Type2ObjectType::Put, -1 },
                { Type2ObjectType::Get, 1 },
                { Type2ObjectType::And, -1 },
                { Type2ObjectType::Or, -1 },
                { Type2ObjectType::Not, 0 },
                { Type2ObjectType::Eq, -1 },
                { Type2ObjectType::IfElse, -3 }
            };

            return ops;
        }
    };
} } }
