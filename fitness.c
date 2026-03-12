#include "fitness.h"

float count_ones(DNA *member, int k, float d){
    (void)k; (void)d;
    float count = 0;
    for(int i = 0; i < STRINGLENGHT; i++){
        count+=member->dna[i];
    }
    return count;
}

float block_fitness(int CO, int k, float d){
    if (CO == k) return k;
    else return k - d - ((k-d)*CO)/(k-1);
}

float TL_trap_fitness(DNA *member, int k, float d){
    float total_fitness = 0;
    for (int j = 0; j < STRINGLENGHT / k; j++){
        int CO = 0;
        for (int i = 0; i < k; i++) {
            if (member->dna[j * k + i] == 1) CO++;
        }
        total_fitness += block_fitness(CO, k, d);
    }
    return total_fitness;
}

float non_TL_trap_fitness(DNA *member, int k, float d){
    float total_fitness = 0;
    int gap = STRINGLENGHT / k;
    for (int j = 0; j < gap; j++){
        int CO = 0;
        for (int i = 0; i < k; i++) {
            if (member->dna[j + i*gap] == 1) CO++;
        }
        total_fitness += block_fitness(CO, k, d);
    }
    return total_fitness;
}

float evaluate_fitness(DNA *member, int k, float d, int type){
    float (*func)(DNA *, int, float);
    if (type == 1) func = count_ones;
    else if (type == 2 || type == 4) func = TL_trap_fitness;
    else func = non_TL_trap_fitness;
    return func(member, k, d);
}

float population_mean_fitness(Population *population){
    float mean = 0;
    for(int i = 0; i < population->size; i++){
        mean += population->members[i]->fitness;
    }
    return mean / population->size;
}

float population_max_fitness(Population *population){
    float max = -1000000.0;
    for(int i = 0; i < population->size; i++){
        if (population->members[i]->fitness > max) {
            max = population->members[i]->fitness;
        }
    }
    return max;
}

