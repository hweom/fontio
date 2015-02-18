#pragma once

#include <vector>
#include <unordered_map>

#include <fontio/model/cff/CffObject.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffDict
    {
    private:

        std::unordered_map<CffOperatorType, std::vector<CffObject>> objects;

    public:

        CffDict(std::unordered_map<CffOperatorType, std::vector<CffObject>>&& objects)
            : objects(std::move(objects))
        {
        }

    public:

        bool HasOperator(CffOperatorType op) const
        {
            return this->objects.count(op) > 0;
        }

        int32_t GetAsInt(CffOperatorType op, int32_t defaultValue) const
        {
            auto pos = this->objects.find(op);
            if (pos == this->objects.end())
            {
                return defaultValue;
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for operator: expected 1 integer.");
            }

            return (int32_t)numbers[0].GetIntegerSafe();
        }

        uint32_t GetAsUint(CffOperatorType op) const
        {
            auto pos = this->objects.find(op);
            if (pos == this->objects.end())
            {
                throw std::runtime_error("Missing value for operator");
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for offset operator: expected 1 integer.");
            }

            return (uint32_t)numbers[0].GetIntegerSafe();
        }

        uint16_t GetAsSid(CffOperatorType op) const
        {
            auto value = this->GetAsUint(op);

            if (value > 0xFFFF)
            {
                throw std::runtime_error("Value too big for SID");
            }

            return static_cast<uint16_t>(value);
        }

        uint32_t GetAsUint(CffOperatorType op, uint32_t defaultValue) const
        {
            auto pos = this->objects.find(op);
            if (pos == this->objects.end())
            {
                return defaultValue;
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for offset operator: expected 1 integer.");
            }

            return (uint32_t)numbers[0].GetIntegerSafe();
        }

        std::pair<uint32_t, uint32_t> GetAsOffsetAndLength(CffOperatorType op) const
        {
            auto pos = this->objects.find(op);
            if (pos == this->objects.end())
            {
                throw std::runtime_error("Missing value for operator");
            }

            auto& numbers = pos->second;

            if (numbers.size() != 2)
            {
                throw std::runtime_error("Wrong format for offset and length operator: expected 2 integers.");
            }

            return std::make_pair((uint32_t)numbers[1].GetIntegerSafe(), (uint32_t)numbers[0].GetIntegerSafe());
        }

        template<typename T>
        T GetAsEnum(CffOperatorType op, T defaultValue) const
        {
            auto pos = this->objects.find(op);
            if (pos == this->objects.end())
            {
                return defaultValue;
            }

            auto& numbers = pos->second;

            if (numbers.size() != 1)
            {
                throw std::runtime_error("Wrong format for enum type: expected 1 number.");
            }

            return (T)numbers[0].GetIntegerSafe();
        }

        template<typename T, size_t N>
        std::array<T, N> GetAsArray(CffOperatorType op, const std::array<T, N>& defaultValue) const
        {
            auto pos = this->objects.find(op);

            if (pos == this->objects.end())
            {
                return defaultValue;
            }

            auto& numbers = pos->second;

            if (numbers.size() != N)
            {
                throw std::runtime_error("Operand count mismatch: expected " + std::to_string(N) + " numbers, got " + std::to_string(numbers.size()));
            }

            std::array<T, N> result;
            for (size_t i = 0; i < N; i++)
            {
                result[i] = static_cast<T>(numbers[i].GetRealSafe());
            }

            return result;
        }
    };
} } }
