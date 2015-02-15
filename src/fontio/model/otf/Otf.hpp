#pragma once

#include <memory>

#include <fontio/model/otf/OtfCmapTable.hpp>
#include <fontio/model/otf/OtfHeadTable.hpp>
#include <fontio/model/otf/OtfHheaTable.hpp>
#include <fontio/model/otf/OtfHmtxTable.hpp>
#include <fontio/model/otf/OtfMaxpTable.hpp>
#include <fontio/model/otf/OtfNameTable.hpp>
#include <fontio/model/otf/OtfOs2Table.hpp>
#include <fontio/model/otf/OtfPostTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class Otf
    {
    private:

        std::unique_ptr<OtfCmapTable> cmapTable;

        std::unique_ptr<OtfHeadTable> headTable;

        std::unique_ptr<OtfHheaTable> hheaTable;

        std::unique_ptr<OtfHmtxTable> hmtxTable;

        std::unique_ptr<OtfMaxpTable> maxpTable;

        std::unique_ptr<OtfNameTable> nameTable;

        std::unique_ptr<OtfOs2Table> os2Table;

        std::unique_ptr<OtfPostTable> postTable;

    public:

        void SetCmapTable(std::unique_ptr<OtfCmapTable>&& table)
        {
            this->cmapTable = std::move(table);
        }

        void SetHeadTable(std::unique_ptr<OtfHeadTable>&& table)
        {
            this->headTable = std::move(table);
        }

        void SetHheaTable(std::unique_ptr<OtfHheaTable>&& table)
        {
            this->hheaTable = std::move(table);
        }

        void SetHmtxTable(std::unique_ptr<OtfHmtxTable>&& table)
        {
            this->hmtxTable = std::move(table);
        }

        void SetMaxpTable(std::unique_ptr<OtfMaxpTable>&& table)
        {
            this->maxpTable = std::move(table);
        }

        void SetNameTable(std::unique_ptr<OtfNameTable>&& table)
        {
            this->nameTable = std::move(table);
        }

        void SetOs2Table( std::unique_ptr<OtfOs2Table>&& table)
        {
            this->os2Table = std::move(table);
        }

        void SetPostTable(std::unique_ptr<OtfPostTable>&& table)
        {
            this->postTable = std::move(table);
        }

    };
} } }
