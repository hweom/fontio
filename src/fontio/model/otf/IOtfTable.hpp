#pragma once

#include <ostream>

#include <fontio/model/otf/OtfTableCrc.hpp>
#include <fontio/model/otf/OtfTableType.hpp>

namespace fontio { namespace model { namespace otf
{
    class IOtfTable
    {
    public:

        virtual ~IOtfTable()
        {
        }

    public:

        virtual OtfTableType GetType() const = 0;

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const = 0;

        virtual uint32_t GetId() const = 0;
    };
} } }
