#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

namespace OpenFlow
{
    namespace {
        ushort Flip(ushort value)
        {
            return (ushort)((value >> 8) | ((value & 0xff) << 8));
        }


        uint Flip(uint value)
        {
            return ((value >> 24)
                | ((value & 0xff0000) >> 8)
                | ((value & 0xff00) << 8)
                | ((value & 0xff) << 24));
        }

        ulong Flip(ulong value)
        {
            return ((value >> 56)
                | ((value & 0xff000000000000L) >> 40)
                | ((value & 0xff0000000000L) >> 24)
                | ((value & 0xff00000000L) >> 8)
                | ((value & 0xff000000L) << 8)
                | ((value & 0xff0000L) << 24)
                | ((value & 0xff00L) << 40)
                | ((value & 0xff) << 56));
        }

        template <class T>
        void write(std::ostream& os, const T& value)
        {
            os.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        template <class T>
        void read(std::istream& is, T& value)
        {
            is.read(reinterpret_cast<char*>(&value), sizeof(value));
        }
    }

}


#endif // UTIL_H_INCLUDED
