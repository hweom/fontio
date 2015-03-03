#pragma once

#include <cinttypes>
#include <ostream>
#include <functional>

namespace fontio { namespace model { namespace type2
{
    enum class Type2ObjectType
    {
        Operand = 0,
        HStem = 0x0001,
        VStem = 0x0003,
        VMoveTo = 0x0004,
        RLineTo = 0x0005,
        HLineTo = 0x0006,
        VLineTo = 0x0007,
        RRCurveTo = 0x0008,
        CallSubr = 0x000a,
        Return = 0x000b,
        EndChar = 0x000e,
        Blend = 0x0010,
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

    inline std::ostream& operator << (std::ostream& out, Type2ObjectType type)
    {
        switch (type)
        {
        case Type2ObjectType::HStem:
            return out << "HStem";
        case Type2ObjectType::VStem:
            return out << "VStem";
        case Type2ObjectType::VMoveTo:
            return out << "VMoveTo";
        case Type2ObjectType::RLineTo:
            return out << "RLineTo";
        case Type2ObjectType::HLineTo:
            return out << "hLineTo";
        case Type2ObjectType::VLineTo:
            return out << "VLineTo";
        case Type2ObjectType::RRCurveTo:
            return out << "RRCurveTo";
        case Type2ObjectType::CallSubr:
            return out << "CallSubr";
        case Type2ObjectType::Return:
            return out << "Return";
        case Type2ObjectType::EndChar:
            return out << "EndChar";
        case Type2ObjectType::HStemHM:
            return out << "HStemHM";
        case Type2ObjectType::HintMask:
            return out << "HintMask";
        case Type2ObjectType::CntrMask:
            return out << "CntrMask";
        case Type2ObjectType::RMoveTo:
            return out << "RMoveTo";
        case Type2ObjectType::HMoveTo:
            return out << "HMoveTo";
        case Type2ObjectType::VStemHM:
            return out << "VStemHM";
        case Type2ObjectType::RCurveLine:
            return out << "RCurveLine";
        case Type2ObjectType::RLineCurve:
            return out << "RLineCurve";
        case Type2ObjectType::VVCurveTo:
            return out << "VVCurveTo";
        case Type2ObjectType::HHCurveTo:
            return out << "HHCurveTo";
        case Type2ObjectType::CallGSubr:
            return out << "CallGSubr";
        case Type2ObjectType::VHCurveTo:
            return out << "VHCurveTo";
        case Type2ObjectType::HVCurveTo:
            return out << "HVCurveTo";
        case Type2ObjectType::And:
            return out << "And";
        case Type2ObjectType::Or:
            return out << "Or";
        case Type2ObjectType::Not:
            return out << "Not";
        case Type2ObjectType::Abs:
            return out << "Abs";
        case Type2ObjectType::Add:
            return out << "Add";
        case Type2ObjectType::Sub:
            return out << "Sub";
        case Type2ObjectType::Div:
            return out << "Div";
        case Type2ObjectType::Neg:
            return out << "Neg";
        case Type2ObjectType::Eq:
            return out << "Eq";
        case Type2ObjectType::Drop:
            return out << "Drop";
        case Type2ObjectType::Put:
            return out << "Put";
        case Type2ObjectType::Get:
            return out << "Get";
        case Type2ObjectType::IfElse:
            return out << "IfElse";
        case Type2ObjectType::Random:
            return out << "Random";
        case Type2ObjectType::Mul:
            return out << "Mul";
        case Type2ObjectType::Sqrt:
            return out << "Sqrt";
        case Type2ObjectType::Dup:
            return out << "Dup";
        case Type2ObjectType::Exch:
            return out << "Exch";
        case Type2ObjectType::Index:
            return out << "Index";
        case Type2ObjectType::Roll:
            return out << "Roll";
        case Type2ObjectType::HFlex:
            return out << "HFlex";
        case Type2ObjectType::Flex:
            return out << "Flex";
        case Type2ObjectType::HFlex1:
            return out << "HFlex1";
        case Type2ObjectType::Flex1:
            return out << "Flex1";
        default:
            return out << "<???>";
        }
    }
} } }

namespace std
{
    template<>
    struct hash<fontio::model::type2::Type2ObjectType>
    {
        size_t operator () (fontio::model::type2::Type2ObjectType type) const
        {
            return (size_t)type;
        }
    };
}
