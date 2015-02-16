#pragma once

#include <vector>

#include <fontio/model/cff/ICffCharstring.hpp>
#include <fontio/model/type2/Type2Object.hpp>

namespace fontio { namespace model { namespace cff
{
    using namespace fontio::model::type2;

    class CffType2Charstring : public ICffCharstring
    {
    private:

        std::vector<Type2Object> objects;

    public:

        CffType2Charstring(std::vector<Type2Object>&& objects)
            : objects(std::move(objects))
        {
        }

    public:

        virtual CffCharstringFormat GetFormat() const override
        {
            return CffCharstringFormat::Type2;
        }
    };
} } }
