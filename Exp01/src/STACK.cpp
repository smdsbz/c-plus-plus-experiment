/**
 * Pure-C implementation of stack
 *
 * Author:      Xiaoguang Zhu
 * Student ID:  U201610136
 * Class:       CSIE1601
 */

#include <iostream>
using std::cin; using std::cout; using std::endl;

// NOTE: due to experiment restrictions, keep it Pure-C!
#include <cstdlib>
using std::malloc; using std::free;
#include <cstring>
using std::memcpy;

#include "STACK.hpp"


/******* Helper Functions *******/

static
void
__clearSTACK(STACK *const self) {
    if (self->elems != 0) {
        free(self->elems);
        self->elems = 0;
    }
    self->max = 0;
    self->pos = 0;
    return;
}


/******* Function Implementations *******/

void
initSTACK(STACK *const self, int num_elems) {
    // parameter validation
    if (num_elems <= 0 || self == 0) {
        __clearSTACK(self);
        return;
    }
    // space allocation (static stack)
    self->elems = (int *)malloc(sizeof(int) * num_elems);
    if (self->elems == 0) {
        self->max = 0;
        self->pos = 0;
        return;
    }
    // other initialization steps
    self->max = num_elems;
    self->pos = 0;
    return;
}

void
initSTACK(STACK *const self, const STACK &other) {
    // parameter validation
    if (self == 0) {
        __clearSTACK(self);
        return;
    }
    // copy content
    memcpy(self->elems, other.elems, sizeof(int) * other.max);
    self->max = other.max;
    self->pos = other.pos;
    return;
}

int
size(const STACK *const self) { return self->max; }

int
howMany(const STACK *const self) { return self->pos; }

int
getelem(const STACK *const self, int idx) {
    if (idx < 0 || idx >= self->pos) {
        // NOTE: parameter validation cannot be performed, due to return value
        //       data type
        /* TODO: */
        return 0;
    }
    return self->elems[idx];
}

STACK *const
push(STACK *const self, int val) {
    // parameter validation
    if (self == 0) {
        __clearSTACK(self);
        return 0;
    }
    // doability checking: full stack
    if (self->pos >= self->max) {
        return 0;
    }
    // okay to do
    self->elems[self->pos] = val;
    self->pos++;
    return self;
}

STACK *const
pop(STACK *const self, int &out) {
    // parameter validation
    if (self == 0) {
        __clearSTACK(self);
        return 0;
    }
    // doability checking: empty stack
    if (self->pos == 0) {
        return 0;
    }
    // okay to do
    self->pos--;
    out = self->elems[self->pos];
    return self;
}

STACK *const
assign(STACK *const self, const STACK &other) {
    // parameter validation
    if (self == 0) {
        __clearSTACK(self);
        return 0;
    }
    // get number of elements to copy
    int num_copy = (other.pos < self->max) ? other.pos : self->max;
    // do copy job
    self->pos = num_copy;
    memcpy(self->elems, other.elems, sizeof(int) * num_copy);
    return self;
}

/**
 * Format:
 *
 * 1  2  3  ...
 *
 * NOTE: two spaces in between!
 */
void
print(const STACK *const self) {
    // parameter validation
    if (self == 0) {
        return;
    }
    // print to command line, two spaces in between
    int stack_depth = self->pos;
    for (int idx = 0; idx != stack_depth; idx++) {
        printf("%d", self->elems[idx]);
        if (idx != stack_depth - 1) {
           printf("  ");
        }
    }
    return;
}

void
destroySTACK(STACK *const self) {
    // parameter validation
    if (self == 0) {
        return;
    }
    __clearSTACK(self);
    return;
}
