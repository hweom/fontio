#pragma once

#include <ostream>

namespace fontio { namespace infrastructure
{
    struct BigEndian
    {
    };

    struct LittleEndian
    {
    };

    namespace details
    {
        template<typename Endianness, typename T, typename Enable = void>
        struct WriteBytesImpl
        {
            void operator () (std::ostream& out, T value)
            {
                static_assert(sizeof(T) != 0, "Not implemented");
            }

            template<typename F>
            void operator () (std::ostream& out, T value, F func)
            {
                static_assert(sizeof(T) != 0, "Not implemented");
            }
        };

        template<typename T>
        struct WriteBytesImpl<BigEndian, T, typename std::enable_if<std::is_integral<T>::value, void>::type>
        {
            void operator () (std::ostream& out, T value)
            {
                for (size_t i = 0; i < sizeof(T); i++)
                {
                    out.put(*reinterpret_cast<const std::ostream::char_type*>(&value));

                    value <<= 8;
                }
            }

            template<typename F>
            void operator () (std::ostream& out, T value, F func)
            {
                for (size_t i = 0; i < sizeof(T); i++)
                {
                    uint8_t byte = *reinterpret_cast<const uint8_t*>(&value);

                    func(byte);

                    out.put(static_cast<std::ostream::char_type>(byte));

                    value <<= 8;
                }
            }
        };
    }

    template<typename Endianness, typename T>
    inline void WriteBytes(std::ostream& out, T value)
    {
        return details::WriteBytesImpl<Endianness, T, void>()(out, value);
    }

    template<typename Endianness, typename T, typename F>
    inline void WriteBytes(std::ostream& out, T value, F func)
    {
        return details::WriteBytesImpl<Endianness, T, F>()(out, value, func);
    }
} }
