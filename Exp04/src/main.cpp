#include <iostream>
using std::cin; using std::cout; using std::endl;

#include "QUEUE.hpp"


/******* Question Parameters *******/

// gentalmen count
#define M       ( 17 )
// ladies count
#define F       ( 13 )
// NOTE: the following `place`s are one-indexed
// initial place of our gent
#define m       ( 1 )
// initial place of our lady
#define f       ( 1 )


/******* Solution Session *******/

// use these value to track our two delicates
#define TARGET      ( 1 )
#define NONTARGET   ( 0 )

class Solution {

public:
    QUEUE   gents_queue;
    QUEUE   maids_queue;

public:

    Solution(const unsigned gents_count=M, const unsigned maids_count=F,
             unsigned gent_pos=m, unsigned lady_pos=f)
            :   gents_queue(M), maids_queue(F) {
        // convert one-indexed place to zero-indexed
        --gent_pos; --lady_pos;
        // construct gents queue
        for (unsigned idx = 0; idx != gents_count; ++idx) {
            if (idx == gent_pos) {
                this->gents_queue << TARGET;
            } else {
                this->gents_queue << NONTARGET;
            }
        }
        // construct maids queue
        for (unsigned idx = 0; idx != maids_count; ++idx) {
            if (idx == lady_pos) {
                this->maids_queue << TARGET;
            } else {
                this->maids_queue << NONTARGET;
            }
        }
    }

    void _stepOneRound(int &gent, int &lady) {
        // pick queue heads
        this->gents_queue >> gent;
        this->maids_queue >> lady;
        // dance
        // and put them back
        this->gents_queue << gent;
        this->maids_queue << lady;
        return;
    }

    bool _isThePair(const int &gent, const int &lady) {
        return ((gent == TARGET) && (lady == TARGET));
    }

    unsigned solve(void) {
        // first round
        unsigned rounds = 0;
        int last_gent, last_lady;
        // keep dancing 'til they meet!
        do {
            this->_stepOneRound(last_gent, last_lady);
            ++rounds;
        } while (!this->_isThePair(last_gent, last_lady));
        return rounds;
    }

} solution;


/******* Main Process *******/

int main(void) {
    cout << solution.solve() << endl;
    return 0;
}
