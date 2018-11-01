// Name: Jonathan Perry
// Date: 5/4/18
// Project #3 - CS 475
// 1. Apply Fix #1 from the notes, i.e., pad the rest of the struct with a certain number,
//    NUM, of integers. Set NUM to 0, 1, 2, 3,..., 15, 16 (and more if you want).
// 2. Use a variety of # of threads. At least 1,2, and 4. You can use more if you'd like.
// 3. If you are doing this from a script, note that: int pad[NUM]; is a legal C statement,
//    even when NUM is #define'd as 0 (at least in g++). It works like you think it should.
// 4. Use OpenMP's timer calls to time the length of execution. As always, change the elapsed
//    time into a sensible unit of performance.
// 5. Apply Fix #2 from the notes, i.e., accumulate the sum in a variable that is private to
//    each thread.
//    - NUMPAD does not come in play at all here. So you could just commend out out the pad variable
// 6. Plot, on the same set of axes, Performance vs. NUM for 1 thread, 2 threads, etc.
// 7. Plot, also on that same set of axes, horizontal lines showing what performance resulted
//    from Fix #2.
#include <omp.h>
#include <stdio.h>
#include <fstream>
using std::ofstream;
#define NUMTRIES 15
struct s{
	float value;
	int pad[NUMPAD]; 
} myArray[ARRAYSIZE]; // if you wanna do more cores, change 4 to another #

int main(){
    #ifndef _OPENMP // does openmp exist on the current system?
        fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
        return 1;
    #endif
	omp_set_num_threads(NUMT);
	double maxMegaAdds = 0.;
	double sumMegaAdds = 0.;
	double elapsedTime = 0.;
	int someBigNumber = 1000000000;

	double time0 = omp_get_wtime();
	#if FIX == 1
		printf("Trying fix #1.\n\n");
		#pragma omp parallel for
		for(int i = 0; i < ARRAYSIZE; i++){
			for(int j = 0; j < someBigNumber; j++){
				myArray[i].value = myArray[i].value + 2.;
			}
		}
	#endif
	#if FIX == 2
		printf("Trying fix #2.\n\n");
		#pragma omp parallel for
		for(int i = 0; i < ARRAYSIZE; i++){
			float temp = myArray[i].value;
			for(int j = 0; j < someBigNumber; j++){
				temp += myArray[i].value + 2.;
			}
			myArray[i].value = temp;
		}
	#endif
	elapsedTime = omp_get_wtime() - time0;
	double megaAdds = (float)(someBigNumber)/(elapsedTime)/1000000.;
	sumMegaAdds += maxMegaAdds;
	if(megaAdds > maxMegaAdds){
		maxMegaAdds = megaAdds;
	}

	printf("Peak Performance = %8.2lf MegaAdds/Sec\n", maxMegaAdds);
	printf("            Time = %8.2lf Seconds\n\n", elapsedTime);
}