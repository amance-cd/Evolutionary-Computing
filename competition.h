#ifndef _COMPETITION_H_
#define _COMPETITION_H_

#include <stdlib.h> 
#include <stdio.h>

#include "dna.h"
#include "fitness.h"

void sort_by_fitness_family(DNA *family[4], DNA **res1, DNA **res2);
void family_competition(Population *parent_population, Population *offspring_population, Population *new_population);



#endif