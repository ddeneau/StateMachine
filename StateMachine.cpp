#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <map>

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
        /* Take in input and create state machine. */
        StateMachine(U start) {
            initial_state = start;
            iteration = 0;
            states.push_back(initial_state);
        }
        
        /* Gets the output for the input. For future: Design class template with the feature, and use that to pass as parameter.*/
        V transition(U in) {
            V v;
            
            if(in % 2 == 0) {
                v = '0';
            } else {
                v = '1';
            } 
        
            return v;
        }

        /* Gets the next state from the input to place state register. */
        void next_state(U input) {
            U state = states.at(iteration);
            V output = transition(input);
            states.push_back(input);
            outputs.push_back(output);
            instructions[input] = output;
            ++iteration;
        }

        /* Returns the output set as a list. */
        std::vector<V> get_output() {
            return outputs;
        }

        void run_input(std::vector<int> input, int input_size) {
            for(int i = 1; i < input_size; i++)  {
                next_state(input.at(i));
            }
        }

};

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
}
