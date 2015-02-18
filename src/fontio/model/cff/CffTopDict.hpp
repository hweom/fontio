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

        std::unordered_map<CffOperatorType, std::vector<CffObject>> objects;

        std::string weight;

        CffFontMatrix fontMatrix;

        BoundBox boundBox;

        std::unique_ptr<ICffCharstrings> charstrings;

        std::unique_ptr<CffCharset> charset;

        std::unique_ptr<ICffCharstrings> localSubroutines;

    public:

        CffTopDict(
            const std::string& weight,
            const CffFontMatrix& fontMatrix,
            const BoundBox& boundBox,
            std::unique_ptr<ICffCharstrings>&& charstrings,
            std::unique_ptr<CffCharset>&& charset,
            std::unique_ptr<ICffCharstrings>&& localSubroutines)
            : weight(weight)
            , fontMatrix(fontMatrix)
            , boundBox(boundBox)
            , charstrings(std::move(charstrings))
            , charset(std::move(charset))
            , localSubroutines(std::move(localSubroutines))
        {
        }

    public:

        CffFontMatrix GetFontMatrix() const
        {
            return this->fontMatrix;
        }

        BoundBox GetBoundBox() const
        {
            return this->boundBox;
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
