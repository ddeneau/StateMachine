#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <stdexcept>

using namespace std;

/* Takes in input(s) and computes the set of corresponding output(s).
   Right now, all it can do is convert base-10 integers to binary.  */
template <class U, class V>
class StateMachine {
    std::vector<U> states; /* Recorded states. */
    std::vector<V> outputs; /* Recorded outputs. */
    U initial_state; /* Starting state. */
    int iteration; /* Keeps track of which state to compute on. */;
    map <U, V> instructions; /* All inputs mapped to their outputs.*/

     public:
        /* Take in input and create state machine.
        @param start - the starting element in the computation.  */
        StateMachine(U start) {
            initial_state = start;
            iteration = 0;
            states.push_back(initial_state);
        }
        
        /* Gets the output for the input. For future: Design class template with the feature, and use that to pass as parameter.
        @param in - the input variable.
        @return - the output for that input.  */
        V transition(U in) {
            V v;
            int i = 0;
            
           while(i < 8) {
               if(in % 2 == 0) {
                   v += '0';
               } else if(in % 2 == 1) {
                   v += '1';
               }

               in = in / 2;
               ++i;
           }

            return v;
        }

        /* Gets the next state from the input to place state register. 
        @param input - the input variable. */
        void next_state(U input) {
            U state = states.at(iteration);
            V output = transition(input);
            states.push_back(input);
            outputs.push_back(output);
            instructions[input] = output;
            ++iteration;
        }

        /* Returns the output set as a list. 
        @return - The list of outputs. */
        std::vector<V> get_output() {
            return outputs;
        }

        /* Calculates the output for a set of input.
        @param input - the inputs to be computed on. 
        @param input_size - the size of the input.  */
        void run_input(std::vector<int> input, int input_size) {
            for(int i = 0; i < input_size; i++)  {
                try {
                    next_state(input.at(i));
                }

                catch(std::out_of_range) {
                    std::cerr << "Must fit within 8 bits." << '\n';
                }
            }
        }

};

/* Reverses strings of binary representations of numbers. 
@param str - the original string. 
@param n - the length of the string. 
@return - the reversed version of str.  */
string reverse(string str, int n) {
    string new_str;

    for(int i = n - 1; i >= 0; i--) {
        new_str += str[i];
    } 

    return new_str;
}

/* Testing */
int main() {
    /* Following two variables used for generating random numbers. */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-250, 250);

    /* Create a new state machine and try it out with test inputs. */
    StateMachine<int, string> state_machine(0);
    std::cout << "Enter input size: ";
    int n;
    std::cin >> n;
    std::vector<int> inputs;

    while(inputs.size() < n) {
        int in;
        std::cout << "Enter a number: ";
        std::cin >> in;
        inputs.push_back(in);
    }

    /* Run machine on input and get the output. */
    state_machine.run_input(inputs, n);
    std::vector<string> outputs = state_machine.get_output();
    string results = "";

    for(int i = 0; i < outputs.size(); i++) {
        string term = outputs.at(i);
        results += reverse(term, term.length()) + '\n';
    }

    std::cout << results;
}
