#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <map>

using namespace std;

/* Takes in input(s) and computes the set of corresponding output(s). */
template <class i, class o>
class StateMachine {
    std::vector<i> states; /* Recorded states. */
    int initial_state; /* Starting state. */
    int iteration /* Keeps track of which state to compute on. */;
    map <i, o> instructions; /* All inputs mapped to their outputs.*/

     public:
        /* Take in input and create state machine. */
        StateMachine() {
            initial_state = 0;
            iteration = 0;
            states.push_back(initial_state);
        }

        /* Gets the next state from the input to place state register. */
        void next_state(int input) {
            int state = states.at(iteration);
            int output = state + input / states.size();
            states.push_back(output);
            instructions[input] = output;
            ++iteration;
        }

        /* Returns the output set as a list. */
        std::vector<int> get_output() {
            return states;
        }
};

int main(){
    /* Following two variables used for generating random numbers. */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-250, 250);

    /* Create a new state machine and try it out with test inputs. */
    StateMachine<int, string>  state_machine;
    for(int i = 1; i < 10; i++) 
        state_machine.next_state(i);
}