#ifndef BIT_SIGNAL_DATA_H
#define BIT_SIGNAL_DATA_H

//!
//! \file bit_signal_data.h
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

#include "bit_base.h"

namespace bit
{
class SignalData
{
public:

    //--------------------------- Member methods -------------------------------

    //!
    //! \brief Virtual destructor of the SignalData interface
    //!
    virtual ~SignalData();

    //!
    //! \brief Byte position of the signal in the bit buffer
    //!
    //! \return std::size_t The byte position
    //!
    virtual std::size_t position() const = 0;

    //!
    //! \brief Size in bytes the signal occupies in a bit buffer
    //!
    //! \return std::size_t The byte count
    //!
    virtual std::size_t sizeInBuffer() const = 0;

    //!
    //! \brief Size in bytes of the signal type
    //!
    //! \return std::size_t The byte count
    //!
    virtual std::size_t typeSize() const = 0;

    //!
    //! \brief Left shift applied to the signal when written to the buffer
    //!
    //! \return std::size_t The bit shift count
    //!
    virtual std::size_t writeLShift() const = 0;

    //!
    //! \brief Right shift applied to the signal when written to the buffer
    //!
    //! \return std::size_t The bit shift count
    //!
    virtual std::size_t writeRShift() const = 0;

    //!
    //! \brief Left shift applied to the signal when read from the buffer
    //!
    //! \return std::size_t The bit shift count
    //!
    virtual std::size_t readRShift() const = 0;

    //!
    //! \brief Right shift applied to the signal when read from the buffer
    //!
    //! \return std::size_t The bit shift count
    //!
    virtual std::size_t readLShift() const = 0;

    //!
    //! \brief Array index operator
    //!
    //! \param i        The index of the array (unsigned)
    //!
    //! \return u08&    Reference to the data index
    //!
    virtual uint8_t& operator[](const std::size_t& i) = 0;
};
}

#endif
