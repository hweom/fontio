#pragma once

#include <vector>

#include <fontio/model/type2/Type2Object.hpp>

namespace fontio { namespace model { namespace type2
{
    class Type2Charstring
    {
    private:

        std::vector<Type2Object> objects;

    public:

        Type2Charstring(std::vector<Type2Object>&& objects)
            : objects(objects)
        {
        }

    public:

        const std::vector<Type2Object>& GetObjects() const
        {
            return this->objects;
        }
    };
} } }
