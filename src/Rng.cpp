#include "Rng.h"
#include <cstdio>
void Rng::setup_seed(unsigned long int seed){
    next = seed;
}

int Rng::next_int(){
    next = next * 1664525 + 1013904223;
    //printf("\t%d\n",sizeof(unsigned int) * 8);
    return (unsigned int)(next/65536) % (this->_TGB_RAND_MAX + 1);
}

float Rng::next_float(){
    return ((float)this->next_int()) / this->_TGB_RAND_MAX;
}

int Rng::dice(int num, int edges){
    return this->next_int()%((edges-1)*num) + num+1;
}
