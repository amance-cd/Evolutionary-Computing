#ifndef _CROSSOVERS_H_
#define _CROSSOVERS_H_

#include <stdlib.h> 
#include <stdio.h>

#include "dna.h"

void two_pt_crossover(DNA *parent1, DNA *parent2, DNA *child1, DNA *child2);
void uniform_crossover(DNA *parent1, DNA *parent2, DNA *child1, DNA *child2, float probability);




#endif