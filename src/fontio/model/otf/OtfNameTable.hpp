// The Modified BSD License
//
// Copyright (c) 2015, Mikhail Balakhno
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of fontio nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <cstdint>
#include <map>
#include <stdexcept>
#include <vector>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/OtfNameId.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfNameTable : public IOtfTable
    {
    private:

        struct NameRecord
        {
            uint16_t platformId;

            uint16_t encodingId;

            uint16_t languageId;

            uint16_t nameId;

            uint16_t length;

            uint16_t offset;
        };

        struct NameEntry
        {
            NameRecord header;

            std::wstring text;

            size_t characterWidth;
        };

    private:

        static const uint16_t PLATFORM_MACINTOSH = 1;

        static const uint16_t PLATFORM_WINDOWS = 3;

        static const uint16_t ENCODING_MACINTOSH_ROMAN = 0;

        static const uint16_t ENCODING_WINDOWS_UNICODE2 = 1;

        static const uint16_t LANGUAGE_MACINTOSH_ENGLISH = 0;

        static const uint16_t LANGUAGE_WINDOWS_ENGLISH_US = 0x409;

    private:

        std::map<OtfNameId, std::wstring> names;

    public:

        OtfNameTable(const std::map<OtfNameId, std::wstring>& names)
            : names(names)
        {
        }

        OtfNameTable(std::initializer_list<std::pair<const OtfNameId, std::wstring>>& names)
            : names(names)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Name;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            auto entries = this->BuildEntries();

            auto stringsOffset = entries.size() * sizeof(NameRecord) + 6;

            WriteBytes<BigEndian>(out, static_cast<uint16_t>(0), crc);                  // Format.
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(entries.size()), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(stringsOffset), crc);

            for (const auto& entry : entries)
            {
                WriteBytes<BigEndian>(out, entry.header.platformId, crc);
                WriteBytes<BigEndian>(out, entry.header.encodingId, crc);
                WriteBytes<BigEndian>(out, entry.header.languageId, crc);
                WriteBytes<BigEndian>(out, entry.header.nameId, crc);
                WriteBytes<BigEndian>(out, entry.header.length, crc);
                WriteBytes<BigEndian>(out, entry.header.offset, crc);
            }

            for (const auto& entry : entries)
            {
                this->WriteStringData(out, entry.text, entry.characterWidth, crc);
            }
        }

        virtual uint32_t GetId() const override
        {
            return 0x6e616d65; // name
        }

    private:

        std::vector<NameEntry> BuildEntries() const
        {
            std::vector<NameEntry> result;

            this->BuildMacintoshEntries(result);
            this->BuildWindowsEntries(result);

            this->FillOffsets(result);

            return result;
        }

        void BuildMacintoshEntries(std::vector<NameEntry>& entries) const
        {
            for (const auto& pair : this->names)
            {
                entries.emplace_back(
                    NameEntry({
                        {
                            PLATFORM_MACINTOSH,
                            ENCODING_MACINTOSH_ROMAN,
                            LANGUAGE_MACINTOSH_ENGLISH,
                            static_cast<uint16_t>(pair.first),
                            static_cast<uint16_t>(pair.second.length()),
                            0
                        },
                        pair.second,
                        1
                    }));
            }
        }

        void BuildWindowsEntries(std::vector<NameEntry>& entries) const
        {
            for (const auto& pair : this->names)
            {
                entries.emplace_back(
                    NameEntry({
                        {
                            PLATFORM_WINDOWS,
                            ENCODING_WINDOWS_UNICODE2,
                            LANGUAGE_WINDOWS_ENGLISH_US,
                            static_cast<uint16_t>(pair.first),
                            static_cast<uint16_t>(pair.second.length() * 2),
                            0
                        },
                        pair.second,
                        2
                    }));
            }
        }

        void FillOffsets(std::vector<NameEntry> entries) const
        {
            uint16_t offset = 0;

            for (auto& entry : entries)
            {
                entry.header.offset = offset;

                offset += static_cast<uint16_t>(entry.text.size() * entry.characterWidth);
            }
        }

        void WriteStringData(std::ostream& out, const std::wstring& text, size_t characterWidth, OtfTableCrc& crc) const
        {
            if (characterWidth == 1)
            {
                this->WriteStringBytes<uint8_t>(out, text, crc);
            }
            else if (characterWidth == 2)
            {
                this->WriteStringBytes<uint16_t>(out, text, crc);
            }
            else if (characterWidth == 4)
            {
                this->WriteStringBytes<uint32_t>(out, text, crc);
            }
            else
            {
                throw std::logic_error("Unsupported character width");
            }
        }

        template<typename T>
        void WriteStringBytes(std::ostream& out, const std::wstring& text, OtfTableCrc& crc) const
        {
            for (auto c : text)
            {
                WriteBytes<BigEndian>(out, static_cast<T>(c), crc);
            }
        }
    };
} } }
