#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <bits>

using namespace testing;

namespace
{
struct U16TestStruct
{
    u16 data;
    u16 result;
};

struct U32TestStruct
{
    u32 data;
    u32 result;
};

//------------------------------------------------------------------------------
u08 reflect(u08 data)
{
    u32 r = data; // r will be reversed bits of v; first get LSB of v
    int s = sizeof(data) * CHAR_BIT - 1; // extra shift needed at end

    for (data >>= 1; data; data >>= 1)
    {
        r <<= 1;
        r |= data & 1;
        s--;
    }

    r <<= s; // shift when v's highest bits are zero

    return static_cast<u08>(r);
}
}

//------------------------------------------------------------------------------
class BitBase : public Test
{
public:

    BitBase();

    virtual void SetUp();
};

//------------------------------------------------------------------------------
BitBase::BitBase()
{
}

//------------------------------------------------------------------------------
void BitBase::SetUp()
{
}

//------------------------------------------------------------------------------
TEST_F(BitBase, lsbPosition)
{
    u32 data = 774355515UL; // b101110001001111011101000111011

    // Represent the bit set in that position
    const std::ssize_t table[]
    {
         0L,  1L, -1L,  3L,  4L,  5L, -1L, -1L,
        -1L,  9L, -1L, 11L, 12L, 13L, -1L, 15L,
        16L, 17L, 18L, -1L, -1L, 21L, -1L, -1L,
        -1L, 25L, 26L, 27L, -1L, 29L, -1L, -1L
    };

    while (data != 0UL)
    {
        std::ssize_t result = bit::lsbPos(data);

        ASSERT_TRUE(result != -1L);

        ASSERT_EQ(result, table[result]);

        data &= ~(1UL << result);
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, reflectU08)
{
    for (u16 i = 0UL; i <= UCHAR_MAX; i++)
    {
        ASSERT_EQ(bit::reflect(static_cast<u08>(i)),
                  reflect(static_cast<u08>(i)));
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, reflectU16)
{
    const U16TestStruct reflectDataNormal[] =
    {
        { 0x0001U, 0x8000U },
        { 0x0002U, 0x4000U },
        { 0x0003U, 0xC000U },
        { 0xC000U, 0x0003U },
        { 0x4000U, 0x0002U },
        { 0x8000U, 0x0001U },
        { 0x0010U, 0x0800U },
        { 0x0020U, 0x0400U },
        { 0x0030U, 0x0C00U }
    };

    for (auto& input : reflectDataNormal)
    {
        ASSERT_EQ(bit::reflect(input.data, false), input.result);
    }

    const U16TestStruct reflectDataLsb[] =
    {
        { 0x0001U, 0x0080U },
        { 0x0002U, 0x0040U },
        { 0x0003U, 0x00C0U },
        { 0xC000U, 0x0300U },
        { 0x4000U, 0x0200U },
        { 0x8000U, 0x0100U }
    };

    for (auto& input : reflectDataLsb)
    {
        ASSERT_EQ(bit::reflect(input.data, true), input.result);
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, reflectU32)
{
    const U32TestStruct reflectDataNormal[] =
    {
        { 0x00000001UL, 0x80000000UL },
        { 0x00000002UL, 0x40000000UL },
        { 0x00000003UL, 0xC0000000UL },
        { 0x0000C000UL, 0x00030000UL },
        { 0x00004000UL, 0x00020000UL },
        { 0x00008000UL, 0x00010000UL },
        { 0x00000010UL, 0x08000000UL },
        { 0x00000020UL, 0x04000000UL },
        { 0x00000030UL, 0x0C000000UL }
    };

    for (auto& input : reflectDataNormal)
    {
        ASSERT_EQ(bit::reflect(input.data, false), input.result);
    }

    const U32TestStruct reflectDataLsb[] =
    {
        { 0x00000001UL, 0x00000080UL },
        { 0x00000002UL, 0x00000040UL },
        { 0x00000003UL, 0x000000C0UL },
        { 0x0000C000UL, 0x00000300UL },
        { 0x00004000UL, 0x00000200UL },
        { 0x00008000UL, 0x00000100UL }
    };

    for (auto& input : reflectDataLsb)
    {
        ASSERT_EQ(bit::reflect(input.data, true), input.result);
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, u08Convert)
{
    struct TestStruct
    {
        u08 b0;
        u08 n0;
        u08 n1;
    };

    const TestStruct testData[] =
    {
        { 0x5AU, 0x0AU, 0x05U },
        { 0x3CU, 0x0CU, 0x03U },
        { 0x92U, 0x02U, 0x09U },
        { 0x71U, 0x01U, 0x07U }
    };

    for (auto& data : testData)
    {
        ASSERT_EQ(bit::u08ToU4L(data.b0), data.n0);
        ASSERT_EQ(bit::u08ToU4H(data.b0), data.n1);

        ASSERT_EQ(bit::toU08(data.n1, data.n0), data.b0);
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, u16Convert)
{
    struct TestStruct
    {
        u16 w0;
        u08 b0;
        u08 b1;
    };

    const TestStruct testData[] =
    {
        { 0x3C5AU, 0x5AU, 0x3CU },
        { 0x9173U, 0x73U, 0x91U },
        { 0x55AAU, 0xAAU, 0x55U },
        { 0x7122U, 0x22U, 0x71U }
    };

    for (auto& data : testData)
    {
        ASSERT_EQ(bit::u16ToU08L(data.w0), data.b0);
        ASSERT_EQ(bit::u16ToU08H(data.w0), data.b1);

        ASSERT_EQ(bit::toU16(data.b1, data.b0), data.w0);
    }
}

//------------------------------------------------------------------------------
TEST_F(BitBase, u32Convert)
{
    struct TestStruct
    {
        u32 dw0;
        u16 w0;
        u16 w1;
    };

    const TestStruct testData[] =
    {
        { 0x91733C5AUL, 0x3C5AU, 0x9173U },
        { 0x55AA7122UL, 0x7122U, 0x55AAU }
    };

    for (auto& data : testData)
    {
        ASSERT_EQ(bit::u32ToU16L(data.dw0), data.w0);
        ASSERT_EQ(bit::u32ToU16H(data.dw0), data.w1);

        ASSERT_EQ(bit::toU32(data.w1, data.w0), data.dw0);
    }
}
