#pragma once

#include <istream>

namespace fontio { namespace model { namespace cff
{
    class CffHeader
    {
    private:

        uint8_t versionMajor;

        uint8_t versionMinor;

        uint8_t headerSize;

        uint8_t offsetSize;

    public:

        CffHeader()
        {
        }

        CffHeader(std::istream& stream)
        {
            stream.read(reinterpret_cast<char*>(&this->versionMajor), 4);
        }

    public:

        uint8_t GetVersionMajor() const
        {
            return this->versionMajor;
        }

        uint8_t GetVersionMinor() const
        {
            return this->versionMinor;
        }

        uint8_t GetHeaderSize() const
        {
            return this->headerSize;
        }

        uint8_t GetOffsetSize() const
        {
            return this->offsetSize;
        }
    };
} } }
