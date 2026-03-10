#ifndef _FITNESS_H_
#define _FITNESS_H_

#include <stdlib.h> 
#include <stdio.h>

#include "dna.h"

float count_ones(DNA *member, int k, float d);
float deceptive_trap_fitness(DNA *member, int k, float d);
float population_mean_fitness(Population *population);
int check_ending(Population *population, int current_gen);
float evaluate_fitness(DNA *member, int k, float d, int type);

#endif