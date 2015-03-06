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

#include <memory>
#include <unordered_map>
#include <vector>

#include <fontio/model/BoundBox.hpp>
#include <fontio/model/cff/ICffCharset.hpp>
#include <fontio/model/cff/CffCharsetType.hpp>
#include <fontio/model/cff/CffFontMatrix.hpp>
#include <fontio/model/cff/CffOperatorType.hpp>
#include <fontio/model/cff/CffObject.hpp>
#include <fontio/model/cff/ICffCharstrings.hpp>

namespace fontio { namespace model { namespace cff
{
    using namespace fontio::model::cff;

    class CffTopDict
    {
    private:

        std::string version;

        std::string notice;

        std::string copyright;

        std::string fullName;

        std::string familyName;

        std::string weight;

        CffFontMatrix fontMatrix;

        BoundBox boundBox;

        int32_t defaultWidthX;

        int32_t nominalWidthX;

        std::unique_ptr<ICffCharstrings> charstrings;

        std::unique_ptr<ICffCharset> charset;

        std::unique_ptr<ICffCharstrings> localSubroutines;

    public:

        CffTopDict(
            const std::string version,
            const std::string notice,
            const std::string copyright,
            const std::string fullName,
            const std::string familyName,
            const std::string& weight,
            const CffFontMatrix& fontMatrix,
            const BoundBox& boundBox,
            int32_t defaultWidthX,
            int32_t nominalWidthX,
            std::unique_ptr<ICffCharstrings>&& charstrings,
            std::unique_ptr<ICffCharset>&& charset,
            std::unique_ptr<ICffCharstrings>&& localSubroutines)
            : version(version)
            , notice(notice)
            , copyright(copyright)
            , fullName(fullName)
            , familyName(familyName)
            , weight(weight)
            , fontMatrix(fontMatrix)
            , boundBox(boundBox)
            , defaultWidthX(defaultWidthX)
            , nominalWidthX(nominalWidthX)
            , charstrings(std::move(charstrings))
            , charset(std::move(charset))
            , localSubroutines(std::move(localSubroutines))
        {
        }

        CffTopDict(CffTopDict&& other)
            : version(std::move(other.version))
            , notice(std::move(other.notice))
            , copyright(std::move(other.copyright))
            , fullName(std::move(other.fullName))
            , familyName(std::move(other.familyName))
            , weight(std::move(other.weight))
            , fontMatrix(std::move(other.fontMatrix))
            , boundBox(std::move(other.boundBox))
            , defaultWidthX(std::move(other.defaultWidthX))
            , nominalWidthX(std::move(other.nominalWidthX))
            , charstrings(std::move(other.charstrings))
            , charset(std::move(other.charset))
            , localSubroutines(std::move(other.localSubroutines))
        {
        }

        CffTopDict(const CffTopDict& other) = delete;

    public:

        const std::string GetVersion() const
        {
            return this->version;
        }

        const std::string GetNotice() const
        {
            return this->notice;
        }

        const std::string GetCopyright() const
        {
            return this->copyright;
        }

        const std::string GetFullName() const
        {
            return this->fullName;
        }

        const std::string GetFamilyName() const
        {
            return this->familyName;
        }

        CffFontMatrix GetFontMatrix() const
        {
            return this->fontMatrix;
        }

        BoundBox GetBoundBox() const
        {
            return this->boundBox;
        }

        int32_t GetDefaultWidthX() const
        {
            return this->defaultWidthX;
        }

        int32_t GetNominalWidthX() const
        {
            return this->nominalWidthX;
        }

        const std::string GetWeight() const
        {
            return this->weight;
        }

        const ICffCharstrings& GetCharstrings() const
        {
            assert (this->charstrings != nullptr);

            return *this->charstrings;
        }

        const ICffCharset& GetCharset() const
        {
            assert (this->charset != nullptr);

            return *this->charset;
        }

        bool HasLocalSubroutines() const
        {
            return this->localSubroutines != nullptr;
        }

        const ICffCharstrings& GetLocalSubroutines() const
        {
            assert (this->HasLocalSubroutines());

            return *this->localSubroutines;
        }
    };
} } }
