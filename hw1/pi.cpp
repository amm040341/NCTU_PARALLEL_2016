#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int intRand(const int & min, const int & max) {
    static  mt19937 generator;
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

void *msg(void* n){
    int times = *((int*)n);
    printf("%d", intRand(0, 100));
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


