#pragma once

#include <cinttypes>
#include <fstream>
#include <vector>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfCffTable : public IOtfTable
    {
    private:

        std::vector<uint8_t> cffData;

    public:

        OtfCffTable(const std::string& filename)
        {
            std::ifstream stream(filename, std::ios_base::binary);

            stream.seekg(0, std::ios_base::end);
            auto filesize = static_cast<size_t>(stream.tellg());

            stream.seekg(0, std::ios_base::beg);
            stream.clear();

            this->cffData.resize(filesize);

            stream.read(reinterpret_cast<char*>(this->cffData.data()), filesize);
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Cmap;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            out.write(reinterpret_cast<const char*>(this->cffData.data()), this->cffData.size());
        }

        virtual uint32_t GetId() const override
        {
            return 0x43464620; // CFF
        }
    };
} } }
