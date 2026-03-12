#include "dna.h"
#include "crossovers.h"
#include "competition.h"
#include "inputs_outputs.h"

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
    Inputs inputs;
    int use_previous = 0;
    int population_size;
    printf("\n\nEnter population size: ");
    scanf("%d", &population_size);
    while (population_size <= 0 || population_size % 2 != 0) {
        printf("\n Population size must be a positive even number. Please enter again : ");
        scanf("%d", &population_size);
    }
    if (load_inputs_from_file(&inputs, "previous_inputs.txt")) {
        printf("\nPrevious parameters found : ");
        print_inputs(inputs);
        printf("\nDo you want to use these parameters for this run? (1 for Yes, 0 for No): ");
        scanf("%d", &use_previous);
    }
    
    if (!use_previous) {
        inputs = input_function();
        save_inputs_to_file(inputs, "previous_inputs.txt");
    }


    int generations = inputs.generations;
    int fitness_function_type = inputs.fitness_function_type;
    float crossover_probability = inputs.crossover_probability;
    
    //generation and execution
    srand(time(NULL)); // Seed the random number generator
    
    int k = 0; float d = 0;
    if (fitness_function_type != 1) {
        if (fitness_function_type == 2 || fitness_function_type == 3) {
            printf("\nSet k and d values (Usually k=4, d=1 for deceptive trap functions) : ");
            scanf("%d %f", &k, &d);
        } else {
            printf("\nSet k and d values (Usually k=4, d=2.5 for non-deceptive trap functions) : ");
            scanf("%d %f", &k, &d);
        }
    }
    int num_runs = 10;
    int next_set_id = get_next_set_id("results.csv");
    int successful_runs = 0;
    for (int run = 1; run <= num_runs; run++) {
        printf("\n\n=============== RUN %d ===============\n", run);
        int gen = 0;
        Population *population = generate_population(population_size, gen, k, d, fitness_function_type);
        gen++;
        float current_fitness = population_mean_fitness(population);
        printf("Initial population mean fitness : %.2f\n", current_fitness);

        clock_t start_time = clock();
        int stagnation_counter = 0;
        float max_fitness = population_max_fitness(population);

        while ((stagnation_counter < 20) && (gen < generations) && (max_fitness < 40.0)){
            shuffle_population(population);

            Population *offspring_population = (Population *)malloc(sizeof(Population));
            generate_offsprings(population, offspring_population, gen, crossover_probability, k, d, fitness_function_type);
            
            Population *new_population = (Population *)malloc(sizeof(Population));
            int improved = family_competition(population, offspring_population, new_population);

            if (improved) {
                stagnation_counter = 0;
            } else {
                stagnation_counter++;
            }

            current_fitness = population_mean_fitness(new_population);
            max_fitness = population_max_fitness(new_population);
            
            population = new_population;
            gen++;
        }
        clock_t end_time = clock();
        double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        if (max_fitness ==40.0) successful_runs++;
        printf("\nRun %d finished in %d generations.\n", run, gen);
        printf("Execution Time: %f seconds\n", time_spent);
        printf("Final max fitness: %.2f\n", max_fitness);

        append_run_to_csv("results.csv", next_set_id, run, gen, time_spent, max_fitness, population_size, crossover_probability, fitness_function_type);

        free_population(population);
    }
    printf("%d Succesful runs\n", successful_runs);
    printf("\nResults saved to results.csv\n");
    return 0;   
}
