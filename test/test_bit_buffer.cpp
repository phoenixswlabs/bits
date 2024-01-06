#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <bits>

using namespace testing;

//------------------------------------------------------------------------------
class BitBuffer : public Test
{
public:

    BitBuffer();

    virtual void SetUp();
};

//------------------------------------------------------------------------------
BitBuffer::BitBuffer()
{
}

//------------------------------------------------------------------------------
void BitBuffer::SetUp()
{
}

//------------------------------------------------------------------------------
TEST_F(BitBuffer, readWrite)
{
}

