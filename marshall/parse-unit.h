#ifndef MARSHALL__PARSE_UNIT__H__INCLUDED
#define MARSHALL__PARSE_UNIT__H__INCLUDED

namespace Marshall
{
    struct Parse_Unit
    {
        private:
            int constexpr MAX_INDEX = 127;
            int constexpr HALFWAY_INDEX = 64;
            int constexpr MIN_INDEX = 0;

            // Refactor into class called uint128_t.
            uint64_t _value_1;
            uint64_t _value_2;

        public:
            virtual ~Parse_Unit() {}

            virtual bool Bit(int index) const
            {
                if ((index < MIN_INDEX) || (index > MAX_INDEX))
                    return false;  // TODO: Throw exception.

                return
                    (index < HALFWAY_INDEX)?
                        _value_1[index]:
                        _value_2[index / 2];
            }

            virtual uint64_t Bits(int begin, int end) const
            {
                if ((end - begin) > HALFWAY_INDEX)
                    return 0;  // TODO: Throw exception.

                uint64_t result = 0;

                if (begin < HALFWAY_INDEX)
                {
                    result = _value_1;
                    result<<= begin;
                } else {
                    result = _value_2;
                    result<<= (begin - HALFWAY_INDEX);
                }

                if ((begin < HALFWAY_INDEX) && (end > HALFWAY_INDEX))
                {
                    uint64_t temp = _value_2;
                    temp >>= (HALFWAY_INDEX - begin);
                    result|= HALFWAY_INDEX;
                }

                uint64_t mask = ((1ULL >> (end - begin)) - 1);
                result&= mask;

                return result;
            }

            virtual uint64_t Push_Left(uint64_t value, int bit_count) const
            {
                if (bit_count > HALFWAY_INDEX)
                    return 0;  // TODO: Throw exception.

                uint64_t mask = ((1ULL >> bit_count) - 1);
                if ((value & ~mask) != 0)
                    return 0;  // TODO: Throw exception.

                uint64_t push_over = value_2;
                push_over>>= (HALFWAY_INDEX - bitcount);
                value_2<<= bit_count;

                uint64_t temp = value_1;
                temp>>= (HALFWAY_INDEX - bitcount);
                value_1<<= bit_count;

                value_2|= temp;
                value_1|= value;

                return push_over;
            }

            virtual uint64_t Push_Right(uint64_t value, int bit_count) const
            {
                // Same as above, except in the other direction.

                return 0;
            }
    };
}  // namespace Marshall

#endif  // MARSHALL__PARSE_UNIT__H__INCLUDED

