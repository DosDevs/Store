#ifndef INT128__INCLUDED
#define INT128__INCLUDED

#include <cstdint>

class uint128_t
{
    private:
#ifdef BIG_ENDIAN
        uint64_t _high;
        uint64_t _low;
#else
        uint64_t _low;
        uint64_t _high;
#endif

    public:
        uint128_t(uint128_t const& that):
            uint128_t(that._low, that._high)
        {}

        uint128_t(uint64_t low = 0, uint64_t high = 0):
            _low(low),
            _high(high)
        {}

};

#endif  // INT128__INCLUDED

