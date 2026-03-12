#ifndef _INPUTS_OUTPUTS_H_
#define _INPUTS_OUTPUTS_H_

#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

typedef struct inputs_{
    int generations;
    int counting_ones;
    int deceptiveness;
    int linkage;
    float crossover_probability;
    int confirm_choice;
    int fitness_function_type;
}Inputs;

//inputs functions & file
Inputs input_function();
void print_inputs(Inputs inputs);
void save_inputs_to_file(Inputs inputs, const char* filename);
int load_inputs_from_file(Inputs *inputs, const char* filename);

//csv output functions & file
int get_next_set_id(const char* filename);
void append_run_to_csv(const char* filename, int set_id, int run, int gen, double time_spent, float max_fitness, int population_size, float crossover_probability, int fitness_function_type);



#endif