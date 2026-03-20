Project done for the Evolutionary Computing course I am attending at Utrecht University

The project consists in creating a evolutionary algorithm in order to study the impact of linkage and deceptivity in the fitness functions on the performance of the crossover operators. 

General description : 

This project relies on a bit-oriented-dna (length 40), each member having its own dna, randomly generated for the first generation, and a mix of parents dna for the following generations. The offspring dna is determined by a crossover, Uniform or 2-point (detailed below). Each member is then given a fitness grade depending on its dna (the different fitness functions are detailed below). The algorithm uses family competition between the 2 parents and the 2 offsprings to keep selection pressure as well as a fixed population size. 
The purpose of the project is to determine how each fitness function affects the performance of the 2 crossovers, to know which one is the most efficient to use for each case.

Experiment : 

The objective is to find the lowest population size where the algorithm finds the optimal solution (every member of the population has a string full of ones) for each fitness function and crossover type. The algorithm is considered reliable if at least 9 runs out of 10 find the optimal solution. The minimal population is found with bisection search, starting at 10 members and going up to 10000 members. For each reliable solution, I noted the average number of generations and the average execution time for the 10 runs.   

Crossover operators description : 

- 2 Points Crossover (2X) : 2 cross points are selected at random on the dna string, child 1 gets parent 1 dna inside the points and parent 2 dna outside, and invertely for child 2  
- Uniform Crossover (UX) : for each bit where both parents have the same number, both child gets this bit, whereas if the dna differ on a bit between the parents, each child gets a parent's dna on this bit (parents selected randomly) 

Fitness functions description :

- Counting Ones : Simply count the number of ones in the dna string
- Trap functions : Relies on intentionnally misleading the algorithm, by creating a "false summit" (giving higher fitness for the more 0 the string contains), making the real optimal solution hard to discover. Trap functions depends on 2 parameters Linkage and Deceptiveness.
    - Tightly Linked : the function relies on considering the string as blocks of 4 bits next to each other, giving each block a fitness
    - Non Tightly Linked : here the block logic stays but all bits of a block are considered at a distance of 10 bits (Block 1 : bit 1, bit 11, bit 21, bit 31) 

File description :

- dna.c : Base functions to generate the population and generate offsprings knowing the 2 parents
- crossovers.c : Crossover operators (UX & 2X) functions
- competition.c : Family competition function, returning the 2 best members of a family and erasing the 2 others
- fitness.c : Different fitness functions - Counting Ones & Trap functions (Tightly and not Tightly-linked, deceptiveness as a parameter with k & d)
- inputs_outputs.c : The functions on this file allow to save the parameters entered by the user into a file, as well as saving each run results into a csv file
