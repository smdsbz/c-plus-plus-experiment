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

#include "STACK.hpp"


/******* Main Process *******/

int main(int argc, char const *argv[]) {

    unsigned argidx = 0;
    vector<string> args;
    for (int idx(0); idx != argc; idx++) {
        args.push_back(string(argv[idx]));
    }

    // Pointer to Working Stack, or PWS
    STACK *pws = 0;

    try {

        for (int idx(1); idx < argc; idx++) {
            string &word(args[idx]);
            if (idx != 1) {
                cout << "  ";
            }
            word.erase(0, 1);   // delete '-'
            cout << word;

            // `-S`: (1) create stack with size specified
            // `-I`: (N) sequentially push following elements into stack
            // `-O`: (1) pop n times, where n is specified later
            // `-A`: (1) create new stack with n size, copying first n elements from
            //       last working stack
            // `-C`: (0) create an exact copy of the old working stack
            // `-N`: (0) get number of elements in stack

            if (word == string("S")) {
                // get stack size
                idx++;
                string &str_size = args[idx];
                int stack_size;
                try {
                    stack_size = stoi(str_size);
                } catch (const std::invalid_argument &e) {
                    throw std::runtime_error("failed to read integer!");
                }
                // stack size validation
                if (stack_size < 0) {
                    throw std::runtime_error("stack size for initialization "
                                             "must be positive!");
                }
                // create stack
                try {
                    pws = new STACK(stack_size);
                } catch (const std::bad_alloc &e) {
                    throw std::runtime_error("failed to create stack!");
                }
                cout << "  " << stack_size;
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
                    // push element to working stack if no previous error
                    try {
                        (*pws) << val;
                    } catch (const std::overflow_error &e) {
                        throw std::runtime_error(e.what());
                    }
                    idx++;
                }
                // print result
                if (int(*pws) != 0) {
                    cout << "  ";
                    pws->print();
                }
            } else if (word == string("O")) {
                // get number of times to pop
                idx++;
                string &str_num_pops = args[idx];
                int num_pops;
                try {
                    num_pops = stoi(str_num_pops);
                } catch (const std::invalid_argument &e) {
                    throw std::runtime_error(e.what());
                }
                // pop count validation
                if (num_pops < 0) {
                    throw std::runtime_error("cannot pop negative times!");
                }
                // start popping
                int pop_result;
                for (; num_pops != 0; num_pops--) {
                    try {
                        (*pws) >> pop_result;
                    } catch (const std::underflow_error &e) {
                        throw std::runtime_error(e.what());
                    }
                }
                // print result
                if (int(*pws) != 0) {
                    cout << "  ";
                    pws->print();
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
                // stack size validation
                if (new_size < 0) {
                    throw std::runtime_error("stack size for initialization "
                                             "must be positive!");
                }
                // create copy destination stack
                STACK *dststk = 0;
                try {
                    dststk = new STACK(new_size);
                } catch (const std::bad_alloc &e) {
                    throw std::runtime_error(e.what());
                }
                (*dststk) = (*pws);
                delete pws;
                pws = dststk;
                if (int(*pws) != 0) {
                    cout << "  ";
                    pws->print();
                }
            } else if (word == string("C")) {
                // create new stack space
                STACK *dststk = 0;
                try {
                    dststk = new STACK(*pws);
                } catch (std::bad_alloc &e) {
                    throw std::runtime_error(e.what());
                }
                delete pws;
                pws = dststk;
                if (int(*pws) != 0) {
                    cout << "  ";
                    pws->print();
                }
            } else if (word == string("N")) {
                cout << "  " << int(*pws);
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
                    val = (*pws)[key];
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
    delete pws;

    return 0;
}
