#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define PI 3.1415926535

int main(int argc, char **argv) 
{
    
    long long i, num_intervals;
    double rect_width, area, sum, x_middle; 

    sscanf(argv[1],"%llu",&num_intervals);

    rect_width = PI / num_intervals;
    
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int h = num_intervals/size+1;
    int local_min = rank * h + 1;
    int local_max = local_min + h - 1;
    local_max = local_max > num_intervals?num_intervals:local_max;


    printf("local min: %d\n", local_min);
    printf("local max: %d\n", local_max);

    sum = 0;
    /*for(i = 1; i < num_intervals + 1; i++) {

        // find the middle of the interval on the X-axis.

        x_middle = (i - 0.5) * rect_width;
        area = sin(x_middle) * rect_width; 
        sum = sum + area;
    }*/

    for(i = local_min; i<=local_max; i++){
        x_middle = (i - 0.5) * rect_width;
        area = sin(x_middle) * rect_width; 
        sum = sum + area;
    }

    MPI_Status status;
    if(rank == 0){
        double sum_area = sum;
        int proc;
        int max_prime = 0;
        for(proc = 1; proc < size; proc++){
            MPI_Recv(&sum, 1, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD, &status);
            sum_area += sum;
        }
        printf("The total area is: %f\n", (float)sum_area);

    } else {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}   
