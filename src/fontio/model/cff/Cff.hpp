#pragma once

#include <fontio/model/cff/CffCharset.hpp>
#include <fontio/model/cff/CffHeader.hpp>
#include <fontio/model/cff/CffNameIndex.hpp>
#include <fontio/model/cff/CffStringIndex.hpp>
#include <fontio/model/cff/CffTopDict.hpp>

namespace fontio { namespace model { namespace cff
{
    class Cff
    {
    private:

        CffHeader header;

        CffNameIndex nameIndex;

        std::vector<CffTopDict> topDicts;

        CffStringIndex stringIndex;

    public:

        Cff(
            const CffHeader& header,
            const CffNameIndex& nameIndex,
            std::vector<CffTopDict>&& topDicts,
            const CffStringIndex stringIndex)
            : header(header)
            , nameIndex(nameIndex)
            , topDicts(std::move(topDicts))
            , stringIndex(stringIndex)
        {
        }

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
    };
} } }
