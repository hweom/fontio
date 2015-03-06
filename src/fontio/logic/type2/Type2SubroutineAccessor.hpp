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

#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model::type2;

    class Type2SubroutineAccessor
    {
    private:

        const std::vector<Type2Charstring>* subroutines = nullptr;

    public:

        Type2SubroutineAccessor()
        {
        }

        Type2SubroutineAccessor(const std::vector<Type2Charstring>& subroutines)
            : subroutines(&subroutines)
        {
        }

    public:

        const Type2Charstring& operator [] (int index) const
        {
            if (this->subroutines == nullptr)
            {
                throw std::runtime_error("No subroutines");
            }

            auto unbiased = this->UnbiasIndex(index);
            if ((unbiased < 0) || (unbiased >= static_cast<int>(this->subroutines->size())))
            {
                throw std::runtime_error("Index out of range");
            }

            return this->subroutines->at(static_cast<size_t>(unbiased));
        }

    private:

        int UnbiasIndex(int index) const
        {
            return this->GetBias() + index;
        }

        int GetBias() const
        {
            if (this->subroutines == nullptr)
            {
                return 0;
            }
            else if (this->subroutines->size() < 1240)
            {
                return 107;
            }
            else if (this->subroutines->size() < 33900)
            {
                return 1131;
            }
            else
            {
                return 32768;
            }
        }
    };
} } }
