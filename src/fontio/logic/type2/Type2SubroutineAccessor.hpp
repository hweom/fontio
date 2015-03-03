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
            if ((unbiased < 0) || (unbiased >= this->subroutines->size()))
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
