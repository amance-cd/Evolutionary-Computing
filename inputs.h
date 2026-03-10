#ifndef _INPUTS_H_
#define _INPUTS_H_

#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

typedef struct inputs_{
    int population_size;
    int generations;
    int counting_ones;
    int deceptiveness;
    int linkage;
    float crossover_probability;
    int confirm_choice;
}Inputs;

Inputs input_function();
void print_inputs(Inputs inputs);
void save_inputs_to_file(Inputs inputs, const char* filename);
int load_inputs_from_file(Inputs *inputs, const char* filename);



#endif