#pragma once

#include <unordered_map>

namespace fontio { namespace model { namespace cff
{
    class CffCharset
    {
    private:

        std::unordered_map<uint16_t, uint16_t> gidToSid;

    public:

        CffCharset()
        {
        }

        CffCharset(const std::unordered_map<uint16_t, uint16_t>& gidToSid)
            : gidToSid(gidToSid)
        {
        }

    public:

        uint16_t operator [] (uint16_t gid) const
        {
            auto pos = this->gidToSid.find(gid);

            assert (pos != this->gidToSid.end());

            return pos->second;
        }
    };
} } }
