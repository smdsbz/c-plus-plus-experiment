/**
 * Author:      Xiaoguang Zhu
 * Student ID:  U201610136
 * Class:       CSIE1601
 */

#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <stdexcept>
#include <string>
using std::string; using std::stoi;
#include <vector>
using std::vector;

#include "QUEUE.hpp"


/******* Main Process *******/

int main(int argc, char const *argv[]) {

    unsigned argidx = 0;
    vector<string> args;
    for (int idx(0); idx != argc; idx++) {
        args.push_back(string(argv[idx]));
    }

    // Pointer to Working Queue, or PWQ
    QUEUE *pwq = 0;

    try {

        for (int idx(1); idx < argc; idx++) {
            string &word(args[idx]);
            if (idx != 1) {
                cout << "  ";
            }
            word.erase(0, 1);   // delete '-'
            cout << word;

            // `-S`: (1) create queue with size specified
            // `-I`: (N) sequentially enqueue following elements into queue
            // `-O`: (1) dequeue n times, where n is specified later
            // `-A`: (1) create new queue with n size, copying first n elements
            //           from last working queue
            // `-C`: (0) create an exact copy of the old working queue
            // `-N`: (0) get number of elements in queue

            if (word == string("S")) {
                // get queue size
                idx++;
                string &str_size = args[idx];
                int queue_size;
                try {
                    queue_size = stoi(str_size);
                } catch (const std::invalid_argument &e) {
                    throw std::runtime_error("failed to read integer!");
                }
                // queue size validation
                if (queue_size < 0) {
                    throw std::runtime_error("queue size for initialization "
                                             "must be positive!");
                }
                // create queue
                try {
                    pwq = new QUEUE(queue_size);
                } catch (const std::bad_alloc &e) {
                    throw std::runtime_error("failed to create queue!");
                }
                cout << "  " << queue_size;
            } else if (word == string("I")) {
                // iterate over args
                idx++;
                while (idx != argc) {
                    // get value
                    int val;
                    try {
                        val = stoi(args[idx]);
                    } catch (const std::invalid_argument &e) {    // reached non-numeric, could be a flag
                        idx--;      // complementing `idx++` at end of for-loop
                        break;
                    }
                    // enqueue element to working queue if no previous error
                    try {
                        (*pwq) << val;
                    } catch (const std::overflow_error &e) {
                        throw std::runtime_error(e.what());
                    }
                    idx++;
                }
                // print result
                if (int(*pwq) != 0) {
                    cout << "  ";
                    pwq->print();
                }
            } else if (word == string("O")) {
                // get number of times to dequeue
                idx++;
                string &str_num_deqs = args[idx];
                int num_deqs;
                try {
                    num_deqs = stoi(str_num_deqs);
                } catch (const std::invalid_argument &e) {
                    throw std::runtime_error(e.what());
                }
                // dequeue count validation
                if (num_deqs < 0) {
                    throw std::runtime_error("cannot dequeue negative times!");
                }
                // start deqping
                int deq_result;
                for (; num_deqs != 0; num_deqs--) {
                    try {
                        (*pwq) >> deq_result;
                    } catch (const std::underflow_error &e) {
                        throw std::runtime_error(e.what());
                    }
                }
                // print result
                if (int(*pwq) != 0) {
                    cout << "  ";
                    pwq->print();
                }
            } else if (word == string("A")) {
                idx++;
                string &str_size = args[idx];
                int new_size;
                try {
                    new_size = stoi(str_size);
                } catch (const std::invalid_argument &e) {
                    throw std::runtime_error(e.what());
                }
                // queue size validation
                if (new_size < 0) {
                    throw std::runtime_error("queue size for initialization "
                                             "must be positive!");
                }
                // create copy destination queue
                QUEUE *dstq = 0;
                try {
                    dstq = new QUEUE(new_size);
                } catch (const std::bad_alloc &e) {
                    throw std::runtime_error(e.what());
                }
                (*dstq) = (*pwq);
                delete pwq;
                pwq = dstq;
                if (int(*pwq) != 0) {
                    cout << "  ";
                    pwq->print();
                }
            } else if (word == string("C")) {
                // create new queue space
                QUEUE *dstq = 0;
                try {
                    dstq = new QUEUE(*pwq);
                } catch (std::bad_alloc &e) {
                    throw std::runtime_error(e.what());
                }
                delete pwq;
                pwq = dstq;
                if (int(*pwq) != 0) {
                    cout << "  ";
                    pwq->print();
                }
            } else if (word == string("N")) {
                cout << "  " << int(*pwq);
            } else if (word == string("G")) {
                // get index
                idx++;
                string &str_key = args[idx];
                int key;
                try {
                    key = stoi(str_key);
                } catch (std::invalid_argument &e) {
                    throw std::runtime_error(e.what());
                }
                // doability checking: if overflow
                int val;
                try {
                    val = (*pwq)[key];
                } catch (std::out_of_range &e) {
                    throw std::runtime_error(e.what());
                }
                cout << "  " << val;
            } else {
                throw std::runtime_error("unrecognized operational flag!");
            }

        }   // end for

    } catch (const std::runtime_error &e) {
        cout << "  E";
    }

    // cleaning jobs
    delete pwq;

    return 0;
}
