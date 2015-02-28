#pragma once

#include <fontio/model/AdobeGlyphList.hpp>
#include <fontio/model/cff/CffIndex.hpp>
#include <fontio/model/cff/CffStandardStrings.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffStringIndex
    {
    private:

        std::vector<std::string> names;

    public:

        CffStringIndex(const std::vector<std::string>& names)
            : names(names)
        {
        }

    public:

        const std::string& GetString(size_t index) const
        {
            const auto& stdStrings = CffStandardStrings::Get();
            if (index < stdStrings.size())
            {
                return stdStrings[index];
            }

            index -= stdStrings.size();

            assert (index < this->names.size());

            return this->names[index];
        }
    };
} } }
