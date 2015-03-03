#pragma once

#include <ostream>
#include <vector>

#include <fontio/model/type2/Type2Object.hpp>

namespace fontio { namespace model { namespace type2
{
    class Type2Charstring
    {
    private:

        std::vector<uint8_t> bytes;

    public:

        Type2Charstring(std::vector<uint8_t>&& bytes)
            : bytes(bytes)
        {
        }

    public:

        const std::vector<uint8_t>& GetBytes() const
        {
            return this->bytes;
        }
    };
} } }
