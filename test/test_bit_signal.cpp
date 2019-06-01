#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <bits>

using namespace testing;

//------------------------------------------------------------------------------
class BitSignal : public Test
{
public:

    BitSignal();

    virtual void SetUp();
};

//------------------------------------------------------------------------------
BitSignal::BitSignal()
{
}

//------------------------------------------------------------------------------
void BitSignal::SetUp()
{
}

//------------------------------------------------------------------------------
TEST_F(BitSignal, readWrite)
{
}

