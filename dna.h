#ifndef _DNA_H_
#define _DNA_H_

#include <stdlib.h> 
#include <stdio.h>


#define STRINGLENGHT 40
#define N 10

typedef struct DNA_{
    int gen;
    int number;
    int dna[STRINGLENGHT];
}DNA;

typedef struct Population_{
    DNA *members[N];
}Population;

/*typedef struct Family_{
    DNA *members[4];
}Family;*/

//generation functions
DNA *generate_member(int gen, int num);
void generate_random_DNA(DNA *member);
Population *generate_population(int gen);
void shuffle_population(Population *population);
void generate_offsprings(Population *population, Population *new_population, int gen, float proba);


//printing functions
void print_member(DNA *member);
void print_population(Population *population);

//freeing functions
void free_member(DNA *member);
void free_population(Population *population);




#endif