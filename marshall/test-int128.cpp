#include "int128.h"

#include <iostream>


#define EXPECT(condition)                                           \
    if (!condition)                                                 \
    {                                                               \
        std::cerr << "Test failed: " << #condition << std::endl;    \
        return 1;                                                   \
    }                                                               \

#define EXPECT_EQ(a, b)     EXPECT((a == b))
#define EXPECT_NE(a, b)     EXPECT((a != b))
#define EXPET_NOT(c)        EXPECT((c) == false)


int main()
{
    uint128_t zero = 0;
    EXPECT_EQ(zero.low(), 0);
    EXPECT_EQ(zero.high(), 0);

    uint128_t one = 1;
    EXPECT_EQ(one.low(), 1);
    EXPECT_EQ(one.high(), 0);

    uint128_t i64 = 0xdeadbeefcafebabeULL;
    EXPECT_EQ(i64.low(), 0xdeadbeefcafebabeULL);
    EXPECT_EQ(i64.high(), 0);

    uint128_t i128(0xdeadbeefcafebabeULL, 0x0face0ff0badf00dULL);
    EXPECT_EQ(i128.low(), 0xdeadbeefcafebabeULL);
    EXPECT_EQ(i128.high(), 0x0face0ff0badf00dULL);

    i128 = uint128_t(0x1234432156788765ULL, 0x3456654378900987ULL);
    EXPECT_EQ(i128.low(), 0x1234432156788765ULL);
    EXPECT_EQ(i128.high(), 0x3456654378900987ULL);
    EXPECT_EQ(i128, i128);

    uint128_t a(0x1234432112344321ULL, 0x1234432112344321ULL);
    uint128_t b(0x3210012332100123ULL, 0x3210012332100123ULL);
    uint128_t c(0x4444444444444444ULL, 0x4444444444444444ULL);
    EXPECT_EQ(a + b, c);

    EXPECT_EQ(a >> 64, uint64_t(0x1234432112344321ULL));

    std::cout << "All tests passed.";

    return 0;
}

