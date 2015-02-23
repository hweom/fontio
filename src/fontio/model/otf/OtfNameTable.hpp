#pragma once

#include <map>

#include <fontio/model/otf/OtfNameId.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfNameTable : public IOtfTable
    {
    private:

        std::map<OtfNameId, std::wstring> names;

    public:

        OtfNameTable(const std::map<OtfNameId, std::wstring>& names)
            : names(names)
        {
        }

        OtfNameTable(std::initializer_list<std::pair<const OtfNameId, std::wstring>>& names)
            : names(names)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Name;
        }
    };
} } }
