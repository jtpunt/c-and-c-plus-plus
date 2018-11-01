/*
 * project0.cpp
 *
 *  Created on: March 07, 2018
 *      Project: CS 475 Project #0
 *      Author: Jonathan Perry
 */
#include <omp.h>
#include <stdio.h>
#include <math.h>

// #define NUMT	                // defined in bash script
// #define ARRAYSIZE        	// defined in bash script
#define NUMTRIES        15	// you decide

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

int main(){
        #ifndef _OPENMP // does openmp exist on the current system?
                fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
                return 1;
        #endif

        omp_set_num_threads(NUMT); // sets how many # of threads will be in the thread pool
        fprintf(stderr, "Using %d threads\n", NUMT);

        double maxMegaMults = 0.;
        double sumMegaMults = 0.;
        double elapsedTime;
        for(int t = 0; t < NUMTRIES; t++){
                double time0 = omp_get_wtime();
                // creates a team of threads from the thread pool and divides the 
                // for-loop passes up among those threads
                #pragma omp parallel for
                for(int i = 0; i < ARRAYSIZE; i++){
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime();
                elapsedTime = time1 - time0;
                double megaMults = (double)ARRAYSIZE/(elapsedTime)/1000000.;
                sumMegaMults += megaMults;
                if(megaMults > maxMegaMults){
                        maxMegaMults = megaMults;
                }

        }

        double avgMegaMults = sumMegaMults/(double)NUMTRIES;
        printf("   Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults);
        printf("Average Performance = %8.2lf MegaMults/Sec\n", avgMegaMults);
        fprintf(stderr, "Elapsed time = %10.8lf seconds\n", elapsedTime);
	// note: %lf stands for "long float", which is how printf prints a "double"
	//        %d stands for "decimal integer", not "double"

        return 0;
}