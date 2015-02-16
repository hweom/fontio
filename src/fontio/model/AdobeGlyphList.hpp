#pragma once

#include <string>
#include <unordered_map>

namespace fontio { namespace model
{
    class AdobeGlyphList
    {
    public:

        uint16_t GetUnicode(const std::string& name) const
        {
            auto& nameMap = GetNameMap();

            auto pos = nameMap.find(name);

            return (pos == nameMap.end()) ? 0 : pos->second;
        }

    private:

        static std::unordered_map<std::string, uint16_t>& GetNameMap()
        {
            static std::unordered_map<std::string, uint16_t> nameMap = CreateNameMap();

            return nameMap;
        }

        static std::unordered_map<std::string, uint16_t> CreateNameMap();
    };
} }
