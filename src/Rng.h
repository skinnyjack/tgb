#ifndef _RNG_H_
#define _RNG_H_

class Rng {
    private: 
    unsigned long int _TGB_RAND_MAX = 32767;
    unsigned long int next = 1;
    public:
        void setup_seed(unsigned long int seed);
        int next_int();
        float next_float();
        int dice(int num, int edges);
};

#endif  
