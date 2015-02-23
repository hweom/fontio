#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <fontio/model/BoundBox.hpp>
#include <fontio/model/cff/CffCharset.hpp>
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

        std::unique_ptr<CffCharset> charset;

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
            std::unique_ptr<CffCharset>&& charset,
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

        const CffCharset& GetCharset() const
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
