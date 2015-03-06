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

namespace fontio { namespace logic { namespace type2
{
    class Type2CharstringReaderState
    {
    private:

        int hintCount = 0;

        int stackDepth = 0;

    public:

        int GetHintCount() const
        {
            return this->hintCount;
        }

        int GetStackDepth() const
        {
            return this->stackDepth;
        }

        void Reset()
        {
            this->hintCount = 0;

            this->stackDepth = 0;
        }

        void AddHintCount(int hints)
        {
            this->hintCount += hints;
        }

        void IncrementStackDepth()
        {
            this->stackDepth++;
        }

        void ChangeStackDepth(int delta)
        {
            this->stackDepth = std::max(0, this->stackDepth + delta);
        }

        void ResetStackDepth()
        {
            this->stackDepth = 0;
        }
    };
} } }
