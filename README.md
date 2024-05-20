# Turing Machine Simulator

**Author**: Jana Essam   
**Course**: Switching Theory and Models of Computation

## Overview

This program simulates a basic Turing Machine. It allows users to input the machine's states, alphabets, transitions, and an input string, and then simulates the execution of the Turing Machine on that string. It also provides an encoded representation of the Turing Machine.

## Features

- Initialize and display a Turing Machine with user-defined states, input alphabets, tape alphabets, transitions, and start state.
- Simulate the execution of the Turing Machine on an input string.
- Display the tape during each step of the execution.
- Encode the Turing Machine into a simplified string format.

## How to Use

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/username/mini-turing-machine.git
    cd mini-turing-machine
    ```

2. **Compile the Code**:
    ```bash
    gcc main.c -o turing_machine
    ```

3. **Run the Program**:
    ```bash
    ./turing_machine
    ```

4. **Follow the On-Screen Instructions**:
    - Enter the number of states.
    - Enter the set of input alphabets.
    - Enter the set of all alphabets (including blank).
    - Enter the start state.
    - Enter the number of transition states.
    - Enter each transition state in the format: `current_state,current_alphabet,next_state,new_alphabet,action`.
    - Enter the input string.
    - Enter the index of the head on the tape.

## Example Usage

```plaintext
** Welcome to Mini-Turing Machine! **

Please enter the number of states: 3
Please enter the set of input alphabet (separated by commas only): a,b
Please enter the set of all alphabet (including blank) (separated by commas only): a,b,_
Enter the start state: 0
Enter the number of transition states: 2
Enter the transition state number 1 separated by commas: 0,a,1,b,R
Enter the transition state number 2 separated by commas: 1,b,0,a,L
Now enter the input string. example: "ababcba" (without quotations): ab
Enter the index of the head on the tape (first index is 0): 0
```
## Sample Run:

![image](https://github.com/JanaElnagar/Turing-Machine/assets/108252869/eed64a49-52ac-4765-89e8-516e8b4037e3)

## Functions

- `Tape* init_tape(char new_items[], int new_num, int new_head)`: Initializes the tape with given items, number of items, and head position.
- `Turing_Machine* init_TM(char* states, char* inp, char* alph, char start, int num_states, char* transitions[])`: Initializes the Turing Machine with given states, input alphabets, tape alphabets, start state, number of transitions, and transition states.
- `char* string_to_array(char* string)`: Converts a comma-separated string to an array of characters.
- `void display_array(char* array)`: Displays the elements of an array.
- `void display_tape(Tape* tape)`: Displays the current state of the tape.
- `int check_in_array(char ch, char* array)`: Checks if a character exists in an array.
- `char* encode_TM(Turing_Machine* TM)`: Encodes the Turing Machine into a simplified string format.
- `Tape* execute_TM(Turing_Machine* TM, Tape* tape)`: Executes the Turing Machine on the given tape.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements

This project was developed as part of the Switching Theory and Models of Computation course. Special thanks to the course instructors and peers for their support and guidance.

---

Feel free to explore and contribute to the project. For any issues or suggestions, please open an issue or submit a pull request.


