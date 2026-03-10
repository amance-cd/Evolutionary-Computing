#include "fitness.h"

float count_ones(DNA *member){
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

float population_mean_fitness_CO(Population *population){
    float mean = 0;
    for(int i = 0; i < population->size; i++){
        mean += count_ones(population->members[i]);
    }
    return mean / population->size;
}

float population_mean_fitness_trap(Population *population, int k, float d, int type){
    float mean = 0;
    float (*func)(DNA *, int, float);
    if (type) func = TL_trap_fitness;
    else func = non_TL_trap_fitness;
    for(int i = 0; i < population->size; i++){
        mean += func(population->members[i], k, d);
    }
    return mean / population->size;
}

int check_ending(Population *population, int current_gen){
    for(int i = 0; i < population->size; i++){
        if (population->members[i]->gen < current_gen - 20) return 1;
    }
    return 0;
}

