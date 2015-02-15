#pragma once

#include <fontio/model/cff/CffIndex.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffNameIndex
    {
    private:

        std::vector<std::string> names;

    public:

        CffNameIndex(const std::vector<std::string>& names)
            : names(names)
        {
        }

    public:

        const std::vector<std::string>& GetNames() const
        {
            return this->names;
        }
    };
} } }
