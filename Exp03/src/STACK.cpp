/**
 * Pure-C implementation of stack
 *
 * Author:      Xiaoguang Zhu
 * Student ID:  U201610136
 * Class:       CSIE1601
 */

#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <cstring>
using std::memcpy;
#include <stdexcept>

#include "STACK.hpp"


/******* Function Implementations *******/

STACK::STACK(int num_elems)
            // throws `std::bad_alloc` if `num_elems` is negative
        :   elems(new int [num_elems]),
            max(num_elems),
            pos(0) {
    return;
}

STACK::STACK(const STACK &other)
        :   elems(new int [other.max]),
            max(other.max),
            pos(other.pos) {
    memcpy(this->elems, other.elems, sizeof(int) * other.pos);
    return;
}

int
STACK::size(void) const { return this->max; }

STACK::operator int(void) const { return this->pos; }

int
STACK::operator[](int idx) const {
    if (idx < 0 || idx >= this->pos) {
        throw std::out_of_range("index passed exceeded range!");
    }
    return this->elems[idx];
}

STACK &
STACK::operator<<(int val) {
    // doability checking: full stack
    if (this->pos >= this->max) {
        throw std::overflow_error("cannot push to full stack!");
    }
    // okay to do
    this->elems[this->pos] = val;
    this->pos++;
    return *this;
}

STACK &
STACK::operator>>(int &out) {
    // doability checking: empty stack
    if (this->pos == 0) {
        throw std::underflow_error("connot pop from empty stack!");
    }
    // okay to do
    this->pos--;
    out = this->elems[this->pos];
    return *this;
}

STACK &
STACK::operator=(const STACK &other) {
    // get number of elements to copy
    int num_copy = (other.pos < this->max) ? other.pos : this->max;
    // do copy job
    this->pos = num_copy;
    memcpy(this->elems, other.elems, sizeof(int) * num_copy);
    return *this;
}

/**
 * Format:
 *
 * 1  2  3  ...
 *
 * NOTE: two spaces in between!
 */
void
STACK::print(void) const {
    // print to standard out, two spaces in between
    int stack_depth = this->pos;
    for (int idx = 0; idx != stack_depth; idx++) {
        cout << this->elems[idx];
        if (idx != stack_depth - 1) {
            cout << "  ";
        }
    }
    return;
}

STACK::~STACK(void) {
    if (this->elems) {
        delete [] this->elems;
    }
    *((int **)&this->elems) = 0;
    *((int *)&this->max) = 0;
    this->pos = 0;
    return;
}
