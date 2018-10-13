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

    unsigned argidx(0);     // yes, I'm using the stupid "C++ style initialization" deliberately :-)
    vector<string> args;
    for (int idx(0); idx != argc; idx++) {
        args.push_back(string(argv[idx]));
    }

    // // get output .txt file name
    // string outputname(args[0]);
    // if (outputname[outputname.size() - 4] == '.') {     // kill suffix if there is a 3-char suffix
    //     outputname.erase(outputname.size() - 4, 4);
    // }
    // outputname.append(".txt");

    // Pointer to Working Stack, or PWS
    struct STACK *pws(new struct STACK);    // NOTE: throws std::bad_alloc

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
            string &str_size(args[idx]);
            int stack_size(stoi(str_size));
            if (stack_size < 0) {
                cout << "  E";
                break;
            }
            // create stack
            initSTACK(pws, stack_size);
            if (pws->elems == 0) {
                cout << "  E";
                break;
            }
            cout << "  " << stack_size;
        } else if (word == string("I")) {
            // iterate over args
            idx++;
            bool has_finished(false), error_occured(false);
            while ((!has_finished) && (idx != argc)) {
                // checking if reached next flag
                try {
                    stoi(args[idx]);
                } catch (std::invalid_argument &e) {
                    idx--;      // complementing `idx++` at end of for-loop
                    break;
                }
                // push element to working stack if no previous error
                if (!error_occured) {
                    if (push(pws, stoi(args[idx])) == 0) {  // error pushing to stack
                        cout << "  E";
                        error_occured = true;
                        break;
                    } else {
                        /* pass */
                    }
                }
                idx++;
            }
            if (!error_occured) {
                // display result
                if (howMany(pws) != 0) {
                    cout << "  ";
                    print(pws);
                } else {
                    /* pass */
                }
            } else {
                break;
            }
        } else if (word == string("O")) {
            // get number of times to pop
            idx++;
            string &str_num_pops(args[idx]);
            int num_pops(stoi(str_num_pops));
            if (num_pops < 0) {
                cout << "  E";
                break;
            }
            // start popping
            int pop_result;
            bool error_occured(false);
            for (; num_pops != 0; num_pops--) {
                if (pop(pws, pop_result) == 0) {    // error while popping
                    cout << "  E";
                    error_occured = true;
                    break;
                } else {
                    /* pass */
                }
            }
            if (error_occured) {
                break;
            } else {
                if (howMany(pws) != 0) {
                    cout << "  ";
                    print(pws);
                } else {
                    /* pass */
                }
            }
        } else if (word == string("A")) {
            idx++;
            string &str_size(args[idx]);
            int new_size(stoi(str_size));
            if (new_size < 0) {
                cout << "  E";
                break;
            }
            // create copy destination stack
            struct STACK *dststk(new struct STACK);
            initSTACK(dststk, new_size);
            if (assign(dststk, *pws) == 0) {
                cout << "  E";
                break;
            } else {
                // redirect working stack to new stack
                destroySTACK(pws);
                delete pws;
                pws = dststk;
                if (howMany(pws) != 0) {
                    cout << "  ";
                    print(pws);
                } else {
                    /* pass */
                }
            }
        } else if (word == string("C")) {
            // create new stack space
            struct STACK *dststk(new struct STACK);
            initSTACK(dststk, *pws);
            // HACK: validate using internal members
            if (dststk->elems == 0) {
                cout << "  E";
                delete dststk;
                break;
            } else {
                destroySTACK(pws);
                delete pws;
                pws = dststk;
                if (howMany(pws) != 0) {
                    cout << "  ";
                    print(pws);
                } else {
                    /* pass */
                }
            }
        } else if (word == string("N")) {
            cout << "  " << howMany(pws);
        } else if (word == string("G")) {
            // get index
            idx++;
            string &str_key(args[idx]);
            int key(stoi(str_key));
            // doability checking: if overflow
            if (key < 0 || key >= howMany(pws)) {
                cout << "  E";
                break;
            }
            cout << "  " << getelem(pws, key);
        } else {
            cout << "  E";
            break;
        }

    }   // end for

    // DEBUG OUTPUT
    // cout << endl;
    // print(pws);

    // cleaning jobs
    if (pws != 0) {
        destroySTACK(pws);
    }
    delete pws;

    return 0;
}
