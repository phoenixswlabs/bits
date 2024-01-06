#ifndef BIT_BASE_H
#define BIT_BASE_H

//!
//! \file bit_base.h
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

#include <cstdint>
#include <sys/types.h>

//lint --e{714}
namespace bit
{
//--------------------------- Public constants ---------------------------------

enum Parity
{
    Even = 0,
    Odd
};

/**
 * \brief U04 bit count
 */
const std::size_t U04_BIT_COUNT = 4UL;

//!
//! \brief uint8_t bit count
//!
const std::size_t U08_BIT_COUNT = 8UL;

//!
//! \brief uint16_t bit count
//!
const std::size_t U16_BIT_COUNT = 16UL;

//!
//! \brief uint32_t bit count
//!
const std::size_t U32_BIT_COUNT = 32UL;

//!
//! \brief U04 bit mask
//!
const uint8_t U04_BIT_MASK   = 0x0FU;

//!
//! \brief uint8_t bit mask
//!
const uint16_t U08_BIT_MASK   = 0x00FFU;

//!
//! \brief uint16_t bit mask
//!
const uint32_t U16_BIT_MASK  = 0x0000FFFFUL;

//--------------------------- Public methods -----------------------------------

//!
//! \brief Returns the two's complement of the input data
//!
//! \param data The input data
//!
//! \return uint32_t The two's complement
//!
uint32_t twosComplement(const uint32_t data);

//!
//! \brief Returns the consecutive zero bits (trailing) on the right
//!
//! \param data The data containing one or more bits set
//!
//! \return std::ssize_t The lsb set position (0-31), -1 if no bit set
//!
//! \abstract   This method count the consecutive zero bits (trailing) on the
//!             right with multiply and lookup based on deBrujn sequences
//!
ssize_t lsbPos(const uint32_t data);

//!
//! \brief Reflects the bits of the uint8_t data
//!
//! \param data The data to be reflected
//!
//! \return uint8_t  The reflected data
//!
uint8_t reflect(const uint8_t data);

//!
//! \brief Reflects the bits of the uint16_t data
//!
//! \param data     The data to be reflected
//! \param lsbFirst If set each byte is reflected but the position of the bytes
//!                 is not affected
//!
//! \return uint16_t  The reflected data
//!
uint16_t reflect(const uint16_t data, const bool isLsbFirst);

//!
//! \brief Reflects the bits of the uint32_t data
//!
//! \param data     The data to be reflected
//! \param lsbFirst If set each byte is reflected but the position of the bytes
//!                 is not affected
//!
//! \return uint16_t  The reflected data
//!
uint32_t reflect(const uint32_t data, const bool isLsbFirst);

//!
//! \brief Calculates the parity of the given 32-bit fixed-width integer
//!
//! \param data     The 32-bit fixed-width integer
//! \param parity   The parity type
//!
//! \return uint8_t The parity of the data
//!
uint8_t parity(const uint32_t data, Parity parity);

//!
//! \brief Converts a pair of nibbles to an unsigned 8-bit fixed-width integer
//!
//! \param u4_1 Most significant nibble
//! \param u4_0 Least significant nibble
//!
//! \return uint8_t  The converted 8-bit unsigned integer
//!
inline uint8_t toU08(const uint8_t u4_1, const uint8_t u4_0)
{
    const uint8_t result =
            ((static_cast<uint8_t>((u4_1 & U04_BIT_MASK) << U04_BIT_COUNT)) |
             (static_cast<uint8_t>((u4_0 & U04_BIT_MASK))));

    return result;
}

//!
//! \brief Extracts the most significant nibble from an uint8_t
//!
//! \param u08_0 The uint8_t data
//!
//! \return uint8_t  The extracted data
//!
inline uint8_t u08ToU4H(const uint8_t u08_0)
{
    const uint8_t result = u08_0 >> U04_BIT_COUNT;

    return result;
}

//!
//! \brief Extracts the least significant U4 from an uint8_t
//!
//! \param u08_0 The uint8_t data
//!
//! \return uint8_t  The extracted data
//!
inline uint8_t u08ToU4L(const uint8_t u08_0)
{
    const uint8_t result = u08_0 & U04_BIT_MASK;

    return result;
}

//!
//! \brief Converts two uint8_t to uint16_t
//!
//! \param u08_1 Most significant uint8_t
//! \param u08_0 Least significant uint8_t
//!
//! \return uint16_t The converted data
//!
inline uint16_t toU16(const uint8_t u08_1, const uint8_t u08_0)
{
    const uint16_t result =
            ((static_cast<uint16_t>(static_cast<uint32_t>(u08_1) << U08_BIT_COUNT)) |
             (static_cast<uint16_t>(u08_0)));

    return result;
}

//!
//! \brief Extracts the most significant uint8_t from an uint16_t
//!
//! \param u16_0    The uint16_t data
//!
//! \return uint8_t  The extracted data
//!
inline uint8_t u16ToU08H(const uint16_t u16_0)
{
    const uint8_t result =
            static_cast<uint8_t>(static_cast<uint32_t>(u16_0) >> U08_BIT_COUNT);

    return result;
}

//!
//! \brief Extracts the least significant uint8_t from an uint16_t
//!
//! \param u16_0    The uint16_t data
//!
//! \return uint8_t  The extracted data
//!
inline uint8_t u16ToU08L(const uint16_t u16_0)
{
    const uint8_t result = static_cast<uint8_t>(u16_0 & U08_BIT_MASK);

    return result;
}

//!
//! \brief Converts a 16-bit fixed-width integer to an array
//!
//! \param u16_0    The 16 bit integer data
//!
inline void u16ToArray(const uint16_t u16_0, uint8_t (&data)[sizeof(uint16_t)])
{
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    data[0] = u16ToU08H(u16_0);
    data[1] = u16ToU08L(u16_0);

#else

    data[0] = u16ToU08L(u16_0);
    data[1] = u16ToU08H(u16_0);

#endif
}

//!
//! \brief Converts an array to a 16-bit fixed-width integer
//!
//! \return uint16_t The 16 bit integer
//!
inline uint16_t arrayToU16(uint8_t (&data)[sizeof(uint16_t)])
{
    uint16_t result;

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    result = toU16(data[0], data[1]);

#else

    result = toU16(data[1], data[0]);

#endif

    return result;
}

//!
//! \brief Converts two uint16_t to a uint32_t
//!
//! \param u16_1    The most significant uint16_t
//! \param u16_0    The least significant uint16_t
//!
//! \return uint32_t The converted data
//!
inline uint32_t toU32(const uint16_t u16_1, const uint16_t u16_0)
{
    const uint32_t result = (static_cast<uint32_t>(u16_1) << U16_BIT_COUNT) |
                        static_cast<uint32_t>(u16_0);

    return result;
}

//!
//! \brief Converts four uint8_t to a uint32_t
//!
//! \param u08_3 The most significant uint8_t of the most significant uint16_t
//! \param u08_2 The least significant uint8_t of the most significant uint16_t
//! \param u08_1 The most significant uint8_t of the least significant uint16_t
//! \param u08_0 The least significant uint8_t of the least significant uint16_t
//!
//! \return uint32_t The converted data
//!
inline uint32_t toU32(const uint8_t u08_3,
                 const uint8_t u08_2,
                 const uint8_t u08_1,
                 const uint8_t u08_0)
{
    const uint32_t result =
            ((static_cast<uint32_t>(u08_3) << (U16_BIT_COUNT + U08_BIT_COUNT)) |
             (static_cast<uint32_t>(u08_2) <<  U16_BIT_COUNT) |
             (static_cast<uint32_t>(u08_1) <<  U08_BIT_COUNT) |
             (static_cast<uint32_t>(u08_0)));

    return result;
}

//!
//! \brief Extracts the most significant uint16_t from a uint32_t
//!
//! \param u32_0    The uint32_t data
//!
//! \return uint16_t The extracted data
//!
inline uint16_t u32ToU16H(const uint32_t u32_0)
{
    const uint16_t result = static_cast<uint16_t>(u32_0 >> U16_BIT_COUNT);

    return result;
}

//!
//! \brief Extracts the least significant uint16_t from a uint32_t
//!
//! \param u32_0    The uint32_t data
//!
//! \return uint16_t The extracted data
//!
inline uint16_t u32ToU16L(const uint32_t u32_0)
{
    const uint16_t result = static_cast<uint16_t>(u32_0 & U16_BIT_MASK);

    return result;
}

//!
//! \brief Converts a 32-bit fixed-width integer to an array
//!
//! \param u32_0    The 32 bit integer data
//!
inline void u32ToArray(const uint32_t u32_0, uint8_t (&data)[sizeof(uint32_t)])
{
    const uint16_t w0 = u32ToU16L(u32_0);
    const uint16_t w1 = u32ToU16H(u32_0);

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    data[0] = u16ToU08H(w1);
    data[1] = u16ToU08L(w1);
    data[2] = u16ToU08H(w0);
    data[3] = u16ToU08L(w0);

#else

    //! \todo Implement big endian

#endif
}

//!
//! \brief Converts an array to a 32-bit fixed-width integer
//!
//! \return uint32_t The 32 bit integer
//!
inline uint32_t arrayToU32(uint8_t (&data)[sizeof(uint32_t)])
{
    uint32_t result;

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    result = toU32(data[0], data[1], data[2], data[3]);

#else

    //! \todo Implement big endian

#endif

    return result;
}
}
#endif
