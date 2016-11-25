#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int isprime(int n) {
    int i,squareroot;
    if (n>10) {
        squareroot = (int) sqrt(n);
        for (i=3; i<=squareroot; i=i+2)
            if ((n%i)==0)
                return 0;
            return 1;
    }
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int pc,       /* prime counter */
    foundone = 0; /* most recent prime found */
    long long int n, limit;
    int size, rank;
    
    sscanf(argv[1],"%llu",&limit);    
    printf("Starting. Numbers to be scanned= %lld\n",limit);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //printf("size: %d\n", size);
    //printf("rank: %d\n", rank);

    pc=4;     /* Assume (2,3,5,7) are counted here */
    
    int singlePc = 0;

    /*for (n=11; n<=limit; n=n+2) {
        if (isprime(n)) {
            pc++;
            foundone = n;
        }            
    }*/

    int h = limit/size;

    int local_min = (rank*h)+11;
    if(!(local_min%2))
        local_min++;

    int local_max = local_min + h - 2;
    local_max = local_max > limit ? limit:local_max;

    //printf("local min: %d\n", local_min);
    //printf("local max: %d\n", local_max);
    for(n = local_min; n<=local_max; n=n+2){
        if(isprime(n)){
            singlePc++;
            if(n>foundone){
                foundone = n;
            }
        }
    }

    //printf("single pc:%d\n", singlePc);
    
    MPI_Status status;
    if(rank == 0){
        pc+=singlePc;
        int proc;
        int max_prime = 0;
        for(proc = 1; proc < size; proc++){
            MPI_Recv(&singlePc, 1, MPI_INT, proc, 0, MPI_COMM_WORLD, &status);
            pc+=singlePc;
            MPI_Recv(&foundone, 1, MPI_INT, proc, 1, MPI_COMM_WORLD, &status);
            if(max_prime < foundone){
                max_prime = foundone;
            }
        }
        //printf("total: %d\n", pc);
        printf("Done. Largest prime is %d Total primes %d\n",foundone,pc);
    } else {
        MPI_Send(&singlePc, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&foundone, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
} 
