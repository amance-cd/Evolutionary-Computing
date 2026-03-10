#include "crossovers.h"

void two_pt_crossover(DNA *parent1, DNA *parent2, DNA *child1, DNA *child2, float ghost_var){
    (void)ghost_var; //avoids the warning of unused variable, ghost_var is present to make the function signature the same as uniform_crossover
    int pt1 = 5 + rand() % (STRINGLENGHT-10); //assigns a random point on the string 
    int pt2 = -1;
    while ((pt2==pt1)||(pt2==-1)){ //makes sure the two points are different 
        pt2 = 5 + rand() % (STRINGLENGHT-10);
    }
    if (pt2 < pt1){ //makes sure pt1 < pt2
        int temp = pt2;
        pt2 = pt1;
        pt1 = temp;
    }
    //printf("pt1 : %d\npt2 : %d\n", pt1, pt2); to know where the crossover happens
    int i;
    for(i = pt1; i<=pt2; i++){
        child1->dna[i] = parent1->dna[i];
        child2->dna[i] = parent2->dna[i];
    }
    for(i=0; i<STRINGLENGHT; i++){
        if (child1->dna[i] == -1){
            child1->dna[i] = parent2->dna[i];
            child2->dna[i] = parent1->dna[i];
        }
    }
    /*DNA *p = parent1;
    for(int j=0; j<2; j++){ //verifies that the crossover works (tried with stringlength 8 to see it easier)
        if (j==1){
            p = parent2;
        }
        printf("Parent %d\n", j+1);
        for (i=0; i<STRINGLENGHT; i++){
            printf("%d", p->dna[i]);
            if (i==pt1){
                printf("\npt1\n");
            }
            if (i==pt2){
                printf("\npt2\n");
            }
        }
        printf("\n");
    }*/
}

void uniform_crossover(DNA *parent1, DNA *parent2, DNA *child1, DNA *child2, float probability){
    int b;
    for(int i = 0; i<STRINGLENGHT; i++){
        if(parent1->dna[i]==parent2->dna[i]){
            child1->dna[i] = parent1->dna[i];
            child2->dna[i] = parent1->dna[i];
        }
        else{
            b = rand() % (int)(1/probability);
            if(b){
                child1->dna[i] = parent1->dna[i];
                child2->dna[i] = parent2->dna[i];
            }
            else{
                child1->dna[i] = parent2->dna[i];
                child2->dna[i] = parent1->dna[i];
            }
        }
    }
    /*DNA *p = parent1;
    for(int j=0; j<2; j++){ //verifies that the crossover works (tried with stringlength 8 to see it easier)
        if (j==1){
            p = parent2;
        }
        printf("Parent %d\n", j+1);
        for (int i=0; i<STRINGLENGHT; i++){
            printf("%d", p->dna[i]);
        }
        printf("\n");
    }*/
}