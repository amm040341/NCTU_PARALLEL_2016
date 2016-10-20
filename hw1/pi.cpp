#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <random>
using namespace std;

double Rand(const uint64_t & min, const uint64_t & max) {
    static mt19937 generator;
    uniform_int_distribution<uint64_t> distribution(min,max);
    return (double)distribution(generator)/((double)max/2) - 1;
}

void *msg(void* n){
    int times = *((int*)n);
    while(1)
        printf("%.20lf\n", Rand(0, numeric_limits<uint64_t>::max()));
}

int main(int argc, char** argv){
    int id[4] = {1, 2, 3, 4};
    cout << "cnt:" << argv[1] << endl;
    pthread_t threads[4];   
    for(int i=0; i<4; i++){
        pthread_create(&threads[i], NULL, msg, (void*)(id+i));
    }
    for(int i=0; i<4; i++){
        pthread_join(threads[i], NULL);
    }
}


