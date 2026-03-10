#include "competition.h"

void sort_by_fitness_family(DNA *family[4], DNA **res1, DNA **res2){
    float max1 = -1;
    float max2 = -1;
    *res1 = NULL;
    *res2 = NULL;
    for (int i = 0; i < 4; i++){
        if (family[i]->fitness > max1){
            max2 = max1;
            *res2 = *res1; // Old 1st place becomes 2nd place
            max1 = family[i]->fitness;
            *res1 = family[i];
        }
        else if (family[i]->fitness > max2){
            max2 = family[i]->fitness;
            *res2 = family[i];
        }
    }
} 

void family_competition(Population *parent_population, Population *offspring_population, Population *new_population){
    new_population->size = parent_population->size;
    new_population->members = (DNA **)malloc(new_population->size * sizeof(DNA *));

    for (int i = 0; i < parent_population->size; i+=2){
        DNA *family[4];
        family[0] = parent_population->members[i];
        family[1] = parent_population->members[i+1];
        family[2] = offspring_population->members[i];
        family[3] = offspring_population->members[i+1];
        DNA *res1, *res2;
        sort_by_fitness_family(family, &res1, &res2);
        new_population->members[i] = res1;
        new_population->members[i+1] = res2;
        for(int j = 0; j < 4; j++) { // Find which ones to free
            if(family[j] != res1 && family[j] != res2) free_member(family[j]);
        }
    }
    // Free the populations structures
    free(parent_population);
    free(offspring_population);
}