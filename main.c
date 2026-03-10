#include "dna.h"
#include "crossovers.h"
#include "competition.h"

#include <time.h>

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
    
    //inputs
    int population_size, generations, crossover_type, counting_ones, deceptiveness, linkage;
    
    //Population size input
    printf("Enter population size: ");
    scanf("%d", &population_size);
    while (population_size <= 0 || population_size % 2 != 0) {
        printf("\n Population size must be a positive even number. Please enter again : ");
        scanf("%d", &population_size);
    }

    //Number of generations input
    printf("\nEnter number of generations: \n");
    scanf("%d", &generations);
    while (generations <= 0) {
        printf("\nNumber of generations must be a positive integer. Please enter again : ");
        scanf("%d", &generations);
    }

    //Crossover type input
    printf("\nEnter crossover type : \n   - 0 for two-point\n   - 1 for uniform: ");
    scanf("%d", &crossover_type);
    while (crossover_type < 0 || crossover_type > 1) {
        printf("\nCrossover type must be 0 or 1. Please enter again : ");
        scanf("%d", &crossover_type);
    }
    float crossover_probability;
    if (crossover_type == 1) {
        printf("\nSelect crossover probability (usually 0.5) : ");
        scanf("%f", &crossover_probability);
        while (crossover_probability <= 0 || crossover_probability >= 1) {
            printf("\nCrossover probability must be in the range (0, 1). Please enter again : ");
            scanf("%f", &crossover_probability);
        }
    }else crossover_probability = 0; //crossover_probability is not used for two-point crossover

    //confirmation of parameters 
    

    //Fitness function type input
    printf("\nFitness function type : Use Counting Ones? \n    - 1 for Yes\n    - 0 for No\n   Selection : ");
    scanf("%d", &counting_ones);
    while (counting_ones < 0 || counting_ones > 1) {
        printf("\nCounting Ones choice must be 0 or 1. Please enter again : ");
        scanf("%d", &counting_ones);
    }
    if (!counting_ones) {
        printf("\nSelect deceptiveness: \n");
        printf("- 0 for Non-Deceptive trap function\n    - 1 for Deceptive trap function\n   Selection : ");
        scanf("%d", &deceptiveness);
        while (deceptiveness < 0 || deceptiveness > 1) {
            printf("\nDeceptiveness choice must be 0 or 1. Please enter again : ");
            scanf("%d", &deceptiveness);
        }
        printf("\nSelect linkage: \n");
        printf("- 0 for Non-Tightly Linked trap function\n    - 1 for Tightly Linked trap function\n   Selection : ");
        scanf("%d", &linkage);
        while (linkage < 0 || linkage > 1) {
            printf("\nLinkage choice must be 0 or 1. Please enter again : ");
            scanf("%d", &linkage);
        }
    }

    //generation and execution
    srand(time(NULL)); // Seed the random number generator
    int gen = 0;
    Population *population = generate_population(population_size, gen);
    print_population(population);
    
    //counting ones fitness function
    if (counting_ones) {
        printf("\nInitial population mean fitness : %.2f", population_mean_fitness_CO(population));
        for(gen = 1; gen < generations; gen++){
        printf("\n\nGeneration %d\n", gen);
        shuffle_population(population);
        //print_population(population);
        //printf("Parent population mean fitness : %f\n", population_mean_fitness(population));

        Population *offspring_population = (Population *)malloc(sizeof(Population));
        
        generate_offsprings(population, offspring_population, gen, crossover_probability);
        //print_population(offspring_population);
        //printf("Offspring population mean fitness : %f\n", population_mean_fitness(offspring_population));
        
        Population *new_population = (Population *)malloc(sizeof(Population));
        family_competition(population, offspring_population, new_population);
        //print_population(new_population);
        printf("New population mean fitness : %.2f\n", population_mean_fitness_CO(new_population));
        
        population = new_population;
        }
    }

    else { //trap fitness functions
        int k; float d;
        if (deceptiveness) {
            printf("\nSet k and d values : (Usually k=4, d=1 for deceptive trap functions)\n");
            scanf("%d %f", &k, &d);
        } else {
            printf("\nSet k and d values : (Usually k=4, d=2.5 for non-deceptive trap functions)\n");
            scanf("%d %f", &k, &d);
        }
        printf("\n\nInitial population mean fitness : %.2f", population_mean_fitness_trap(population, k, d, linkage));
        for(gen = 1; gen < generations; gen++){
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
            printf("New population mean fitness : %.2f\n", population_mean_fitness_trap(new_population, k, d, linkage));
            
            population = new_population;
        }
    }
    print_population(population);
    free_population(population);
    return 0;   
}
