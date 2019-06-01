#ifndef BIT_SIGNAL_H
#define BIT_SIGNAL_H

//!
//! \file bit_signal.h
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
//! \version 1.0.0a
//!

//---------------------------- Include files -----------------------------------

#include "bit_signal_data.h"

//!
//! \brief Returns the number of bits used by the signal type
//!
//! \warning    MISRA C++ Rule 16-0-4:
//!             function-like macro, '...', defined
//!
//! \note       This needs to be calculated by the pre-processor
//!
//! \warning    MISRA C++ Rule 16-0-6
//!             unparenthesized macro parameter '...' in definition of macro '...'
//!
//! \note       The T parameter can't be parenthesized with templates usage
//!
//lint -e9026 -e9022
#define typeBitSize(T)      ((std::is_same<T, bool>::value) ? (1UL) : (BitSize))
//lint +e9026 +e9022

#include <cstring>
#include <type_traits>

namespace bit
{
template<typename T,
         const std::size_t BitPos,
         const std::size_t BitSize = sizeof(T) * U08_BIT_COUNT>
class Signal : public SignalData
{
public:

    //--------------------------- Member methods -------------------------------

    //!
    //! \brief Constructs a bit signal object
    //!
    Signal()
        : SignalData()
        , mOverrunData(0U)
        , mData()
    {
    }

    //!
    //! \brief Destroys a bit signal object
    //!
    ~Signal()
    {
    }

    //!
    //! \brief Clears the signal data
    //!
    void clear()
    {
        mOverrunData = 0U;

        (void) std::memset(mData, 0, sizeof(T));
    }

    //!
    //! \brief Updates the value of the signal
    //!
    //! \param value    The signal value
    //!
    void write(const T& value)
    {
        write_(value);
    }

    //!
    //! \brief Reads the current value of the signal
    //!
    //! \return T   The signal value
    //!
    void read(T& value)
    {
        read_(value);
    }

private:

    //-------------------------- Member constants ------------------------------

    //!
    //! \brief Maximum representable bit position
    //!
    static const std::size_t BIT_MAX_POS = (U08_BIT_COUNT - 1UL);

    //!
    //! \brief Bit-byte offset
    //!
    static const std::size_t BIT_OFFSET = (BitPos % U08_BIT_COUNT);

    //!
    //! \brief Bytes used by the signal in the buffer
    //!
    static const std::size_t BYTE_SIZE =
            (BIT_OFFSET + typeBitSize(T) + BIT_MAX_POS) / U08_BIT_COUNT;

    //------------------------- Member variables -------------------------------

    //!
    //! \brief mData out of bounds access handle variable
    //!
    //! \details    if there is an attempt to access the mData buffer with an
    //!             index out of bounds when using operator[], then the
    //!             read/written value will be handled by this variable
    //!
    uint8_t mOverrunData;

    //!
    //! \brief Bit representation value of the signal
    //!
    uint8_t mData[sizeof(T)];

    //--------------------------- Member methods -------------------------------

    // Overriden from SignalData
    virtual std::size_t position() const
    {
        return (BitPos / U08_BIT_COUNT);
    }

    // Overriden from SignalData
    virtual std::size_t sizeInBuffer() const
    {
        return BYTE_SIZE;
    }

    // Overriden from SignalData
    virtual std::size_t typeSize() const
    {
        return sizeof(T);
    }

    // Overriden from SignalData
    virtual std::size_t writeLShift() const
    {
        return (BitPos + 1UL) % U08_BIT_COUNT;
    }

    // Overriden from SignalData
    virtual std::size_t writeRShift() const
    {
        return (U08_BIT_COUNT - writeLShift()) % U08_BIT_COUNT;
    }

    // Overriden from SignalData
    virtual std::size_t readRShift() const
    {
        return (BitPos + 1UL) % U08_BIT_COUNT;
    }

    // Overriden from SignalData
    virtual std::size_t readLShift() const
    {
        return (U08_BIT_COUNT - readRShift()) % U08_BIT_COUNT;
    }

    // Overriden from SignalData
    virtual uint8_t& operator[](const std::size_t& i)
    {
        uint8_t* result = &mOverrunData;

        if (i < sizeof(T))
        {
            result = &mData[i];
        }

        return *result;
    }

    //!
    //! \brief Shift applied to the signal based on the bit size
    //!
    //! \return std::size_t The bit shift count
    //!
    std::size_t bitMaskShift() const
    {
        return ((sizeof(T) * U08_BIT_COUNT) - BitSize);
    }

    //!
    //! \brief Helper method to write an 8-bit array
    //!
    //! \param value    The array to be written
    //!
    template<std::size_t Size>
    void write_(const uint8_t (&value)[Size])
    {
        (void) std::memcpy(mData, value, Size);
    }

    //!
    //! \brief Helper method to read an 8-bit array
    //!
    //! \param value    The array to be extracted
    //!
    template<std::size_t Size>
    void read_(uint8_t (&value)[Size])
    {
        (void) std::memcpy(value, mData, Size);
    }

    //!
    //! \brief Helper method to write a boolean flag
    //!
    //! \param value    The bool flag
    //!
    void write_(const bool& value)
    {
        mData[0] = reflect(static_cast<uint8_t>(value));
    }

    //!
    //! \brief Helper method to read a boolean flag
    //!
    //! \param value    The bool flag
    //!
    void read_(bool& value)
    {
        value = static_cast<bool>(reflect(mData[0] & 0x80U));
    }

    //!
    //! \brief Helper method to write a signed 8-bit fixed-width integer
    //!
    //! \param value    The signed 8-bit fixed-width integer
    //!
    void write_(const int8_t& value)
    {
        write_(static_cast<uint8_t>(value));
    }

    //!
    //! \brief Helper method to read a signed 8-bit fixed-width integer
    //!
    //! \param value    The signed 8-bit fixed-width integer
    //!
    void read_(int8_t& value)
    {
        read_(static_cast<uint8_t>(value));
    }

    //!
    //! \brief Helper method to write an unsigned 8-bit fixed-width integer
    //!
    //! \param value    The unsigned 8-bit fixed-width integer
    //!
    void write_(const uint8_t& value)
    {
        mData[0] = value << bitMaskShift();
    }

    //!
    //! \brief Helper method to read an unsigned 8-bit fixed-width integer
    //!
    //! \param value    The unsigned 8-bit fixed-width integer
    //!
    void read_(uint8_t& value)
    {
        value = mData[0] >> bitMaskShift();
    }

    //!
    //! \brief Helper method to write a signed 16-bit fixed-width integer
    //!
    //! \param value    The signed 16-bit fixed-width integer
    //!
    void write_(const int16_t& value)
    {
        write_(static_cast<uint16_t>(value));
    }

    //!
    //! \brief Helper method to read a signed 16-bit fixed-width integer
    //!
    //! \param value    The signed 16-bit fixed-width integer
    //!
    void read_(int16_t& value)
    {
        read_(static_cast<uint16_t>(value));
    }

    //!
    //! \brief Helper method to write an unsigned 16-bit fixed-width integer
    //!
    //! \param value    The unsigned 16-bit fixed-width integer
    //!
    void write_(const uint16_t& value)
    {
        const uint16_t data = value << bitMaskShift();

        u16ToArray(data, mData);
    }

    //!
    //! \brief Helper method to read an unsigned 16-bit fixed-width integer
    //!
    //! \param value    The unsigned 16-bit fixed-width integer
    //!
    void read_(uint16_t& value)
    {
        const uint16_t data = arrayToU16(mData);

        value = data >> bitMaskShift();
    }

    //!
    //! \brief Helper method to write a signed 32-bit fixed-width integer
    //!
    //! \param value    The signed 32-bit fixed-width integer
    //!
    void write_(const int32_t& value)
    {
        write_(static_cast<uint32_t>(value));
    }

    //!
    //! \brief Helper method to read a signed 32-bit fixed-width integer
    //!
    //! \param value    The signed 32-bit fixed-width integer
    //!
    void read_(int32_t& value)
    {
        read_(static_cast<uint32_t>(value));
    }

    //!
    //! \brief Helper method to write an unsigned 32-bit fixed-width integer
    //!
    //! \param value    The unsigned 32-bit fixed-width integer
    //!
    void write_(const uint32_t& value)
    {
        const uint32_t data = value << bitMaskShift();

        u32ToArray(data, mData);
    }

    //!
    //! \brief Helper method to read an unsigned 32-bit fixed-width integer
    //!
    //! \param value    The unsigned 32-bit fixed-width integer
    //!
    void read_(uint32_t& value)
    {
        const uint32_t data = arrayToU32(mData);

        value = data >> bitMaskShift();
    }

    //!
    //! \brief Helper method to write a single precision floating point
    //!
    //! \param value    The single precision floating point
    //!
    void write_(const float& value)
    {
        //!
        //! \warning    MISRA C++ Rule 5-2-8
        //!             explicit cast from '...' to '...'
        //!
        //! \warning    MISRA C++ Rule 3-9-3
        //!             bit representation of a floating point type used
        //!
        //! \warning    MISRA C++ Rule 5-2-7
        //!             pointer type '...' converted to unrelated pointer type
        //!
        //! \note       Bit level access is required to the floating point data
        //!             in order to write the data to the buffer
        //!
        //lint -e925 -e9110 -e9176
        const void* address = static_cast<const void*>(&value);

        const uint32_t* data = static_cast<const uint32_t*>(address);
        //lint +e925 +e9110 +e9176

        write_(*data);
    }

    //!
    //! \brief Helper method to read a single precision floating point
    //!
    //! \param value    The single precision floating point
    //!
    void read_(float& value)
    {
        //!
        //! \warning    MISRA C++ Rule 5-2-8
        //!             explicit cast from '...' to '...'
        //!
        //! \warning    MISRA C++ Rule 3-9-3
        //!             bit representation of a floating point type used
        //!
        //! \warning    MISRA C++ Rule 5-2-7
        //!             pointer type '...' converted to unrelated pointer type
        //!
        //! \note       Bit level access is required to the floating point data
        //!             in order to write the data to the buffer
        //!
        //lint -e925 -e9110 -e9176
        const void* address = static_cast<const void*>(&value);

        const uint32_t* data = static_cast<const uint32_t*>(address);
        //lint +e925 +e9110 +e9176

        read_(*data);
    }

    //!
    //! \brief Helper method to write a double precision floating point
    //!
    //! \param value    The double precision floating point
    //!
    void write_(const double& value)
    {
        //!
        //! \warning    MISRA C++ Rule 5-2-8
        //!             explicit cast from '...' to '...'
        //!
        //! \warning    MISRA C++ Rule 3-9-3
        //!             bit representation of a floating point type used
        //!
        //! \warning    MISRA C++ Rule 5-2-7
        //!             pointer type '...' converted to unrelated pointer type
        //!
        //! \note       Bit level access is required to the floating point data
        //!             in order to write the data to the buffer
        //!
        //lint -e925 -e9110 -e9176
        const void* address = static_cast<const void*>(&value);

        const uint64_t* data = static_cast<const uint64_t*>(address);
        //lint +e925 +e9110 +e9176

        (void) data;
    }

    //!
    //! \brief Helper method to read a double precision floating point
    //!
    //! \param value    The double precision floating point
    //!
    void read_(double& value)
    {
        //!
        //! \warning    MISRA C++ Rule 5-2-8
        //!             explicit cast from '...' to '...'
        //!
        //! \warning    MISRA C++ Rule 3-9-3
        //!             bit representation of a floating point type used
        //!
        //! \warning    MISRA C++ Rule 5-2-7
        //!             pointer type '...' converted to unrelated pointer type
        //!
        //! \note       Bit level access is required to the floating point data
        //!             in order to write the data to the buffer
        //!
        //lint -e925 -e9110 -e9176
        const void* address = static_cast<const void*>(&value);

        const uint64_t* data = static_cast<const uint64_t*>(address);
        //lint +e925 +e9110 +e9176

        (void) data;
    }
};
}

#endif
