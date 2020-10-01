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
    U initial_state; /* Starting state. */
    int iteration /* Keeps track of which state to compute on. */;
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
            /* Currently converts a digit to base 0. */
            V v;
            
            if(in % 2 == 0) {
                v = 0;
            } else {
                v = 1;
            } 
        
            return v;
        }

        /* Gets the next state from the input to place state register. */
        void next_state(U input) {
            U state = states.at(iteration);
            V output = transition(input);
            states.push_back(output);
            instructions[input] = output;
            ++iteration;
        }

        /* Returns the output set as a list. */
        std::vector<int> get_output() {
            return states;
        }

        void run_input(int  *array_in, int input_size) {
            for(int i = 1; i < input_size; i++)  {
                next_state(array_in[i]);
            }
        }
        
        int* get_user_input(int digits) {
            int arr [digits];
            
            while(i < sizeof(arr)) {
                std::cout << "Enter a digit: ";
                std::cin >> arr[i];
                i++;   
            }

            return *arr;
        }

};


/* Testing */
int main(){
    /* Following two variables used for generating random numbers. */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-250, 250);

    /* Create a new state machine and try it out with test inputs. */
    StateMachine<int, int> state_machine(0);
    int digits;
    int *input_array;

    std::cout << "Enter digits in number: ";
    std::cin >> digits;

    input_array = state_machine.get_user_input(digits);


    std::vector<int> output_set;

    /* Run machine on input and get the output. */
    state_machine.run_input(input_array, sizeof(input_array));
    output_set = state_machine.get_output();
    std::string output;
    
    for(int i = 0; i < state_machine.get_output().size(); i++) {
        output += std::to_string(output_set.back()); // Gets the last added element.
        output_set.pop_back();      // pops that element out so the next can be accessed the next time. 
    }

    std::cout << " " + output;
}
