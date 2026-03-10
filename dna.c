#include "dna.h"
#include "crossovers.h"
#include "fitness.h"

//generation functions 

DNA *generate_member(int gen, int num, int k , float d, int type){
    //generates a member of the population 
    DNA *member = (DNA *)malloc(sizeof(DNA));
    for(int i = 0; i < STRINGLENGHT; i++){
        member->dna[i] = -1;
    }
    member->gen = gen;
    member->number = num;
    member->fitness = 0;
    return member;
}

void generate_random_DNA(DNA *member){
    for(int i = 0; i < STRINGLENGHT; i++){
        member->dna[i] = rand() % 2; //random function that ensures complete randomness for long strings of bits
    }
}

Population *generate_population(int size, int gen, int k, float d, int type){
    //generates a population of size size 
    Population *population = (Population *)malloc(sizeof(Population));
    population->size = size;
    population->members = (DNA **)malloc(size * sizeof(DNA *));
    for(int i = 0; i < size; i++){
        population->members[i] = generate_member(gen, i, k, d, type);
        generate_random_DNA(population->members[i]);
        population->members[i]->fitness = evaluate_fitness(population->members[i], k, d, type);
    }
    return population;
}

void shuffle_population(Population *population){
    for(int i = 0; i < population->size; i++){
        int j = rand() % population->size;
        DNA *temp = population->members[i];
        population->members[i] = population->members[j];
        population->members[j] = temp;
    }
}

void generate_offsprings(Population *population, Population *new_population, int gen, float proba, int k, float d, int type){ 
    void (*crossover_function)(DNA *, DNA *, DNA *, DNA *, float);
    if (proba == 0) crossover_function = two_pt_crossover; //proba <= 0 to use 2pt-crossover
    else crossover_function = uniform_crossover; //proba < 1 to use uniform-crossover
    new_population->size = population->size;
    new_population->members = (DNA **)malloc(new_population->size * sizeof(DNA *));

    for(int i=0; i < population->size - 1; i+=2){
        DNA *child1 = generate_member(gen, i, k, d, type);
        DNA *child2 = generate_member(gen, i+1, k, d, type);
        DNA *parent1 = population->members[i];
        DNA *parent2 = population->members[i+1];
        crossover_function(parent1, parent2, child1, child2, proba);
        child1->fitness = evaluate_fitness(child1, k, d, type);
        child2->fitness = evaluate_fitness(child2, k, d, type);
        new_population->members[i] = child1;
        new_population->members[i+1] = child2;
    }
}

//printing functions

void print_member(DNA *member){
    //prints the info of a specific member
    printf("\nnumber : %d\ngen : %d\n", member->number, member->gen);
    for(int i = 0; i < STRINGLENGHT; i++){
        printf("%d", member->dna[i]);
    }
    printf("\n");
}

void print_population(Population *population){
    //prints the info of every member of a population
    for(int i = 0; i < population->size; i++){
        print_member(population->members[i]);
    }
}

//freeing functions

void free_member(DNA *member){
    //frees a spefic member
    free(member);
}

void free_population(Population *population){
    //frees every member of a population and frees the population
    for(int i = 0; i < population->size; i++){
        free_member(population->members[i]);
    }
    free(population->members);
    free(population);
}

/*int main(){
    srand(time(NULL));
    int gen = 0;
    Population *population = generate_population(gen);
    print_population(population);
    free_population(population);
    return 0;
}*/