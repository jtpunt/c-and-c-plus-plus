// Name: Jonathan Perry
// Class: CS 475
// Date: 5/21/18
// Assignment: Project #5
#include "simd.p5.h"
#include <omp.h>
#include <stdio.h>
#include <fstream>
float a[ARRAYSIZE];
float b[ARRAYSIZE];
float c[ARRAYSIZE];
void SimdMul(float *a, float *b, float *c, int len){
	int limit = (len/SSE_WIDTH) * SSE_WIDTH;
	__asm(
		".att_syntax\n\t"
		"movq    -24(%rbp), %rbx\n\t"		// a
		"movq    -32(%rbp), %rcx\n\t"		// b
		"movq    -40(%rbp), %rdx\n\t"		// c
	);

	for(int i = 0; i < limit; i += SSE_WIDTH){
		__asm(
			".att_syntax\n\t"
			"movups	(%rbx), %xmm0\n\t"	// load the first sse register
			"movups	(%rcx), %xmm1\n\t"	// load the second sse register
			"mulps	%xmm1, %xmm0\n\t"	// do the multiply
			"movups	%xmm0, (%rdx)\n\t"	// store the result
			"addq $16, %rbx\n\t"
			"addq $16, %rcx\n\t"
			"addq $16, %rdx\n\t"
		);
	}

	for(int i = limit; i < len; i++){
		c[i] = a[i] * b[i];
	}
}

void selfMul(float *a, float *b, float *c, int len){
	for(int i = 0; i < len; i++){
		c[i] = a[i] * b[i];
	}
}

float SimdMulSum(float *a, float *b, int len){
	float sum[4] = {0., 0., 0., 0.};
	int limit = (len/SSE_WIDTH) * SSE_WIDTH;

	__asm(
		".att_syntax\n\t"
		"movq    -40(%rbp), %rbx\n\t"		// a
		"movq    -48(%rbp), %rcx\n\t"		// b
		"leaq    -32(%rbp), %rdx\n\t"		// &sum[0]
		"movups	 (%rdx), %xmm2\n\t"		// 4 copies of 0. in xmm2
	);

	for(int i = 0; i < limit; i += SSE_WIDTH){
		__asm(
			".att_syntax\n\t"
			"movups	(%rbx), %xmm0\n\t"	// load the first sse register
			"movups	(%rcx), %xmm1\n\t"	// load the second sse register
			"mulps	%xmm1, %xmm0\n\t"	// do the multiply
			"addps	%xmm0, %xmm2\n\t"	// do the add
			"addq $16, %rbx\n\t"
			"addq $16, %rcx\n\t"
		);
	}

	__asm(
		".att_syntax\n\t"
		"movups	 %xmm2, (%rdx)\n\t"	// copy the sums back to sum[ ]
	);

	for(int i = limit; i < len; i++){
		sum[i-limit] += a[i] * b[i];
	}
	return sum[0] + sum[1] + sum[2] + sum[3];
}
float selfMulSum(float *a, float *b, int len){
	float sum = 0.0;
	for(int i = 0; i < len; i++){
		sum += a[i] * b[i];
	}
	return sum;
}

int main(){
    #ifndef _OPENMP // does openmp exist on the current system?
        fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
        return 1;
    #endif

    double maxMegaMults = 0.;
    double sumMegaMults = 0.;
    double elapsedTime;


    for(int t = 0; t < NUMTRIES; t++){
       	double time0 = omp_get_wtime();

       	// Use the supplied SIMD SSE code to run an array multiplication timing experiment. 
       	#if TEST == 1
       	// Run the same experiment a second time using your own c/c++ multiplication code.
       		SimdMul(a, b, c, ARRAYSIZE);
       	#endif
       	#if TEST == 2
       		selfMul(a, b, c, ARRAYSIZE);
       	#endif
       	// Use the supplied SIMD see code to runan array multiplication + reduction timing experiment.
       	#if TEST == 3
       		float simdRes = SimdMulSum(a, b, ARRAYSIZE);
       	#endif
       	#if TEST == 4
       		// Run the same experiment a second time using your own c/c++ array multiplication + reduction code
       		float selfRes = selfMulSum(a, b, ARRAYSIZE);
       	#endif

       	elapsedTime = omp_get_wtime() - time0;
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
}