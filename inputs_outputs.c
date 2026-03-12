#include "inputs_outputs.h"

//inputs
Inputs input_function(){
    int generations, crossover_type, counting_ones, deceptiveness, linkage, fitness_function_type;
    float crossover_probability = 0;
    int confirm_choice = 0;

    //Population size input
    do {

        //Number of generations input
        printf("\nEnter number of generations: ");
        scanf("%d", &generations);
        while (generations <= 0) {
            printf("\nNumber of generations must be a positive integer. Please enter again : ");
            scanf("%d", &generations);
        }

        //Crossover type input
        printf("\nEnter crossover type : \n   - 0 for two-point\n   - 1 for uniform\n   Selection : ");
        scanf("%d", &crossover_type);
        while (crossover_type < 0 || crossover_type > 1) {
            printf("\nCrossover type must be 0 or 1. Please enter again : ");
            scanf("%d", &crossover_type);
        }
    
        if (crossover_type == 1) {
            printf("\nSelect crossover probability (usually 0.5) : ");
            scanf("%f", &crossover_probability);
            while (crossover_probability <= 0 || crossover_probability >= 1) {
                printf("\nCrossover probability must be in the range (0, 1). Please enter again : ");
                scanf("%f", &crossover_probability);
            }
        }
        
        //Fitness function type input
        printf("\nFitness function type : Use Counting Ones? \n    - 0 for No\n    - 1 for Yes\n    Selection : ");
        scanf("%d", &counting_ones);
        while (counting_ones < 0 || counting_ones > 1) {
            printf("\nCounting Ones choice must be 0 or 1. Please enter again : ");
            scanf("%d", &counting_ones);
        }
        if (!counting_ones) {
            printf("\nSelect deceptiveness: \n");
            printf("    - 0 for Non-Deceptive trap function\n    - 1 for Deceptive trap function\n    Selection : ");
            scanf("%d", &deceptiveness);
            while (deceptiveness < 0 || deceptiveness > 1) {
                printf("\nDeceptiveness choice must be 0 or 1. Please enter again : ");
                scanf("%d", &deceptiveness);
            }
            printf("\nSelect linkage: \n");
            printf("    - 0 for Non-Tightly Linked trap function\n    - 1 for Tightly Linked trap function\n    Selection : ");
            scanf("%d", &linkage);
            while (linkage < 0 || linkage > 1) {
                printf("\nLinkage choice must be 0 or 1. Please enter again : ");
                scanf("%d", &linkage);
            }
        }
        if (counting_ones) {
            fitness_function_type = 1;
        } else if (deceptiveness && linkage) {
            fitness_function_type = 2;
        } else if (deceptiveness && !linkage) {
            fitness_function_type = 3;
        } else if (!deceptiveness && linkage) {
            fitness_function_type = 4;
        } else {
            fitness_function_type = 5;
        }

        //parameters confirmation
        Inputs temp_inputs = {generations, counting_ones, deceptiveness, linkage, crossover_probability, confirm_choice, fitness_function_type};
        print_inputs(temp_inputs);
        
        printf("\nDo you want to proceed with these parameters? (1 to confirm, 0 to change): ");
        scanf("%d", &confirm_choice);
        
        if (confirm_choice != 1) {
            printf("\nRestarting parameter selection\n\n");
        }

    } while (confirm_choice != 1);

    return (Inputs){generations, counting_ones, deceptiveness, linkage, crossover_probability, confirm_choice, fitness_function_type};
}

void print_inputs(Inputs inputs) {
    printf("\n--- Parameter Confirmation ---\n");
    printf("Generations           : %d\n", inputs.generations);
    printf("Crossover type        : %s\n", inputs.crossover_probability == 0 ? "Two-point" : "Uniform");
    if (inputs.crossover_probability != 0) {
    printf("Crossover probability : %.2f\n", inputs.crossover_probability);
    }
    printf("Fitness function      : %s\n", inputs.counting_ones ? "Counting Ones" : "Trap Function");
    if (!inputs.counting_ones) {
        printf("Deceptiveness         : %s\n", inputs.deceptiveness ? "Deceptive" : "Non-Deceptive");
        printf("Linkage               : %s\n", inputs.linkage ? "Tightly Linked" : "Non-Tightly Linked");
    }
}

void save_inputs_to_file(Inputs inputs, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%d %d %d %d %f %d %d\n", 
            inputs.generations, inputs.counting_ones, inputs.deceptiveness, inputs.linkage, 
            inputs.crossover_probability, inputs.confirm_choice, inputs.fitness_function_type);
        fclose(file);
    }
}

int load_inputs_from_file(Inputs *inputs, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        int res = fscanf(file, "%d %d %d %d %f %d %d", 
            &inputs->generations, &inputs->counting_ones, &inputs->deceptiveness, &inputs->linkage, 
            &inputs->crossover_probability, &inputs->confirm_choice, &inputs->fitness_function_type);
        fclose(file);
        return res == 7; // return 1 if all 7 fields were read successfully
    }
    return 0; // File does not exist or error reading
}

// CSV outputs functions
int get_next_set_id(const char* filename) {
    int next_set_id = 1;
    FILE *csv_read = fopen(filename, "r");
    if (csv_read != NULL) {
        char line[256];
        int last_set_id = 0;
        // Skip header
        if (fgets(line, sizeof(line), csv_read) != NULL) {
            while (fgets(line, sizeof(line), csv_read) != NULL) {
                int current_set;
                if (sscanf(line, "%d,", &current_set) == 1) {
                    if (current_set > last_set_id) {
                        last_set_id = current_set;
                    }
                }
            }
        }
        next_set_id = last_set_id + 1;
        fclose(csv_read);
    }
    return next_set_id;
}

void append_run_to_csv(const char* filename, int set_id, int run, int gen, double time_spent, float max_fitness, int population_size, float crossover_probability, int fitness_function_type) {
    const char* crossover_str = (crossover_probability == 0) ? "2X" : "UX";
    const char* fitness_str;
    switch(fitness_function_type) {
        case 1: fitness_str = "Counting Ones"; break;
        case 2: fitness_str = "Deceptive TL Trap"; break;
        case 3: fitness_str = "Deceptive Non-TL Trap"; break;
        case 4: fitness_str = "Non-Deceptive TL Trap"; break;
        case 5: fitness_str = "Non-Deceptive Non-TL Trap"; break;
        default: fitness_str = "Unknown"; break;
    }

    FILE *csv_file = fopen(filename, "a");
    if (csv_file != NULL) {
        // Only write header if the file is new/empty
        fseek(csv_file, 0, SEEK_END);
        if (ftell(csv_file) == 0) {
            fprintf(csv_file, "Set ID,Run,Generations,Execution Time (s),Population Size,Success (Max=40),Crossover,Fitness Function\n");
        }
        
        int success = (max_fitness >= 40.0) ? 1 : 0;
        fprintf(csv_file, "%d,%d,%d,%f,%d,%d,%s,%s\n", set_id, run, gen, time_spent, population_size, success, crossover_str, fitness_str);
        fclose(csv_file);
    }
}