#pragma once

#include <unordered_map>

namespace fontio { namespace model { namespace cff
{
    class ICffCharset
    {
    public:

        virtual ~ICffCharset()
        {
        }

    public:

        uint16_t operator [] (uint16_t gid) const
        {
            const auto& map = this->GetGidToSidMap();
            auto pos = map.find(gid);

            if (pos == map.end())
            {
                throw std::runtime_error("No such gid/sid pair in charset");
            }

            return pos->second;
        }

        virtual const std::unordered_map<uint16_t, uint16_t>& GetGidToSidMap() const = 0;
    };
} } }
