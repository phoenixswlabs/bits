#ifndef BIT_BUFFER_H
#define BIT_BUFFER_H

//!
//! \file bit_buffer.h
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

#include "bit_signal.h"

#include <cstring>

namespace bit
{
template <std::size_t Size>
class Buffer
{
public:

    //-------------------------- Member constants ------------------------------

    //!
    //! \brief Possible status of the bit buffer
    //!
    enum Status
    {
        Ok = 0,
        Overflow
    };

    //--------------------------- Member methods -------------------------------

    //!
    //! \brief Constructs a bit buffer object
    //!
    Buffer()
        : mOverrunData(0U)
        , mStatus(Ok)
        , mBuffer()
    {
    }

    //!
    //! \brief Destroys a bit buffer object
    //!
    ~Buffer()
    {
    }

    //!
    //! \brief Clears the bit buffer data
    //!
    void clear()
    {
        mStatus = Ok;
        mOverrunData = 0U;

        (void) std::memset(mBuffer, 0, Size);
    }

    //!
    //! \brief Returns the status of the buffer
    //!
    //! \return Status  (Ok | Overflow)
    //!
    Status status() const
    {
        return mStatus;
    }

    //!
    //! \brief Returns the byte size of the bit buffer
    //!
    //! \return std::size_t The size of the bit buffer
    //!
    std::size_t size() const
    {
        return Size;
    }

    //!
    //! \brief Extracts data from the bit buffer to a signal
    //!
    //! \param signal   The signal to write the buffer data to
    //!
    //! \return Buffer& The bit buffer instance
    //!
    //! \warning    MISRA C++ Rule 17-0-2
    //!             the name '...' is reserved to the compiler
    //!
    //! \note       The name is used in a dedicated namespace
    //!
    //lint -e{9093}
    Buffer& operator >>(SignalData& signal)
    {
        uint8_t rem = 0U;

        std::size_t i = signal.sizeInBuffer();

        do
        {
            i--;

            const std::size_t pos = i + signal.position();

            const uint8_t byte = (*this)[pos];

            if (i < signal.typeSize())
            {
                const std::size_t shiftL = signal.readLShift();

                if (0U == rem)
                {
                    signal[i] |= static_cast<uint8_t>(byte << shiftL);
                }
                else
                {
                    signal[i] |= rem;

                    signal[i] |= static_cast<uint8_t>(byte << shiftL);
                }
            }

            const std::size_t shiftR = signal.readRShift();

            if (shiftR != 0UL)
            {
                rem = static_cast<uint8_t>(byte >> shiftR);
            }

        } while (i > 0UL);

        return *this;
    }

    //!
    //! \brief Inserts data from a signal to the bit buffer
    //!
    //! \param signal   The signal to insert into the buffer
    //!
    //! \return Buffer& The bit buffer instance
    //!
    //! \warning    MISRA C++ Rule 17-0-2
    //!             the name '...' is reserved to the compiler
    //!
    //! \note       The name is used in a dedicated namespace
    //!
    //lint -e{9093}
    Buffer& operator <<(SignalData& signal)
    {
        uint8_t rem = 0U;

        std::size_t i = 0UL;

        do
        {
            uint8_t byte = 0U;

            if (i < signal.typeSize())
            {
                byte = signal[i];
            }

            const std::size_t shiftR = signal.writeRShift();

            const std::size_t pos = i + signal.position();

            if (0U == rem)
            {
                (*this)[pos] |= static_cast<uint8_t>(byte >> shiftR);
            }
            else
            {
                (*this)[pos] |= rem;

                (*this)[pos] |= static_cast<uint8_t>(byte >> shiftR);
            }

            const std::size_t shiftL = signal.writeLShift();

            if (shiftL != 0UL)
            {
                rem = static_cast<uint8_t>(byte << shiftL);
            }

            i++;

        } while (i < signal.sizeInBuffer());

         return *this;
    }

    //!
    //! \brief Array index operator
    //!
    //! \param i    The index of the array (unsigned)
    //!
    //! \return uint8_t&    Reference to the data index
    //!
    uint8_t& operator[](const std::size_t& i)
    {
        uint8_t* result = &mOverrunData;

        if (i < Size)
        {
            result = &mBuffer[i];
        }
        else
        {
            mStatus = Overflow;
        }

        return *result;
    }

private:

    //!
    //! \brief Variable to handle an out of bounds access to the mBuffer buffer
    //!
    //! \details    if there is an attempt to access the mBuffer buffer with an
    //!             index out of bounds when using operator[], then the
    //!             read/written value will be handled by this variable
    //!
    uint8_t mOverrunData;

    //!
    //! \brief Returns the current status of the buffer
    //!
    Status mStatus;

    //!
    //! \brief Contains the bit buffer data
    //!
    uint8_t mBuffer[Size];
};
}

#endif
