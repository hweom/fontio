#pragma once

#include <cinttypes>

namespace fontio { namespace model { namespace otf
{
    class OtfTableCrc
    {
    private:

        int byteIndex = 0;

        uint32_t currentWord = 0;

        uint32_t crc = 0;

    public:

        void operator () (uint8_t byte)
        {
            this->currentWord = (this->currentWord << 8) | byte;

            if (++this->byteIndex >= 4)
            {
                this->crc += this->currentWord;
                this->currentWord = 0;
                this->byteIndex = 0;
            }
        }

        void Adjust(uint32_t crcAdjustment)
        {
            this->crc += crcAdjustment;
        }

        uint32_t GetCrc() const
        {
            return this->crc;
        }

        int GetPadBytes()
        {
            return (4 - this->byteIndex) % 4;
        }
    };
} } }
