// --------------------------------
// projects/c++/deque/TestDeque.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// http://www.cplusplus.com/reference/deque/deque/

// --------
// includes
// --------

#include <deque>     // deque
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#include "Deque.h"

// -----
// Using
// -----

using namespace std;

using testing::Test;
using testing::Types;

// -----
// Types
// -----

template <typename T>
struct Deque_Fixture : Test {
    using deque_type = T;
    using value_type = typename deque_type::value_type;};

typedef Types<
               deque<int>,
            my_deque<int>>
        deque_types;

TYPED_TEST_CASE(Deque_Fixture, deque_types);

// -----
// Tests
// -----

TYPED_TEST(Deque_Fixture, test_1) 
{
    using deque_type = typename TestFixture::deque_type;

    const deque_type x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(x.size(),0);
}
//deque equal test begin
TYPED_TEST(Deque_Fixture, equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	deque_type y(10,1);
	ASSERT_TRUE(x == y);
}
TYPED_TEST(Deque_Fixture, equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,2);
	deque_type y(10,1);
	ASSERT_FALSE(x == y);
}
TYPED_TEST(Deque_Fixture, equal_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(11,1);
	deque_type y(10,1);
	ASSERT_FALSE(x == y);
}
//deque equal test end

//deque less than test begin
TYPED_TEST(Deque_Fixture, less_than_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(12,1);
	deque_type y(10,1);
	ASSERT_FALSE(x<y);
}
TYPED_TEST(Deque_Fixture, less_than_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(12,1);
	deque_type y(100,1);
	ASSERT_TRUE(x<y);
}
TYPED_TEST(Deque_Fixture, less_than_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(12,1);
	deque_type y(12,1);
	ASSERT_FALSE(x<y);
}
TYPED_TEST(Deque_Fixture, less_than_4)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	deque_type y(10,10);
	ASSERT_TRUE(x<y);
}
//deque less than test end

