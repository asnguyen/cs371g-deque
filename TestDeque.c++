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

//iterator equal test begin
TYPED_TEST(Deque_Fixture, iterator_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.begin();
	auto b = x.begin();
	ASSERT_TRUE(a==b);
}
TYPED_TEST(Deque_Fixture, iterator_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	deque_type y(10,1);
	auto a = x.begin();
	auto b = y.begin();
	ASSERT_FALSE(a==b);
}
//iterator equal test end

//iterator plus_plus test begin
TYPED_TEST(Deque_Fixture, iterator_plus_plus_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = (a+1);
	auto c = ++a;
	ASSERT_TRUE(c==b);
}
TYPED_TEST(Deque_Fixture, iterator_plus_plus_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = (a+2);
	auto c = ++(++a);
	ASSERT_TRUE(c==b);
}
//iterator plus plus test end

//iterator minus minus test begin
TYPED_TEST(Deque_Fixture, iterator_minus_minus_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = (a-1);
	auto c = --a;
	ASSERT_TRUE(c==b);
}
TYPED_TEST(Deque_Fixture, iterator_minus_minus_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = (a-2);
	auto c = --(--a);
	ASSERT_TRUE(c==b);
}
//iterator mius minus test end

//iterator plus_equal test begin
TYPED_TEST(Deque_Fixture, iterator_plus_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = x.begin();
	a+=2;
	auto c = (b+2);
	ASSERT_TRUE(c==a);
}
TYPED_TEST(Deque_Fixture, iterator_plus_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = x.begin();
	a+=3;
	auto c = ++(b+2);
	ASSERT_TRUE(c==a);
}
//iterator plus_equal test end

//iterator minus_equal test begin
TYPED_TEST(Deque_Fixture, iterator_minus_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = x.end();
	a-=2;
	auto c = (b-2);
	ASSERT_TRUE(c==a);
}
TYPED_TEST(Deque_Fixture, iterator_minus_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = x.end();
	a-=3;
	auto c = --(b-2);
	ASSERT_TRUE(c==a);
}
//iterator minus_equal test end

//iterator star test begin
TYPED_TEST(Deque_Fixture, iterator_star_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.begin();
	ASSERT_EQ(*a,1);
}
TYPED_TEST(Deque_Fixture, iterator_star_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.begin();
	ASSERT_EQ(*++a,1);
}
TYPED_TEST(Deque_Fixture, iterator_star_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.end();
	ASSERT_EQ(*--a,1);
}
TYPED_TEST(Deque_Fixture, iterator_star_4)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,2);
	auto a = x.begin();
	ASSERT_NE(*a,1);
}
TYPED_TEST(Deque_Fixture, iterator_star_5)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.begin();
	*a = 2;
	ASSERT_EQ(*a,2);
}
//iterator star test end

//const iterator test begin. Same as iterator test but now with const deque
TYPED_TEST(Deque_Fixture, const_iterator_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.begin();
	auto b = x.begin();
	ASSERT_TRUE(a==b);
}
TYPED_TEST(Deque_Fixture, const_iterator_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	const deque_type y(10,1);
	auto a = x.begin();
	auto b = y.begin();
	ASSERT_FALSE(a==b);
}
TYPED_TEST(Deque_Fixture, const_iterator_plus_plus_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = (a+1);
	auto c = ++a;
	ASSERT_TRUE(c==b);
}
TYPED_TEST(Deque_Fixture, const_iterator_plus_plus_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = (a+2);
	auto c = ++(++a);
	ASSERT_TRUE(c==b);
}
//iterator minus minus test begin
TYPED_TEST(Deque_Fixture, const_iterator_minus_minus_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = (a-1);
	auto c = --a;
	ASSERT_TRUE(c==b);
}
TYPED_TEST(Deque_Fixture, const_iterator_minus_minus_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = (a-2);
	auto c = --(--a);
	ASSERT_TRUE(c==b);
}
//iterator mius minus test end

//iterator plus_equal test begin
TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = x.begin();
	a+=2;
	auto c = (b+2);
	ASSERT_TRUE(c==a);
}
TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.begin();
	auto b = x.begin();
	a+=3;
	auto c = ++(b+2);
	ASSERT_TRUE(c==a);
}
//iterator plus_equal test end

//iterator minus_equal test begin
TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = x.end();
	a-=2;
	auto c = (b-2);
	ASSERT_TRUE(c==a);
}
TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	//deque_type y(10,1);
	auto a = x.end();
	auto b = x.end();
	a-=3;
	auto c = --(b-2);
	ASSERT_TRUE(c==a);
}
//iterator minus_equal test end

//iterator star test begin
TYPED_TEST(Deque_Fixture, const_iterator_star_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.begin();
	ASSERT_EQ(*a,1);
}
TYPED_TEST(Deque_Fixture, const_iterator_star_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.begin();
	ASSERT_EQ(*++a,1);
}
TYPED_TEST(Deque_Fixture, const_iterator_star_3)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.end();
	ASSERT_EQ(*--a,1);
}
TYPED_TEST(Deque_Fixture, const_iterator_star_4)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,2);
	auto a = x.begin();
	ASSERT_NE(*a,1);
}
//iterator star test end

//deque copy constructor test begin
TYPED_TEST(Deque_Fixture, copy_constructor)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	const deque_type y(x);
	ASSERT_TRUE(y==x);
}
//deque copy_constructor test end

//deque copy assignment test begin
TYPED_TEST(Deque_Fixture, copy_assignment)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	deque_type y=x;
	ASSERT_TRUE(y==x);
}
//deque copy assignment test end

//operator [] test begin
TYPED_TEST(Deque_Fixture, index_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	int a = x[0];
	auto b = x.begin();
	ASSERT_EQ(a,*b);
}
TYPED_TEST(Deque_Fixture, index_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	int a = x[3];
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, index_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x[3] = 4;
	ASSERT_EQ(x[3],4);
}
TYPED_TEST(Deque_Fixture, const_index_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	int a = x[0];
	auto b = x.begin();
	ASSERT_EQ(a,*b);
}
TYPED_TEST(Deque_Fixture, const_index_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	int a = x[3];
	ASSERT_EQ(a,1);
}
//operator [] test end

//deque at test begin
TYPED_TEST(Deque_Fixture, _at_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	int a = x.at(0);
	auto b = x.begin();
	ASSERT_EQ(a,*b);
}
TYPED_TEST(Deque_Fixture, _at_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	int a = x.at(3);
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, at_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.at(3) = 4;
	ASSERT_EQ(x[3],4);
}
TYPED_TEST(Deque_Fixture, const_at_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	int a = x.at(0);
	auto b = x.begin();
	ASSERT_EQ(a,*b);
}
TYPED_TEST(Deque_Fixture, const_at_2)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	int a = x.at(3);
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, at_4)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	try
	{
		x.at(20);
		ASSERT_TRUE(false);
	}
	catch(out_of_range)
	{
		ASSERT_TRUE(true);
	}
}
//deque back test end
TYPED_TEST(Deque_Fixture, back_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.back();
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, back_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_back(3);
	auto a = x.back();
	ASSERT_EQ(a,3);
}
TYPED_TEST(Deque_Fixture, back_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_front(3);
	auto a = x.back();
	ASSERT_EQ(a,1);
}
//deque back test end

//deque front test end
TYPED_TEST(Deque_Fixture, front_1)
{
	using deque_type = typename TestFixture::deque_type;
	const deque_type x(10,1);
	auto a = x.front();
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, front_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_back(3);
	auto a = x.front();
	ASSERT_EQ(a,1);
}
TYPED_TEST(Deque_Fixture, front_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_front(3);
	auto a = x.front();
	ASSERT_EQ(a,3);
}
//deque back test end

//erase test begin
TYPED_TEST(Deque_Fixture, erase)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.erase(x.begin()+1);
	//ASSERT_TRUE(a==x.begin());
	ASSERT_EQ(x.size(),9);
}
//erase test end

//insert test begin
TYPED_TEST(Deque_Fixture, insert_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.insert(x.begin()+1,1);
	//ASSERT_TRUE(a==x.begin());
	ASSERT_EQ(x.size(),11);
}
TYPED_TEST(Deque_Fixture, insert_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	auto a = x.insert(x.begin()+1,3);
	ASSERT_EQ(*a,3);
}
//insert test end

//pop_back test begin
TYPED_TEST(Deque_Fixture, pop_back)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.pop_back();
	ASSERT_EQ(x.size(),9);
}
//pop_back test end

//pop_front test begin
TYPED_TEST(Deque_Fixture, pop_front)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.pop_front();
	ASSERT_EQ(x.size(),9);
}
//pop_front test end

//push front test begin
TYPED_TEST(Deque_Fixture, push_front)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_front(3);
	ASSERT_EQ(x.size(),11);
	int a = x.front();
	ASSERT_EQ(a,3);
}
//push_front test end

//push_back test end
TYPED_TEST(Deque_Fixture, push_back)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.push_back(3);
	ASSERT_EQ(x.size(),11);
	int a = x.back();
	ASSERT_EQ(a,3);
}
//push_back test end

//resize test begin
TYPED_TEST(Deque_Fixture, resize_1)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.resize(15,1);
	ASSERT_EQ(x.size(),15);
}
TYPED_TEST(Deque_Fixture, resize_2)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.resize(15,3);
	ASSERT_EQ(x.size(),15);
	auto e = x.back();
	ASSERT_EQ(e,3);
}
TYPED_TEST(Deque_Fixture, resize_3)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	x.resize(5);
	ASSERT_EQ(x.size(),5);
}
//resize test end

//size test begin
TYPED_TEST(Deque_Fixture, size)
{
	using deque_type = typename TestFixture::deque_type;
	deque_type x(10,1);
	ASSERT_EQ(x.size(),10);
}
//size test end

/*deque stress test begin
TYPED_TEST(Deque_Fixture. stress_test_1)
{

}
//deque stress test end*/