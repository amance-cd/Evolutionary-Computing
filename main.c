#include "dna.h"
#include "crossovers.h"
#include "competition.h"

#include <time.h>

#define MAX_GEN 40

/*int main(){ //first tries
    srand(time(NULL));
    DNA *parent1 = generate_member(0, 0);
    DNA *parent2 = generate_member(0, 1);
    generate_random_DNA(parent1);
    generate_random_DNA(parent2);
    print_member(parent1);
    print_member(parent2);
    printf("\n");

    DNA *child1 = generate_member(0, 2);
    DNA *child2 = generate_member(0, 3);
    uniform_crossover(parent1, parent2, child1, child2, 0.5);
    print_member(child1);
    print_member(child2);
    printf("\n");
    
    free_member(parent1);
    free_member(parent2);
    free_member(child1);
    free_member(child2);
    return 0;   
}*/

/*int main(){
    srand(time(NULL));
    int gen = 0;
    Population *population = generate_population(gen);
    shuffle_population(population);
    print_population(population);
    printf("Parent population mean fitness : %f\n\n", population_mean_fitness(population));
    Population *offspring_population = (Population *)malloc(sizeof(Population));
    gen++;
    generate_offsprings(population, offspring_population, gen);
    print_population(offspring_population);
    printf("Offspring population mean fitness : %f\n\n", population_mean_fitness(offspring_population));
    Population *new_population = (Population *)malloc(sizeof(Population));
    family_competition(population, offspring_population, new_population);
    print_population(new_population);
    printf("New population mean fitness : %f\n\n", population_mean_fitness(new_population));;
    free_population(new_population);
    return 0;   
}*/

/*int main(){
    srand(time(NULL));
    int gen = 0;
    Population *population = generate_population(gen);
    int k; float d;
    k = 4; d = 1; //deceptive
    //k = 4; d = 2.5; //non_deceptive
    print_population(population);
    printf("\n\nInitial population mean fitness : %.2f", population_mean_fitness_TL(population, k, d, 0));
    for(gen = 1; gen < MAX_GEN; gen++){
        printf("\n\nGeneration %d\n", gen);
        shuffle_population(population);
        //print_population(population);
        //printf("Parent population mean fitness : %f\n", population_mean_fitness(population));

        Population *offspring_population = (Population *)malloc(sizeof(Population));
        generate_offsprings(population, offspring_population, gen, 0.5);
        //print_population(offspring_population);
        //printf("Offspring population mean fitness : %f\n", population_mean_fitness(offspring_population));
        
        Population *new_population = (Population *)malloc(sizeof(Population));
        family_competition(population, offspring_population, new_population);
        //print_population(new_population);
        printf("New population mean fitness : %.2f\n", population_mean_fitness_TL(new_population, k, d, 0));
        
        population = new_population;
    }
    print_population(population);
    free_population(population);
    return 0;   
}*/


int main() {
    #if EXP == 1
        int crossover_type = 1; // Uniform Crossover
    #elif EXP == 2
        int crossover_type = 2; // 2-point Crossover
    #else
        int crossover_type = 1; // Uniform Crossover
    #endif
    srand(time(NULL));
    int gen = 0;
    Population *population = generate_population(gen);
    int k; float d;
    k = 4; d = 1; //deceptive
    //k = 4; d = 2.5; //non_deceptive
    print_population(population);
    printf("\n\nInitial population mean fitness : %.2f", population_mean_fitness_TL(population, k, d, 0));
    for(gen = 1; gen < MAX_GEN; gen++){
        printf("\n\nGeneration %d\n", gen);
        shuffle_population(population);
        //print_population(population);
        //printf("Parent population mean fitness : %f\n", population_mean_fitness(population));

        Population *offspring_population = (Population *)malloc(sizeof(Population));
        generate_offsprings(population, offspring_population, gen, 0.5);
        //print_population(offspring_population);
        //printf("Offspring population mean fitness : %f\n", population_mean_fitness(offspring_population));
        
        Population *new_population = (Population *)malloc(sizeof(Population));
        family_competition(population, offspring_population, new_population);
        //print_population(new_population);
        printf("New population mean fitness : %.2f\n", population_mean_fitness_TL(new_population, k, d, 0));
        
        population = new_population;
    }
    print_population(population);
    free_population(population);
    return 0;   
}
