// --------------------------
// projects/c++/deque/Deque.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <iostream>

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using namespace std;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                           allocator_type;
        typedef typename allocator_type::value_type         value_type;

        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;

        typedef typename allocator_type::template rebind<pointer>::other B;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         checks the size of each deque first
         if they have equal size then use std::equal to figure out which is bigger
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) 
        {
            // <your code>
            if(lhs.deque_size != rhs.deque_size)
                        return false;
            return std::equal(lhs.begin(),lhs.end(),rhs.begin());
        }

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         first judge by the size of which is bigger.
         if they are equal then use std::lexicographical_compare to figure which is bigger
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) 
        {
            // <your code>
            if(lhs.deque_size < rhs.deque_size)
                return true;
            if(lhs.deque_size > rhs.deque_size)
                return false;
            return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
        }

    private:
        // ----
        // data
        // ----

        allocator_type a;                           //allocator for the inner "array"
        // <your data>
        B astar;                                    //allocator for the outer "array"
        pointer* outer_begin;                       //the very start of the "outer array"
        pointer* outer_end;                         //the very end of the "outer array"
        pointer* used_begin;                        //the beginning of the used space in the "outer array"
        pointer* used_end;                          //the end of the used space in the "outer array"
        pointer data_start;                         //the start of the data in the deque
        pointer data_end;                           //the end of the data in the deque
        size_type deque_size;                       //the size(number of elements) of the deque
        size_type deque_capacity;                   //the max number of elements that deque can store
        const size_type static inner_size = 5;      //the size of the "inner arrays"


    private:
        // -----
        // valid
        // -----

        bool valid () const 
        {
            // <your code>
            return outer_begin <= outer_end &&
                   deque_capacity >= 0      &&
                   deque_size >= 0;
        }

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::pointer               pointer;
                typedef typename my_deque::reference             reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 two iterators are equal if they have the same location (address)
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) 
                {
                    // <your code>
                    return lhs.location == rhs.location;
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
                pointer* outer_begin;               //the beginning of the outer array
                pointer location;                   //the location of the iterator
                pointer data_end;                   //the end of the data

                size_type outer_location;           //the location of the iterator in terms of the "outer array"
                size_type inner_location;           //the location of the iterator in terms of the "inner array"

            private:
                // -----
                // valid
                // -----

                bool valid () const 
                {
                    // <your code>
                    if(outer_begin==0)
                        return false;
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                //iterator (){}
                iterator (my_deque<T,A>* deque):
                    outer_begin(deque->used_begin),
                    location(deque->data_start),
                    data_end(deque->data_end)
                {
                    // <your code>
                    outer_location = 0;                                         //starts at the first "index" of "outer array"
                    inner_location = inner_size - (location - *outer_begin) -1; //finds the inner location based on its location compared to outer_begin    
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const 
                {
                    // <your code>
                   return *location;
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () 
                {
                    // <your code>
                    if(location == data_end -1)                         //iterator is at the end of the used data so it has finished iteratoring through the deque
                    {
                        ++location;
                        return *this;
                    }
                    if(inner_location)                                  //if there is room left to move forward in the inner row
                    {
                        ++location;
                        --inner_location;
                    }
                    else                                                //the iterator must move to the next row
                    {
                        ++outer_location;                               //moves to the next row
                        location = *(outer_begin + outer_location);     
                        inner_location = inner_size -1;
                    }

                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -- () 
                {
                    // <your code>
                    if(inner_size -inner_location || location == data_end)              //if there are still room left in the row to move back
                    {
                        --location;
                        if(location!=data_end)                                  
                            ++inner_location;
                    }
                    else
                    {
                        --outer_location;                                               //move to the prev row
                        location = *(outer_begin + outer_location) + inner_size -1;
                        inner_location =0;

                    }
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) 
                {
                    // <your code>
                    while(d)
                    {
                        --d;
                        ++*this;
                    }
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) 
                {
                    // <your code>
                    while(d)
                    {
                        --*this;
                        --d;
                    }
                    assert(valid());
                    return *this;
                }};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::const_pointer         pointer;
                typedef typename my_deque::const_reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) 
                {
                    // <your code>
                    //return const_cast<my_deque*>(lhs) == const_cast<my_deque*>(rhs);
                    return lhs.normal_iterator == rhs.normal_iterator;
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
                my_deque::iterator normal_iterator;                 //a const iterator contains a non const iterator

            private:
                // -----
                // valid
                // -----

                bool valid () const 
                {
                    // <your code
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (const my_deque* deque):
                    normal_iterator(const_cast<my_deque*>(deque))
                {
                    // <your code>
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const 
                {
                    // <your code>
                    return const_cast<const_reference>(*normal_iterator);
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () 
                {
                    // <your code>
                    ++normal_iterator;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () 
                {
                    // <your code>
                    --normal_iterator;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) 
                {
                    // <your code>
                    assert(valid());
                    normal_iterator+=d;
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) 
                {
                    // <your code>
                    assert(valid());
                    normal_iterator-=d;
                    return *this;
                }};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         when a deque is created by default or if no size, it zeros everything. it exist in limbo until a push is called on it
         if called with a size and/or value, a while loop will push "s" values into the deque. Push will call outer_resive which
         will set the values for all the other data members. 

         */
        explicit my_deque (size_type s = 0, const_reference v = value_type(), const allocator_type& a = allocator_type()) 
        {
            // <your code>
            outer_begin = 0;
            outer_end = 0;
            used_end = 0;
            used_begin =0;
            data_end = 0;
            data_start = 0;
            deque_size = 0;
            deque_capacity = 0;
            while(s)
            {
                push_back(v);
                --s;
            }
            assert(valid());

        }

        /**
         * <your documentation>
         the copy constructor creates act like the normal construct except 
         it sets the the caller to the callee
         */
        my_deque (const my_deque& that) 
        {
            // <your code>
            
            deque_capacity = 0;
            deque_size     = 0;
            outer_begin    = 0;
            outer_end      = 0;
            used_begin     = 0;
            used_end       = 0;
            data_end       = 0;
            data_start     = 0;

            *this = that;

            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         the destructor will first clear the caller and deallocate
         the outer array and re-zeroing the data members
         */
        ~my_deque () 
        {
            // <your code>
            this->clear();
            if(outer_begin != 0)
            {
                astar.deallocate(outer_begin, outer_end - outer_begin +1);
            }
            outer_begin = 0;
            outer_end = 0;
            used_end = 0;
            used_begin =0;
            data_end = 0;
            data_start = 0;
            deque_size = 0;
            deque_capacity = 0;
            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         the copy assignment copys the values in rhs
         into this.
         */
        my_deque& operator = (const my_deque& rhs) 
        {
            // <your code>

            if(this == &rhs)
                return *this;
            clear();
            auto b = const_cast<my_deque&>(rhs).begin();
            auto e = const_cast<my_deque&>(rhs).end();
            while(b!=e)
            {
                push_back(*b);
                ++b;
            }
            
            assert(valid());
            return *this;
        }

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         the index operator [] uses divide and mod to find
         the value at [index]. using divide it find the which 
         part of the outer element the index is in. it uses mod
         to find which part of the inner array the index is at
         */
        reference operator [] (size_type index) 
        {
            // <your code>
            size_type new_index = index +(data_start - *used_begin);
            size_type outer_index = new_index / inner_size;
            size_type inner_index = new_index % inner_size;

            pointer* temp_outer = used_begin;
            temp_outer += outer_index;
            pointer temp_inner = *temp_outer;
            temp_inner += inner_index;
            return *temp_inner;

        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         at method uses the same algorithm as operator [] but it
         checks to see if the index is out of bounds or not. 
         */
        reference at (size_type index) 
        {
            // <your code>
            if((index<0)|| (index > deque_size -1))
                throw std::out_of_range("out of range");
            size_type new_index = index +(data_start - *used_begin);
            size_type outer_index = new_index / inner_size;
            size_type inner_index = new_index % inner_size;

            pointer* temp_outer = used_begin;
            temp_outer += outer_index;
            pointer temp_inner = *temp_outer;
            temp_inner += inner_index;
            return *temp_inner;;
        }

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         data_end is the end of last element in the deque so therefore
         data_end -1 is the beginning of the last element
         */
        reference back () 
        {
            // <your code>
            return *(data_end-1);
        }

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () 
        {
            // <your code>
            return iterator(this);
        }

        /**
         * <your documentation>
         */
        const_iterator begin () const 
        {
            // <your code>
            return const_iterator(this);
        }

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         to clear a deque, clear() starts the at the start of the 
         data and go throug and destroy and deallocate the elements
         until reaching the end of data
         */
        void clear () 
        {
            // <your code>
            if(deque_capacity > 0)
            {
                pointer* temp_used = used_begin;
                pointer temp = data_start;


                if(!(data_start == data_end))
                {
                    while(true)
                    {
                        if(temp != data_end)
                            a.destroy(temp);
                        if((*temp_used+(inner_size -1))==temp)
                        {
                            a.deallocate(*(temp_used),inner_size);
                            astar.destroy(temp_used);
                            ++temp_used;
                            if(temp_used == used_end)
                            {
                                break;
                            }
                            temp = *temp_used;
                        }
                        else
                        {
                            ++temp;
                        }
                    }
                    
                    
                }
                used_begin  = outer_begin;
                used_begin += ((deque_capacity/inner_size)/2);
                used_end = used_begin;
                data_start=0;
                data_end=0;
                deque_size = 0;
            }
            assert(valid());
        }

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () 
        {
            // <your code>
            return iterator(this)+=deque_size;
        }

        /**
         * <your documentation>
         */
        const_iterator end () const 
        {
            // <your code>
            return const_iterator(this)+=deque_size;
        }

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         erase starts at the pos and going to the end of the 
         data, takes the next element and sets it to the 
         current element. by using this alogrithm, the value
         at pos is left out. at the end of the algorthim, we pop 
         the last element to reduce the size
         */
        iterator erase (iterator pos) 
        {
            // <your code>
            auto pre = pos;
            auto next = pos++;
            auto it_end = end();
            while(next!=it_end)
            {
                *pre = *next;
                ++next;
                ++pre;
            }
            pop_back();
            assert(valid());
            return --pos;
        }

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () 
        {
            // <your code>
            return *data_start;
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         to insert, we begin at copy of pos and sets the next value to
         the current value. we then copy the val into the pos position
         */
        iterator insert (iterator pos, const_reference val) 
        {
            // <your code>
            auto pre = pos;
            auto next = ++pos;
            auto it_end = end();
            value_type v;
            while(next!=it_end)
            {
                v = *next;
                *next = *pre;
                ++next;
                ++pre;
            } 
            push_back(v);
            *(--pos) = val;
            assert(valid());
            return pos;
        }

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () 
        {
            // <your code>
            if(static_cast<size_type>(data_end != (*(used_end-1)+1)))           //if the element is not the first element in the inner array
            {
                a.destroy(data_end-1);                                          //just simple remove it
                --data_end;
                --deque_size;
            }
            else                                                                //the element that we want to remove is the fist element
            {
                a.destroy(data_end-1);                                          //we remove it
                --deque_size;
                
                a.deallocate(*(used_end-1),inner_size);                         //now we want to deallocate the inner array
                astar.destroy(used_end);                                        //destroys the element in the outer array
                if(outer_begin != outer_end)                                    //there are still elements in the outer array
                {
                    --used_end;
                    data_end = *used_end + inner_size;
                }
                else                                                            //there are no elements in the outer array
                {
                    used_begin = outer_begin;
                    used_begin += ((deque_capacity/inner_size)/2);
                    used_end = used_begin;
                    data_start = 0;
                    data_end = 0;
                    deque_size = 0;

                }
            }
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void pop_front () 
        {
            // <your code>
            if(data_start != *used_begin + inner_size -1)               //check to see if the element is the last element in the inner array
            {
                a.destroy(data_start);                                  //if not, just simple destroy it
                ++data_start;
                --deque_size;
            }
            else                                                        //if the element is the last element of the inner array
            {
                a.destroy(data_start);                                  //if so destroy it and then....
                --deque_size;
                a.deallocate(*used_begin,inner_size);                   //deallocate the inner array
                astar.destroy(used_begin);                              //destroy the element in the outer array
                if(outer_begin != outer_begin)                          //is there elements in the outer array
                {
                    ++used_begin;
                    data_start = *used_begin;
                }
                else                                                    //no? then reset the outer array
                {
                    used_begin = outer_begin;
                    used_begin += ((deque_capacity/inner_size)/2);
                    used_end = used_begin;
                    data_start = 0;
                    data_end = 0;
                    deque_size = 0;
                }
            }
            assert(valid());
        }

        //user defined method: outer_resize
        void outer_resize(bool front)
        {
            if(deque_capacity == 0)                 //initial creation of a deque will have a capacity of 0
            {
                used_begin = astar.allocate(1);    //using astar allocator to allocate space enough for 1 pointer*
                astar.construct(used_begin);        //astar constructs a pointer* at location outer_begin
                
                outer_begin = used_begin;           //since this is the first "inner array" set outer_begin ... 
                outer_end = used_begin;             //... and outer_end to used_begin 
                
                used_end = used_begin + 1;
                
                data_start = a.allocate(inner_size);//using a allocator to allocate enough space to fit inner_size number of 
                                                    //pointer and returns the address to data_start
                *used_begin = data_start;
                data_start+=inner_size/2;
                data_end = data_start+1;
                deque_capacity = inner_size;

            }
            else if(deque_size == 0)
                //if(deque_size == 0)                      //capacity is more than 0 but there is currently no elements in the deque (size = 0)
                {
                    astar.construct(used_begin);         //use astar to create a pointer* at used_begin 
                    used_end = used_begin + 1;           //since we have only created 1 pointer* used_end is only 1 unit away from used_begin
                    data_start = a.allocate(inner_size); //allocates enough space to fit inner_size number of pointers
                    *used_begin = data_start;            //moves *used_begin to data_start
                    data_start += inner_size/2;          //moves data_start to the center of space allocated
                    data_end = data_start + 1;           //sets data_end to 1 unit away from data_start
                }
                else
                {
                    //assert(false);
                    pointer* new_used_begin;                   //pointer* to the new used_begin                                    
                    pointer* new_used_end;                     //pointer* to the new used_end
                    pointer* old_outer_begin = outer_begin;    //creates a pointer that is a copy of outer_begin
                    pointer* old_outer_end = outer_end;        //creates a pointer that is a copy of outer_end

                    //allocate outer pointers to manage 4x old memory 
                    new_used_begin = astar.allocate((deque_capacity/inner_size) * 4);
                    //cout << "old used_begin = " << used_begin <<endl;
                    //cout << "new used_begin = " << new_used_begin << endl; 


                    //Reset memory block ponters
                    outer_begin = new_used_begin;                                        
                    outer_end   = outer_begin + ((deque_capacity/inner_size) * 4) -1;  

                    //cout << outer_end - outer_begin<<endl; 

                    new_used_begin += (deque_capacity/inner_size);
                    new_used_end = new_used_begin;

                    //copies the old deque into the new deque
                    for(pointer* temp_pointer = used_begin; temp_pointer < used_end;++temp_pointer)
                    {
                        astar.construct(new_used_end);
                        *new_used_end = *temp_pointer;
                        ++new_used_end;
                    }
                    //destroys and deallocate the old deque
                    pointer* temp_begin = used_begin;
                    while(temp_begin != used_end)
                    {
                        astar.destroy(temp_begin);
                        ++temp_begin;
                    }
                    astar.deallocate(old_outer_begin,(old_outer_end - old_outer_begin +1));

                    //resets the used_begin and used_end pointers
                    used_begin = new_used_begin;
                    used_end = new_used_end;

                    if(front)                                   //if we need add something in the front
                    {
                        astar.construct(--used_begin);
                        data_start = a.allocate(inner_size);
                        *used_begin = data_start;
                        data_start+= (inner_size-1);
                    }
                    else                                        //if we need to add something in the back
                    {
                        astar.construct(used_end);
                        data_end = a.allocate(inner_size);
                        *used_end = data_end;
                        ++used_end;
                    }
                    deque_capacity = (((deque_capacity/inner_size)*4)*inner_size);



                }
               
        }

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference value) 
        {
            // <your code>
            if(used_begin == used_end)                      //after a resize or a fresh creation
            {
                outer_resize(false);                        //resizes the deque and create element in the back
                a.construct(data_start, value);
            }
            else
            {
                if(static_cast<size_type>((data_end - *(used_end -1))) < inner_size)        //if there is room in the row for another element
                {
                    a.construct(data_end,value);
                    ++data_end;
                }
                else
                {
                    if((used_end)==(outer_end+1))                       //there is no room in the deque so we have resize more space
                    {
                        outer_resize(false);
                        a.construct(data_end,value);
                        ++data_end;
                    }
                    else                                                //there is no room but there is unused space in the outer array
                    {
                        astar.construct(used_end);
                        data_end = a.allocate(inner_size);
                        *used_end = data_end;
                        a.construct(data_end,value);
                        ++data_end;
                        ++used_end;

                    }
                }
            }
            assert(valid());
            ++deque_size;
        }

        /**
         * <your documentation>
         */
        void push_front (const_reference value) 
        {
            // <your code>
            if(used_begin == used_end)                  //after a resize or a fresh creation
            {
                outer_resize(false);                    //resizes the deque and create element in the back
                a.construct(data_start,value);
            }
            else
            {
                if(data_start - *used_begin >= 1)       //if there is room left in the row
                {
                    --data_start;
                    a.construct(data_start,value);      //creates a new element
                }
                else
                {
                    if((used_begin == outer_begin) && (data_start == *used_begin))      //there is no room in inner array or outer array so mus resize and create a element in the front
                    {
                        outer_resize(true);
                        a.construct(data_start, value);
                    }
                    else                                                                //there is no room in the inner but there is room in the outer array
                    {
                        --used_begin;
                        astar.construct(used_begin);
                        data_start = a.allocate(inner_size);
                        *used_begin = data_start;
                        data_start+=(inner_size-1);
                        a.construct(data_start,value);
                    }
                }
            }
            assert(valid());
            deque_size++;
        }

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) 
        {
            // <your code>
            while(deque_size > s)       //if the desire size is smaller than the current size, we must pop the excess elements off
                pop_back();
            while(deque_size < s)       //if the desire size is bigger than the current size, we must push elements with value v
                push_back(v);
            assert(valid());
        }

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const 
        {
            // <your code>
            return deque_size;
        }

        size_type capacity() const
        {
            return deque_capacity;
        }

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (my_deque& that)
        {
            // <your code>
            my_deque temp = *this;
            *this = that;
            that = temp;
            assert(valid());
        }};

#endif // Deque_h
