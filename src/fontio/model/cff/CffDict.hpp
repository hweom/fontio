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

            const auto& numbers = pos->second;

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

            const auto& numbers = pos->second;

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

            const auto& numbers = pos->second;

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

            const auto& numbers = pos->second;

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

            const auto& numbers = pos->second;

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

            const auto& numbers = pos->second;

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
