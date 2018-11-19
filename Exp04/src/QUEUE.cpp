#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <stdexcept>

#include "QUEUE.hpp"


/******* Helper Functions *******/

#define min(lhs, rhs)   ( ((lhs) < (rhs)) ? (lhs) : (rhs) )

/**
 *  move all elements in input buffer to output buffer
 *
 *  Args:
 *  `self`: `QUEUE`: `*this`
 */
#define _move_input_to_output(self)                                         \
    {                                                                       \
        for (int st = 0, range = int((self).s2); st != range; ++st) {       \
            int tmp;                                                        \
            (self).s2 >> tmp;                                               \
            (self).STACK::operator<<(tmp);                                  \
        }                                                                   \
    }


/******* Method Implementations *******/

/**
 *  NOTE:
 *  Using base class instance `QUEUE::STACK` for output, `QUEUE::s2` for
 *  input!
 */

QUEUE::QUEUE(int size)
        :   STACK(size),
            s2(size) {
    if (size <= 0) {
        throw std::runtime_error("Size must be positive!");
    }
    return;
}

QUEUE::QUEUE(const QUEUE &other)
        :   STACK(other),       // `other` treated as of type `STACK`
            s2(other.s2) {
    return;
}

QUEUE::operator int(void) const {
    int output_count = this->STACK::operator int();
    int input_count = int(this->s2);
    return (output_count + input_count);
}

int
QUEUE::full(void) const {
    /**
     *  NOTE:
     *  It can be concluded that the `QUEUE` is considered *full* once the
     *  output buffer is not empty and input buffer is full!
     *  Consider an `enqueue` request at this point: the new element cannot be
     *  pushed into input buffer immediately for it's already full, you must
     *  move the elements in input buffer to the output one. But in order to
     *  keep output follows the correct "FIFO" order, order of the output
     *  buffer elements must not be changed, thus elements in input buffer
     *  cannot be moved into output buffer at this point, causing the `enqueue`
     *  request to fail, the `QUEUE` appears to be *full*.
     */
    bool output_not_empty = this->STACK::operator int();
    bool input_full = (this->s2.size() == int(this->s2));
    if (output_not_empty && input_full) { return 1; }
    return 0;
}

int
QUEUE::operator[](int idx) const {
    // NOTE: `idx` is zero-indexed
    // input validation
    if (idx >= int(*this)) {
        throw std::out_of_range("index exceeded queue length");
    }
    // get the element
    int output_count = this->STACK::operator int();
    // if the element looking for can be found in output buffer
    if (idx < output_count) {
        return this->STACK::operator[](output_count - 1 - idx);
    } else {    // the element is in input buffer
        return this->s2[idx - output_count];
    }
}

QUEUE &
QUEUE::operator<<(int val) {
    // doability checking
    if (this->full()) {
        throw std::overflow_error("trying to enqueue when it's full");
    }
    // if input buffer is full, clear input buffer by stacking all of its
    // elements into output buffer (output buffer should be empty, checking
    // done by last line `this->full()`)
    if (this->s2.size() == int(this->s2)) {
        _move_input_to_output(*this);
    }
    // last step: push `val` to input buffer
    this->s2 << val;
    return *this;
}

QUEUE &
QUEUE::operator>>(int &elem) {
    // doability checking
    if (int(*this) == 0) {
        throw std::underflow_error("trying to dequeue when it's empty");
    }
    // if output buffer is empty, get all elements in input buffer
    if (this->STACK::operator int() == 0) {
        _move_input_to_output(*this);
    }
    // last step: pop from output buffer to `elem`
    this->STACK::operator>>(elem);
    return *this;
}

QUEUE &
QUEUE::operator=(const QUEUE &other) {
    // clear this queue
    int trashcan;
    for (int idx = 0, range = int(*this); idx != range; ++idx) {
        (*this) >> trashcan;
    }
    // calculate copyable range
    int copy_range = min(int(other), this->size());
    // do copy job
    for (int idx = 0; idx != copy_range; ++idx) {
        (*this) << other[idx];
    }
    return *this;
}

void
QUEUE::print(void) const {
    int range = int(*this);
    // if empty, print nothing
    if (range == 0) { return; }
    // print elements in middle of queue
    for (int idx = 0, loop_range = range - 1; idx != loop_range; ++idx) {
        cout << (*this)[idx] << "  ";
    }
    // print last element (without the trailing whitespaces)
    cout << (*this)[range - 1];
    return;
}

QUEUE::~QUEUE(void) {
    // all resource freed via calling `~STACK()`
    return;
}
