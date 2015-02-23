#pragma once

#include <memory>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class Otf
    {
    private:

        std::vector<std::unique_ptr<IOtfTable>> tables;

    public:

        Otf(std::vector<std::unique_ptr<IOtfTable>>&& tables)
            : tables(std::move(tables))
        {
        }
    };
} } }
