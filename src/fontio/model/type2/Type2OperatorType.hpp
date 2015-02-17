#pragma once

#include <cinttypes>
#include <ostream>
#include <functional>

namespace fontio { namespace model { namespace type2
{
    enum class Type2OperatorType : uint16_t
    {
        HStem = 0x0001,
        VStem = 0x0003,
        VMoveTo = 0x0004,
        RLineTo = 0x0005,
        hLineTo = 0x0006,
        VLineTo = 0x0007,
        RRCurveTo = 0x0008,
        CallSubr = 0x000a,
        Return = 0x000b,
        EndChar = 0x000e,
        HStemHM = 0x0012,
        HintMask = 0x0013,
        CntrMask = 0x0014,
        RMoveTo = 0x0015,
        HMoveTo = 0x0016,
        VStemHM = 0x0017,
        RCurveLine = 0x0018,
        RLineCurve = 0x0019,
        VVCurveTo = 0x001a,
        HHCurveTo = 0x001b,
        CallGSubr = 0x001d,
        VHCurveTo = 0x001e,
        HVCurveTo = 0x001f,
        And = 0x0c03,
        Or = 0x0c04,
        Not = 0x0c05,
        Abs = 0x0c09,
        Add = 0x0c0a,
        Sub = 0x0c0b,
        Div = 0x0c0c,
        Neg = 0x0c0e,
        Eq = 0x0c0f,
        Drop = 0x0c12,
        Put = 0x0c14,
        Get = 0x0c15,
        IfElse = 0x0c16,
        Random = 0x0c17,
        Mul = 0x0c18,
        Sqrt = 0x0c1a,
        Dup = 0x0c1b,
        Exch = 0x0c1c,
        Index = 0x0c1d,
        Roll = 0x0c1e,
        HFlex = 0x0c22,
        Flex = 0x0c23,
        HFlex1 = 0x0c24,
        Flex1 = 0x0c25,
    };

    std::ostream& operator << (std::ostream& out, Type2OperatorType type)
    {
        switch (type)
        {
        case Type2OperatorType::HStem:
            return out << "HStem";
        case Type2OperatorType::VStem:
            return out << "VStem";
        case Type2OperatorType::VMoveTo:
            return out << "VMoveTo";
        case Type2OperatorType::RLineTo:
            return out << "RLineTo";
        case Type2OperatorType::hLineTo:
            return out << "hLineTo";
        case Type2OperatorType::VLineTo:
            return out << "VLineTo";
        case Type2OperatorType::RRCurveTo:
            return out << "RRCurveTo";
        case Type2OperatorType::CallSubr:
            return out << "CallSubr";
        case Type2OperatorType::Return:
            return out << "Return";
        case Type2OperatorType::EndChar:
            return out << "EndChar";
        case Type2OperatorType::HStemHM:
            return out << "HStemHM";
        case Type2OperatorType::HintMask:
            return out << "HintMask";
        case Type2OperatorType::CntrMask:
            return out << "CntrMask";
        case Type2OperatorType::RMoveTo:
            return out << "RMoveTo";
        case Type2OperatorType::HMoveTo:
            return out << "HMoveTo";
        case Type2OperatorType::VStemHM:
            return out << "VStemHM";
        case Type2OperatorType::RCurveLine:
            return out << "RCurveLine";
        case Type2OperatorType::RLineCurve:
            return out << "RLineCurve";
        case Type2OperatorType::VVCurveTo:
            return out << "VVCurveTo";
        case Type2OperatorType::HHCurveTo:
            return out << "HHCurveTo";
        case Type2OperatorType::CallGSubr:
            return out << "CallGSubr";
        case Type2OperatorType::VHCurveTo:
            return out << "VHCurveTo";
        case Type2OperatorType::HVCurveTo:
            return out << "HVCurveTo";
        case Type2OperatorType::And:
            return out << "And";
        case Type2OperatorType::Or:
            return out << "Or";
        case Type2OperatorType::Not:
            return out << "Not";
        case Type2OperatorType::Abs:
            return out << "Abs";
        case Type2OperatorType::Add:
            return out << "Add";
        case Type2OperatorType::Sub:
            return out << "Sub";
        case Type2OperatorType::Div:
            return out << "Div";
        case Type2OperatorType::Neg:
            return out << "Neg";
        case Type2OperatorType::Eq:
            return out << "Eq";
        case Type2OperatorType::Drop:
            return out << "Drop";
        case Type2OperatorType::Put:
            return out << "Put";
        case Type2OperatorType::Get:
            return out << "Get";
        case Type2OperatorType::IfElse:
            return out << "IfElse";
        case Type2OperatorType::Random:
            return out << "Random";
        case Type2OperatorType::Mul:
            return out << "Mul";
        case Type2OperatorType::Sqrt:
            return out << "Sqrt";
        case Type2OperatorType::Dup:
            return out << "Dup";
        case Type2OperatorType::Exch:
            return out << "Exch";
        case Type2OperatorType::Index:
            return out << "Index";
        case Type2OperatorType::Roll:
            return out << "Roll";
        case Type2OperatorType::HFlex:
            return out << "HFlex";
        case Type2OperatorType::Flex:
            return out << "Flex";
        case Type2OperatorType::HFlex1:
            return out << "HFlex1";
        case Type2OperatorType::Flex1:
            return out << "Flex1";
        default:
            return out << "<???>";
        }
    }
} } }

namespace std
{
    template<>
    struct hash<fontio::model::type2::Type2OperatorType>
    {
        size_t operator () (fontio::model::type2::Type2OperatorType type) const
        {
            return (size_t)type;
        }
    };
}
