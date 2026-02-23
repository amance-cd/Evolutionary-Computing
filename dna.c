#include "dna.h"
#include "crossovers.h"


//generation functions 

DNA *generate_member(int gen, int num){
    //generates a member of the population 
    DNA *member = (DNA *)malloc(sizeof(DNA));
    for(int i = 0; i < STRINGLENGHT; i++){
        member->dna[i] = -1;
    }
    member->gen = gen;
    member->number = num;
    return member;
}

void generate_random_DNA(DNA *member){
    for(int i = 0; i < STRINGLENGHT; i++){
        member->dna[i] = rand() % 2; //random function that ensures complete randomness for long strings of bits
    }
}

Population *generate_population(int gen){
    //generates a population of size N 
    Population *population = (Population *)malloc(sizeof(Population));
    for(int i = 0; i < N; i++){
        population->members[i] = generate_member(gen, i);
        generate_random_DNA(population->members[i]);
    }
    return population;
}

void shuffle_population(Population *population){
    for(int i = 0; i < N; i++){
        int j = rand() % N;
        DNA *temp = population->members[i];
        population->members[i] = population->members[j];
        population->members[j] = temp;
    }
}

void generate_offsprings(Population *population, Population *new_population, int gen){
    for(int i=0; i<N-1; i+=2){
        DNA *child1 = generate_member(gen, i);
        DNA *child2 = generate_member(gen, i+1);
        DNA *parent1 = population->members[i];
        DNA *parent2 = population->members[i+1];
        two_pt_crossover(parent1, parent2, child1, child2);
        //uniform_crossover(parent1, parent2, child1, child2, 0.5);
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
    for(int i = 0; i < N; i++){
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
    for(int i = 0; i < N; i++){
        free_member(population->members[i]);
    }
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