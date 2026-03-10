#ifndef _DNA_H_
#define _DNA_H_

#include <stdlib.h> 
#include <stdio.h>


#define STRINGLENGHT 40

typedef struct DNA_{
    int gen;
    int number;
    int dna[STRINGLENGHT];
    float fitness;
}DNA;

typedef struct Population_{
    int size;
    DNA **members;
}Population;

typedef struct Family_{
    int size;
    DNA *members[4];
}Family;

//generation functions
DNA *generate_member(int gen, int num, int k , float d, int type);
void generate_random_DNA(DNA *member);
Population *generate_population(int size, int gen, int k, float d, int type);
void shuffle_population(Population *population);
void generate_offsprings(Population *population, Population *new_population, int gen, float proba, int k, float d, int type);


//printing functions
void print_member(DNA *member);
void print_population(Population *population);

//freeing functions
void free_member(DNA *member);
void free_population(Population *population);




#endif