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
