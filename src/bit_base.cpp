//!
//! \file bit_base.cpp
//!
//! \brief Bit manipulation library
//!
//! \details
//!
//! \author Carlos Garcia
//!
//! \copyright Phoenix Software Labs 2019
//!
//! The copyright of the computer program(s) herein is the property of
//! Phoenix Software Labs. The program(s) may be copied and used only with the
//! written consent of Phoenix Software Labs
//!
//!                       REUSE CODE, DO NOT MODIFY!
//!
//! \warning    MISRA C++ Rule 0-1-3
//!             external symbol '...' was defined but not referenced
//!
//! \note       This is a generic library and some functions are unused in some
//!             projects
//!
//! \version 1.0.0a
//!

//---------------------------- Include files -----------------------------------

#include "bit_base.h"

//lint --e{714}

namespace bit
{
const uint8_t parityTable[] =
{
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    0U, 1U, 1U, 0U, 1U, 0U, 0U, 1U,
    1U, 0U, 0U, 1U, 0U, 1U, 1U, 0U
};

//!
//! \brief Pre-calculated bit reversed table
//!
const uint8_t reflectBitTable[] =
{
    0x00U, 0x80U, 0x40U, 0xC0U, 0x20U, 0xA0U, 0x60U, 0xE0U,
    0x10U, 0x90U, 0x50U, 0xD0U, 0x30U, 0xB0U, 0x70U, 0xF0U,
    0x08U, 0x88U, 0x48U, 0xC8U, 0x28U, 0xA8U, 0x68U, 0xE8U,
    0x18U, 0x98U, 0x58U, 0xD8U, 0x38U, 0xB8U, 0x78U, 0xF8U,
    0x04U, 0x84U, 0x44U, 0xC4U, 0x24U, 0xA4U, 0x64U, 0xE4U,
    0x14U, 0x94U, 0x54U, 0xD4U, 0x34U, 0xB4U, 0x74U, 0xF4U,
    0x0CU, 0x8CU, 0x4CU, 0xCCU, 0x2CU, 0xACU, 0x6CU, 0xECU,
    0x1CU, 0x9CU, 0x5CU, 0xDCU, 0x3CU, 0xBCU, 0x7CU, 0xFCU,
    0x02U, 0x82U, 0x42U, 0xC2U, 0x22U, 0xA2U, 0x62U, 0xE2U,
    0x12U, 0x92U, 0x52U, 0xD2U, 0x32U, 0xB2U, 0x72U, 0xF2U,
    0x0AU, 0x8AU, 0x4AU, 0xCAU, 0x2AU, 0xAAU, 0x6AU, 0xEAU,
    0x1AU, 0x9AU, 0x5AU, 0xDAU, 0x3AU, 0xBAU, 0x7AU, 0xFAU,
    0x06U, 0x86U, 0x46U, 0xC6U, 0x26U, 0xA6U, 0x66U, 0xE6U,
    0x16U, 0x96U, 0x56U, 0xD6U, 0x36U, 0xB6U, 0x76U, 0xF6U,
    0x0EU, 0x8EU, 0x4EU, 0xCEU, 0x2EU, 0xAEU, 0x6EU, 0xEEU,
    0x1EU, 0x9EU, 0x5EU, 0xDEU, 0x3EU, 0xBEU, 0x7EU, 0xFEU,
    0x01U, 0x81U, 0x41U, 0xC1U, 0x21U, 0xA1U, 0x61U, 0xE1U,
    0x11U, 0x91U, 0x51U, 0xD1U, 0x31U, 0xB1U, 0x71U, 0xF1U,
    0x09U, 0x89U, 0x49U, 0xC9U, 0x29U, 0xA9U, 0x69U, 0xE9U,
    0x19U, 0x99U, 0x59U, 0xD9U, 0x39U, 0xB9U, 0x79U, 0xF9U,
    0x05U, 0x85U, 0x45U, 0xC5U, 0x25U, 0xA5U, 0x65U, 0xE5U,
    0x15U, 0x95U, 0x55U, 0xD5U, 0x35U, 0xB5U, 0x75U, 0xF5U,
    0x0DU, 0x8DU, 0x4DU, 0xCDU, 0x2DU, 0xADU, 0x6DU, 0xEDU,
    0x1DU, 0x9DU, 0x5DU, 0xDDU, 0x3DU, 0xBDU, 0x7DU, 0xFDU,
    0x03U, 0x83U, 0x43U, 0xC3U, 0x23U, 0xA3U, 0x63U, 0xE3U,
    0x13U, 0x93U, 0x53U, 0xD3U, 0x33U, 0xB3U, 0x73U, 0xF3U,
    0x0BU, 0x8BU, 0x4BU, 0xCBU, 0x2BU, 0xABU, 0x6BU, 0xEBU,
    0x1BU, 0x9BU, 0x5BU, 0xDBU, 0x3BU, 0xBBU, 0x7BU, 0xFBU,
    0x07U, 0x87U, 0x47U, 0xC7U, 0x27U, 0xA7U, 0x67U, 0xE7U,
    0x17U, 0x97U, 0x57U, 0xD7U, 0x37U, 0xB7U, 0x77U, 0xF7U,
    0x0FU, 0x8FU, 0x4FU, 0xCFU, 0x2FU, 0xAFU, 0x6FU, 0xEFU,
    0x1FU, 0x9FU, 0x5FU, 0xDFU, 0x3FU, 0xBFU, 0x7FU, 0xFFU
};

//------------------------ Public member methods -------------------------------

//------------------------------------------------------------------------------
uint32_t twosComplement(const uint32_t data)
{
    return static_cast<uint32_t>(~static_cast<uint32_t>(data)) + static_cast<uint32_t>(1UL);
}

//------------------------------------------------------------------------------
ssize_t lsbPos(const uint32_t data)
{
    ssize_t result = -1;

    if (data != 0UL)
    {
        static const ssize_t deBruijnBitPositionTable[] =
        {
             0L,  1L, 28L,  2L, 29L, 14L, 24L, 3L,
            30L, 22L, 20L, 15L, 25L, 17L,  4L, 8L,
            31L, 27L, 13L, 23L, 21L, 19L, 16L, 7L,
            26L, 12L, 18L,  6L, 11L,  5L, 10L, 9L
        };

        /*
         * Produces a unique pattern of bits into the high 5 bits for
         * each possible bit position that it is multiplied against
         */
        const uint32_t deBruijnSeq = 0x077CB531UL;

        const uint32_t lsb = data & twosComplement(data);

        const uint32_t index = (lsb * deBruijnSeq) >> 27UL;

        result = deBruijnBitPositionTable[index];
    }

    return result;
}

//------------------------------------------------------------------------------
uint8_t reflect(const uint8_t data)
{
    return reflectBitTable[data];
}

//------------------------------------------------------------------------------
uint16_t reflect(const uint16_t data, const bool isLsbFirst)
{
    const uint8_t b0 = u16ToU08L(data);
    const uint8_t b1 = u16ToU08H(data);

    uint16_t result;

    if (isLsbFirst)
    {
        result = toU16(reflectBitTable[b1],
                       reflectBitTable[b0]);
    }
    else
    {
        result = toU16(reflectBitTable[b0],
                       reflectBitTable[b1]);
    }

    return result;
}

//------------------------------------------------------------------------------
uint32_t reflect(const uint32_t data, const bool isLsbFirst)
{
    const uint16_t w0 = u32ToU16L(data);
    const uint16_t w1 = u32ToU16H(data);

    const uint8_t b0 = u16ToU08L(w0);
    const uint8_t b1 = u16ToU08H(w0);
    const uint8_t b2 = u16ToU08L(w1);
    const uint8_t b3 = u16ToU08H(w1);

    uint32_t result;

    if (isLsbFirst)
    {
        result = toU32(reflectBitTable[b3],
                       reflectBitTable[b2],
                       reflectBitTable[b1],
                       reflectBitTable[b0]);
    }
    else
    {
        result = toU32(reflectBitTable[b0],
                       reflectBitTable[b1],
                       reflectBitTable[b2],
                       reflectBitTable[b3]);
    }

    return result;
}

//------------------------------------------------------------------------------
uint8_t parity(const uint32_t data, Parity parity)
{
    uint8_t b[sizeof(uint32_t)];

    u32ToArray(data, b);

    const uint8_t result =
            parityTable[b[3]] ^
            parityTable[b[2]] ^
            parityTable[b[1]] ^
            parityTable[b[0]];

    return result ^ static_cast<uint8_t>(parity);
}
}
