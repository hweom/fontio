#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <fontio/model/cff/CffBoundBox.hpp>
#include <fontio/model/cff/CffCharset.hpp>
#include <fontio/model/cff/CffCharsetType.hpp>
#include <fontio/model/cff/CffFontMatrix.hpp>
#include <fontio/model/cff/CffOperatorType.hpp>
#include <fontio/model/cff/CffObject.hpp>

namespace fontio { namespace model { namespace cff
{
    using namespace fontio::model::cff;

    class CffTopDict
    {
    private:

        std::unordered_map<CffOperatorType, std::vector<CffObject>> objects;

        std::unique_ptr<CffCharset> charset;

    public:

        CffTopDict(
            std::unordered_map<CffOperatorType, std::vector<CffObject>>&& objects,
            std::unique_ptr<CffCharset>&& charset)
            : objects(std::move(objects))
            , charset(std::move(charset))
        {
        }

    public:

        CffFontMatrix GetFontMatrix() const
        {
            auto pos = this->objects.find(CffOperatorType::FontMatrix);

            if (pos != this->objects.end())
            {
                auto& numbers = pos->second;

                if (numbers.size() != 6)
                {
                    throw std::runtime_error("Wrong format for font matrix: expected 6 numbers.");
                }

                return CffFontMatrix(
                    numbers[0].GetRealSafe(),
                    numbers[1].GetRealSafe(),
                    numbers[2].GetRealSafe(),
                    numbers[3].GetRealSafe(),
                    numbers[4].GetRealSafe(),
                    numbers[5].GetRealSafe());
            }
            else
            {
                return CffFontMatrix(0.001, 0.0, 0.0, 0.001, 0.0, 0.0);
            }
        }

        CffBoundBox GetBoundBox() const
        {
            auto pos = this->objects.find(CffOperatorType::FontBBox);

            if (pos != this->objects.end())
            {
                auto& numbers = pos->second;

                if (numbers.size() != 4)
                {
                    throw std::runtime_error("Wrong format for font bbox: expected 4 numbers.");
                }

                return CffBoundBox(
                    numbers[0].GetRealSafe(),
                    numbers[1].GetRealSafe(),
                    numbers[2].GetRealSafe(),
                    numbers[3].GetRealSafe());
            }
            else
            {
                return CffBoundBox(0.0, 0.0, 0.0, 0.0);
            }
        }

        uint16_t GetWeightSid() const
        {
            auto pos = this->objects.find(CffOperatorType::Weight);
            if (pos == this->objects.end())
            {
                throw std::runtime_error("No weight record");
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for weight: expected 1 SID.");
            }

            return numbers[0].GetSidSafe();
        }

        CffCharsetType GetCharsetType() const
        {
            if (this->charset != nullptr)
            {
                return CffCharsetType::Custom;
            }
            else
            {
                auto pos = this->objects.find(CffOperatorType::Charset);
                if (pos == this->objects.end())
                {
                    return CffCharsetType::ISOAdobe;
                }

                return (CffCharsetType)pos->second[0].GetIntegerSafe();
            }
        }

        const CffCharset& GetCharset() const
        {
            assert (this->charset != nullptr);

            return *this->charset;
        }

        bool HasOperator(CffOperatorType type) const
        {
            return this->objects.count(type) > 0;
        }

        const std::vector<CffObject>& GetOperands(CffOperatorType type) const
        {
            auto pos = this->objects.find(type);

            assert (pos != this->objects.end());

            return pos->second;
        }

        const std::unordered_map<CffOperatorType, std::vector<CffObject>>& GetOperators() const
        {
            return this->objects;
        }
    };
} } }
