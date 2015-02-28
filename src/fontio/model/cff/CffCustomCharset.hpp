#pragma once

#include <fontio/model/cff/ICffCharset.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffCustomCharset : public ICffCharset
    {
    private:

        std::unordered_map<uint16_t, uint16_t> gidToSid;

    public:

        CffCustomCharset()
        {
        }

        CffCustomCharset(const std::unordered_map<uint16_t, uint16_t>& gidToSid)
            : gidToSid(gidToSid)
        {
        }

    public:

        virtual const std::unordered_map<uint16_t, uint16_t>& GetGidToSidMap() const override
        {
            return this->gidToSid;
        }
    };
} } }
