#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30


typedef struct{
   // int items[SIZE];
    char *items;
    int num;    // current no. of elements
    int head;   // index of head on tape
}Tape;

typedef struct{
    char* K;  // finite set of states
    char* input_alphabet;
    char* tape_alphabet;
    char S; // start state
    int num; // number of states
    char **transitions;   // transition format = [current state , current alphabet (a), next state , new alphabet (b) (replace a with b), action ]

}Turing_Machine;

Tape* init_tape(char* new_items, int new_num, int new_head){
    Tape* tape = malloc(sizeof(Tape));
    tape->head = new_head;
    tape->num = new_num;
    tape->items = malloc((new_num+1) * sizeof(char*));
    for(int i=0; i<new_num; i++){
        tape->items[i] = malloc(sizeof(new_items[i]));
        strcpy(tape->items[i], new_items[i]);
    }
    tape->items[new_num] = '\0';
    return tape;
}

Turing_Machine* init_TM(char* states, char* inp, char* alph, char start, int num_states, char* transitions[]){
    Turing_Machine* TM = malloc(sizeof(Turing_Machine));
    TM->K = states;
    TM->input_alphabet = inp;
    TM->tape_alphabet = alph;
    TM->S = start;
    TM->num = num_states;
    TM->transitions = malloc(num_states * sizeof(char*));

    for (int i = 0; i < num_states; i++) {
        TM->transitions[i] = malloc((strlen(transitions[i]) + 1) * sizeof(char));
        strcpy(TM->transitions[i], transitions[i]);
    }

    return TM;

}


char* string_to_array(char* string){
    int num_commas = 0;
    int len = strlen(string);

    // Count the number of commas in the input string
    for (int i = 0; i < len; i++) {
        if (string[i] == ',') {
            num_commas++;
        }
    }

    // Allocate memory for the new array excluding commas
    char* arr = malloc(len - num_commas + 1);
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int j = 0;
    char* token = strtok(string,",");  //get first element

    // loop to get the rest of the elements
    while(token != NULL){
        arr[j] = *token;
        token = strtok(NULL,",");  //get next element
        j++;
    }
    arr[j]='\0';  // end character

    return arr;
}

void display_array(char* array) {
  int i = 0;
  while (array[i] != '\0') {
    printf("%c ", array[i]);
    i++;
  }
  printf("\n");

}

void display_tape(Tape* tape) {
    for (int i = 0; i < tape->num; i++) {
        if (i == tape->head) {
            printf("[%c] ", tape->items[i]);
        } else {
            printf("%c ", tape->items[i]);
        }
    }
    printf("\n");
}

int check_in_array(char ch, char* array){  // function to check if an element exists in an array
    int i = 0;
    while (array[i] != '\0') {
        if (array[i] == ch){
            return 1;
        }
        i++;
    }
    return 0;
}

char* encode_TM(Turing_Machine* TM){
    // define string to store description of TM
    char* tape_1;

    // part 1: encode states
    // 0->1 , 1->11 , 2->111 , ...
    for(int i=0; i<strlen(TM->K); i++){
        for(int j=0; j<=i; j++){
           strcat(tape_1,'1');
        }
        strcat(tape_1,'0');
    }
    // add separator
    strcat(tape_1,'00');

    // encode


}


Tape* execute_TM(Turing_Machine* TM, Tape *tape){

    // transition format = [current state , current alphabet (a), next state , new alphabet (b) (replace a with b), action ]
    // initialize with first state
    char current_state = TM->S;

    while (1) {
        int found = 0;
        // loop through all transitions each time
        for (int i = 0; i < TM->num; i++) {
            // if one of the transitions matches my current tape state
            if (TM->transitions[i][0] == current_state && TM->transitions[i][1] == tape->items[tape->head]) {
                current_state = TM->transitions[i][2];  // change state
                tape->items[tape->head] = TM->transitions[i][3];  // change current char to new char
                char action = TM->transitions[i][4];
                if (action == 'L') {
                    tape->head--;
                } else if (action == 'R') {
                    if(tape->head == tape->num-1){  // last item
                        tape->items[tape->num]='#'; // add null
                        tape->num++;
                    }
                    tape->head++;
                } else if (action == 'N') {
                    printf("Tape rejected!\n");
                    return tape;  // Halt if action is 'N'
                } else if (action == 'Y'){
                    found = 1;
                    break;
                } else{
                    printf("ERROR! Invalid Action Encountered! Stopping program.\n");
                    exit(1);
                }

            }
        }
        display_tape(tape);
        if (found){
            printf("Tape accepted!\n");
            break;
        }
    }
    return tape;
}

int main()
{

    printf("** Welcome to Mini-Turing Machine! **\n\n");

    printf("Please enter the number of states:");
    int states_num;
    while (1) {
    if (scanf("%d", &states_num) == 1) {
      break;
    } else {
      // Input failed (non-integer)
      printf("\nInvalid input. Please enter an integer: ");
      scanf("%*[^\n]");
    }
    }

    char states_arr[states_num+1];

    for(int i = 0; i< states_num; i++){
        states_arr[i]=i+'0';
    }

//    char states_str[MAX_SIZE];  // Allocate memory for the input string
//    if (fgets(states_str, sizeof(states_str), stdin) == NULL) {
//        printf("Error reading input\n");
//        return 1;
//    }
//
//    // Remove newline character from fgets input
//    size_t states_len = strlen(states_str);
//    if (states_len > 0 && states_str[states_len - 1] == '\n') {
//        states_str[states_len - 1] = '\0';
//    }
//    char* states_arr = string_to_array(states_str);


    // ----------------------------------------------------------------------------
    printf("Please enter the set of input alphabet (separated by commas only):");
    char inp_str[MAX_SIZE];  // Allocate memory for the input string
    getchar();
    if (fgets(inp_str, sizeof(inp_str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    // Remove newline character from fgets input
    size_t inp_len = strlen(inp_str);
    if (inp_len > 0 && inp_str[inp_len - 1] == '\n') {
        inp_str[inp_len - 1] = '\0';
    }

    char* inp_arr = string_to_array(inp_str);


    // ----------------------------------------------------------------------------
    printf("Please enter the set of all alphabet (NOT including blank) (separated by commas only):");
    char alph_str[MAX_SIZE];  // Allocate memory for the input string
    if (fgets(alph_str, sizeof(alph_str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    // Remove newline character from fgets input
    size_t alph_len = strlen(alph_str);
    if (alph_len > 0 && alph_str[alph_len - 1] == '\n') {
        alph_str[alph_len - 1] = '#';
        alph_str[alph_len] = '\0';
    }

    char* alph_arr = string_to_array(alph_str);

    //----------------------------------------------------------------------------


    printf("Enter the start state: ");
    char start;
    while(1){
        scanf("%c",&start);
        if (check_in_array(start,states_arr))
            break;
        else
            printf("That state does not exist! Please enter a state from the entered states:\n");
            getchar();
    }

    //------------------------------------------------------------------------------


    printf("Enter the number of transition states: ");
    int num;

    while (1) { // Loop until valid input is received
    if (scanf("%d", &num) == 1) {
      break;
    } else {
      // Input failed (non-integer)
      printf("Invalid input. Please enter an integer:\n");
      scanf("%*[^\n]");
    }
    }
    getchar();

    char* transitions[num];

    for(int i=0; i<num; i++){
        printf("Enter the transition state number %d separated by commas:\n",i+1);
        char trans_str[MAX_SIZE];

        if (fgets(trans_str, sizeof(trans_str), stdin) == NULL) {
            printf("Error reading input\n");
            return 1;
        }

        // Remove newline character from fgets input
        size_t len = strlen(trans_str);
        if (len > 0 && trans_str[len - 1] == '\n') {
            trans_str[len - 1] = '\0';
        }

        transitions[i] = string_to_array(trans_str);
        display_array(transitions[i]);

    }

    Turing_Machine* TM = init_TM(states_arr,inp_arr,alph_arr,start,num,transitions);

    if (TM != NULL) {
        printf("Successfully created the Turing Machine.\n");
    }

    //-------------------------------------------------------------------------------

    printf("Now enter the input string. example: \"ababcba\" (without quotations) \n");
    getchar();
    char w[MAX_SIZE];  // input string
    if (fgets(w, sizeof(w), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    // Remove newline character from fgets input
    size_t my_len = strlen(w);
    if (my_len > 0 && w[my_len - 1] == '\n') {
        w[my_len - 1] = '\0';
    }

    printf("Enter the index of the head on the tape (first index is 0): ");
    int head;
    //getchar();

    while (1) {
    if (scanf("%d", &head) == 1) {
      break;
    } else {
      // Input failed (non-integer)
      printf("\nInvalid input. Please enter an integer: ");
      scanf("%*[^\n]");
    }
    }

    Tape* tape = init_tape(w,strlen(w)-1,head);

    display_tape(tape);

    //tape = execute_TM(TM, tape);








    display_array(states_arr);
    display_array(inp_arr);
    display_array(alph_arr);

    // free allocated space

    free(states_arr);
    free(inp_arr);
    free(alph_arr);

    for (int i = 0; i < num; i++) {
        free(transitions[i]);
    }

    for (int i = 0; i < num; i++) {
        free(TM->transitions[i]);
    }
    free(TM->transitions);
    free(TM);


    return 0;
}
