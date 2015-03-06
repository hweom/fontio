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

#include <ostream>

namespace fontio { namespace infrastructure
{
    struct BigEndian
    {
    };

    struct LittleEndian
    {
    };

    namespace details
    {
        template<typename Endianness, typename T, typename Enable = void>
        struct WriteBytesImpl
        {
            void operator () (std::ostream& out, T value)
            {
                static_assert(sizeof(T) == 0, "Not implemented");
            }

            template<typename F>
            void operator () (std::ostream& out, T value, F func)
            {
                static_assert(sizeof(T) == 0, "Not implemented");
            }
        };

        template<typename T>
        struct WriteBytesImpl<BigEndian, T, typename std::enable_if<std::is_integral<T>::value, void>::type>
        {
            void operator () (std::ostream& out, T value)
            {
                for (size_t i = 0; i < sizeof(T); i++)
                {
                    auto byte = static_cast<uint8_t>((value >> ((sizeof(T) - i - 1) * 8)) & 0xff);

                    out.put(byte);
                }
            }

            template<typename F>
            void operator () (std::ostream& out, T value, F func)
            {
                for (size_t i = 0; i < sizeof(T); i++)
                {
                    auto byte = static_cast<uint8_t>((value >> ((sizeof(T) - i - 1) * 8)) & 0xff);

                    func(byte);

                    out.put(static_cast<std::ostream::char_type>(byte));
                }
            }
        };
    }

    template<typename Endianness, typename T>
    inline void WriteBytes(std::ostream& out, T value)
    {
        return details::WriteBytesImpl<Endianness, T>()(out, value);
    }

    template<typename Endianness, typename T, typename F>
    inline void WriteBytes(std::ostream& out, T value, F func)
    {
        return details::WriteBytesImpl<Endianness, T>()(out, value, func);
    }
} }
