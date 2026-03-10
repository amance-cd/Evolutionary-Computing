#ifndef _FITNESS_H_
#define _FITNESS_H_

#include <stdlib.h> 
#include <stdio.h>

#include "dna.h"

float count_ones(DNA *member);
float deceptive_trap_fitness(DNA *member, int k, float d);
float population_mean_fitness_CO(Population *population);
float population_mean_fitness_trap(Population *population, int k, float d, int type);



#endif