#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <random>
using namespace std;
#define MAX numeric_limits<uint64_t>::max() 
#define MIN numeric_limits<uint64_t>::min() 
#define SQUARE_DIS(x,y) x*x+y*y
//#define CORE 8

void *msg(void* n){
    long times = (long)n;
    printf("times: %ld\n", times);
    printf("pid: %d\n", (int)pthread_self());
    mt19937 generator(time(0)+(int)pthread_self());
    uniform_int_distribution<uint64_t> distribution(MIN, MAX);
    long dart_cnt = 0;
    for(int i=0; i< times; i++){
        long double x = distribution(generator)/((long double)MAX/2) - 1;
        long double y = distribution(generator)/((long double)MAX/2) - 1;
        if(SQUARE_DIS(x, y) <= 1){
            dart_cnt++;
        }
    }
    return (void *)dart_cnt;
}

int main(int argc, char** argv){
    int CORE = sysconf(_SC_NPROCESSORS_ONLN);
    printf("core: %d\n", CORE);
    cout << "cnt:" << argv[1] << endl;
    long cnt = atoi(argv[1]);
    pthread_t threads[CORE];   
    for(int i=0; i<CORE; i++){
        long times = cnt/CORE;
        if(i==CORE-1){
            times += cnt%CORE;
        }
        pthread_create(&threads[i], NULL, msg, (void*)times);
    }
    long long int sum = 0;
    for(int i=0; i<CORE; i++){
        void *tmp;
        pthread_join(threads[i], &tmp);
        long a = (long)tmp;
        printf("hit time: %d\n", a);
        sum+=a;
    }

    printf("sum: %ld\n", sum);
    double estimate_pi = 4*sum/(double)cnt;
    printf("pi: %.8lf\n", estimate_pi);
}


