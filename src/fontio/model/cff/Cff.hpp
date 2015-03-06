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

#include <fontio/model/cff/CffHeader.hpp>
#include <fontio/model/cff/CffNameIndex.hpp>
#include <fontio/model/cff/CffStringIndex.hpp>
#include <fontio/model/cff/CffTopDict.hpp>
#include <fontio/model/cff/ICffCharset.hpp>

namespace fontio { namespace model { namespace cff
{
    class Cff
    {
    private:

        CffHeader header;

        CffNameIndex nameIndex;

        std::vector<CffTopDict> topDicts;

        CffStringIndex stringIndex;

        std::unique_ptr<ICffCharstrings> globalSubroutines;

    public:

        Cff(
            const CffHeader& header,
            const CffNameIndex& nameIndex,
            std::vector<CffTopDict>&& topDicts,
            const CffStringIndex stringIndex,
            std::unique_ptr<ICffCharstrings>&& globalSubroutines)
            : header(header)
            , nameIndex(nameIndex)
            , topDicts(std::move(topDicts))
            , stringIndex(stringIndex)
            , globalSubroutines(std::move(globalSubroutines))
        {
        }

        Cff(const Cff& other) = delete;

    public:

        const CffHeader& GetHeader() const
        {
            return this->header;
        }

        const CffNameIndex& GetNameIndex() const
        {
            return this->nameIndex;
        }

        const std::vector<CffTopDict>& GetTopDicts() const
        {
            return this->topDicts;
        }

        const CffStringIndex& GetStringIndex() const
        {
            return this->stringIndex;
        }

        bool HasGlobalSubroutines() const
        {
            return this->globalSubroutines != nullptr;
        }

        const ICffCharstrings& GetGlobalSubroutines() const
        {
            assert (this->HasGlobalSubroutines());

            return *this->globalSubroutines;
        }
    };
} } }
