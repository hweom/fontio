#pragma once

#include <cinttypes>
#include <unordered_set>

#include <fontio/model/type2/Type2OperatorType.hpp>

namespace fontio { namespace model { namespace type2
{
    class Type2Object
    {
    public:

        enum Type
        {
            Operator = 0,

            Integer = 1,
        };

    private:

        Type type;

        union
        {
            struct
            {
                /// Operator type if object is an operator.
                Type2OperatorType operatorType;

                /// Number of bits if object is mask operator (hintmask or cntrmask).
                uint16_t argCount;
            };

            /// Integer value if object is an operand.
            int32_t integerValue;
        };

    public:

        Type2Object(Type2OperatorType operatorType, uint16_t argCount = 0)
            : type(Operator)
            , operatorType(operatorType)
            , argCount(argCount)
        {
        }

        Type2Object(int32_t integerValue)
            : type(Integer)
            , integerValue(integerValue)
        {
        }

        Type2Object(uint32_t integerValue)
            : type(Integer)
            , integerValue((int32_t)integerValue)
        {
        }

    public:

        bool IsOperator() const
        {
            return this->type == Operator;
        }

        bool IsOperand() const
        {
            return this->type != Operator;
        }

        Type2OperatorType GetOperator() const
        {
            assert (this->type == Operator);

            return this->operatorType;
        }

        uint16_t GetArgCount() const
        {
            assert (this->type == Operator);

            return this->argCount;
        }

        int64_t GetIntegerSafe() const
        {
            if (this->type == Integer)
            {
                return this->integerValue;
            }
            else
            {
                throw std::runtime_error("Not an integer");
            }
        }

        bool IsStackClearingOperator() const
        {
            assert (this->IsOperator());

            const auto& ops = GetStackClearingOperators();

            return ops.count(this->operatorType) > 0;
        }

    private:

        static const std::unordered_set<Type2OperatorType>& GetStackClearingOperators()
        {
            static std::unordered_set<Type2OperatorType> ops =
            {
                Type2OperatorType::RMoveTo,
                Type2OperatorType::HMoveTo,
                Type2OperatorType::VMoveTo,
                Type2OperatorType::RLineTo,
                Type2OperatorType::HLineTo,
                Type2OperatorType::VLineTo,
                Type2OperatorType::RRCurveTo,
                Type2OperatorType::HHCurveTo,
                Type2OperatorType::HVCurveTo,
                Type2OperatorType::RCurveLine,
                Type2OperatorType::RLineCurve,
                Type2OperatorType::VHCurveTo,
                Type2OperatorType::VVCurveTo,
                Type2OperatorType::Flex,
                Type2OperatorType::HFlex,
                Type2OperatorType::HFlex1,
                Type2OperatorType::Flex1,
                Type2OperatorType::EndChar,
                Type2OperatorType::HStem,
                Type2OperatorType::VStem,
                Type2OperatorType::HStemHM,
                Type2OperatorType::VStemHM,
                Type2OperatorType::HintMask,
                Type2OperatorType::CntrMask
            };

            return ops;
        }
    };
} } }
