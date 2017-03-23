#ifndef INT128_H__INCLUDED
#define INT128_H__INCLUDED

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
        uint128_t(uint64_t low = 0, uint64_t high = 0):
            _low(low),
            _high(high)
        {}

        uint128_t(uint128_t const& that):
            uint128_t(that._low, that._high)
        {}

        uint128_t& operator=(uint64_t const&& that)
        {
            _low = that;
            _high = 0;

            return (*this);
        }

        uint64_t high() const
        {
            return _high;
        }

        uint64_t low() const
        {
            return _low;
        }

        uint128_t operator++()
        {
            uint128_t result = (*this);

            ++(*this);

            return result;
        }

        uint128_t& operator++(int)
        {
            ++_low;

            if (_low == 0)
                ++_high;

            return (*this);
        }

        uint128_t operator--()
        {
            uint128_t result = (*this);

            --(*this);

            return result;
        }

        uint128_t& operator--(int)
        {
            if (_low == 0)
                --_high;

            --_low;

            return (*this);
        }

        uint128_t& operator+=(uint128_t const& that)
        {
            uint64_t low_sum = _low + that._low;
            uint64_t carry = ((low_sum < _low) && (low_sum < _low))? 1: 0;
            _low = low_sum;
            _high+= that._high + carry;

            return (*this);
        }

        uint128_t operator+(uint128_t const& that) const
        {
            return (uint128_t(*this)+= that);
        }

        uint128_t operator+() const
        {
            return (*this);
        }

        uint128_t& operator-=(uint128_t const& that)
        {
            return operator+=(-that);
        }

        uint128_t operator-(uint128_t const& that) const
        {
            return (uint128_t(*this)-= that);
        }

        uint128_t operator-() const
        {
            return uint128_t(-_low, -_high);
        }

        uint128_t& operator*=(uint128_t const& that)
        {
            uint128_t p1 = (*this) * that._low;
            uint128_t p2 = (*this) * that._high;

            (*this) = p1 + (p2 << 64);

            return (*this);
        }

        uint128_t operator*(uint128_t const& that) const
        {
            return (uint128_t(*this)*= that);
        }

        uint128_t& operator*=(uint64_t const& that)
        {
            uint128_t p1 = (*this) * uint32_t(that);
            uint128_t p2 = (*this) * uint32_t(that >> 32);

            (*this) = p1 + (p2 << 32);

            return (*this);
        }

        uint128_t operator*(uint64_t const& that) const
        {
            return (uint128_t(*this)*= that);
        }

        uint128_t& operator*=(uint32_t const& that)
        {
            uint64_t p1 = uint32_t(_low  >>  0) * that;
            uint64_t p2 = uint32_t(_low  >> 32) * that;
            uint64_t p3 = uint32_t(_high >>  0) * that;
            uint64_t p4 = uint32_t(_high >> 32) * that;

            _low = p1 + (p2 << 32);
            _high = (p2 >> 32) + p3 + (p4 << 32);

            return (*this);
        }

        uint128_t operator*(uint32_t const& that) const
        {
            return (uint128_t(*this)*= that);
        }

        uint128_t& operator<<=(int count)
        {
            if (count < 64)
            {
                uint64_t spillover = (_low >> (64 - count));

                _high<<= count;
                _high|= spillover;

                _low<<= count;
            } else {
                _high = (_low << (count - 64));
                _low = 0;
            }

            return (*this);
        }

        uint128_t operator<<(int count) const
        {
            return (uint128_t(*this)<<= count);
        }

        uint128_t& operator>>=(int count)
        {
            if (count < 64)
            {
                uint64_t spillover = (_high << (64 - count));

                _low>>= count;
                _low|= spillover;

                _high<<= count;
            } else {
                _low = (_high >> (count - 64));
                _high = 0;
            }

            return (*this);
        }

        uint128_t operator>>(int count) const
        {
            return (uint128_t(*this)>>= count);
        }

        uint128_t& operator&=(uint128_t const& mask)
        {
            _high&= mask._high;
            _low&= mask._low;

            return (*this);
        }

        uint128_t& operator|=(uint128_t const& mask)
        {
            _high|= mask._high;
            _low|= mask._low;

            return (*this);
        }

        uint128_t operator&(uint128_t const& mask) const
        {
            return (uint128_t(*this)&= mask);
        }

        uint128_t operator|(uint128_t const& mask) const
        {
            return (uint128_t(*this)|= mask);
        }

        uint128_t operatorˆ(uint128_t const& mask) const
        {
            return (uint128_t(low() ^ mask.low(), high() ^ mask.high()));
        }

        uint128_t operator~() const
        {
            return uint128_t(~_low, ~_high);
        }

        explicit operator bool() const
        {
            return (bool(_low) || bool(_high));
        }

        explicit operator uint64_t() const
        {
            return _low;
        }

        explicit operator uint32_t() const
        {
            return _low;
        }

        explicit operator uint16_t() const
        {
            return uint16_t(_low);
        }

        explicit operator uint8_t() const
        {
            return uint8_t(_low);
        }
};

#endif  // INT128_H__INCLUDED

