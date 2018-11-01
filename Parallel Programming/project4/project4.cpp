// Name: Jonathan Perry
// Date: 5/14/18
// Project #4 - CS 475
// 1. You will create a month-by-month simulation in which each agent fo the simulation will 
//    execute in its own thread where it just has to look at the state of the world around it
//    and react to it.
// 2. You will also get to exercise your creativity by adding an addition "agent" to the simulation,
//    one that impacts the state of the other agents and is impacted by them.
// 3. You will spawn three threads (four, when you add your own agent)
// 4. The GrainGrowth and GrainDeer threads will compute the next grain height and the next number 
//    of deer based on the current set of global state variables. They will compute these into local,
//    temporary, variables. They both then will hit the DoneComputing barrier.
// 5. At that point, both of these threads are done computing using the current set of global state
//    variables. Each thread should then copy the local variables into the global version. All 3
//    threads will then hit the DoneAssigning barrier.
// 6. At this point, the watcher thread will print the current set of global state variables, increment
//    the month count, and then use the new Temperature and Precipitation. Note that the GrainGrowth and
//    GrainDeer threads can proceed because there's a chance they would re-compute the global state variables
//    before they are done being printed. All 3 threads will then hit the DonePrinting barrier.
// 7. After spawning the threads, the main program should wait for the parallel sections to finish.
// 8. Each thread should return when the year hits 2023 (giving us 6 years, or 72 months, of simulation).
#include "omp.h"
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <string>
using std::string;
// The "state" of the system
int	NowYear;     // 2017 - 2022
int	NowMonth;    // 0 - 11
float NowPrecip; // inches of rain per month
float NowTemp;	 // temperature this month
float NowHeight; // grain height in inches
int	NowNumDeer;	 // number of deer in the current population
int NowDeadDeer; // # of deer that died during hunting seasons

const float AVG_DEER_DEATHS_PER_MONTH = 15.0;
const float GRAIN_GROWS_PER_MONTH     =	 8.0; // units of grain growth are inches
const float ONE_DEER_EATS_PER_MONTH   =  0.5;
const float AVG_PRECIP_PER_MONTH      =	 6.0; // average, units=inches
const float AMP_PRECIP_PER_MONTH      =	 6.0; // plus or minus, units=inches
const float RANDOM_PRECIP             =	 2.0; // plus or minus noise, units=inches
const float AVG_TEMP                  = 50.0; // average, units=degrees Fahrenheight
const float AMP_TEMP                  = 20.0; // plus or minus, units=degrees Fahrenheight
const float RANDOM_TEMP               = 10.0; // plus or minus noise, units=degrees Fahrenheight
const float MIDTEMP                   = 40.0; // units=degrees Fahrenheight
const float MIDPRECIP                 = 10.0; // units=inches

// Function Prototypes
float Ranf(unsigned int *seedp, float low, float high);
int getMonth();
void GrainDeer();
void Grain();
void HuntingSeason();
void Flood();
void Watcher();

float SQR(float x){
    return x*x;
}
float Ranf(unsigned int *seedp, float low, float high){
    float r = (float) rand_r( seedp );
    return (low  +  r*(high - low)/(float)RAND_MAX);
}
int Ranf(unsigned int *seedp, int ilow, int ihigh){
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;

    return (int)(  Ranf(seedp, low,high) );
}
int getMonth(){
	return NowMonth + 12 * (NowYear - 2017);
}
void GrainDeer(){
	int grainDeer;
	while(NowYear < 2023){
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		grainDeer = NowNumDeer;
		// The Carrying Capacity of the graindeer is the # of inches of height of the grain. 
		// If the # of graindeer exceeds this value at the end of a month, decrease the # of graindeer by 1
		if(grainDeer > NowHeight){
			grainDeer--;
		}
		// If the # of graindeer is less than this value at the end of a month, increase the # of graindeer by 1
		else if(grainDeer < NowHeight){
			grainDeer++;
		}
		// DoneComputing barrier:
		#pragma omp barrier
		NowNumDeer = grainDeer;
		// DoneAssigning barrier:
		#pragma omp barrier
		
		// DonePrinting barrier:
		#pragma omp barrier
	}
}
// Each month you will need to figure out how much the grain grows.
void Grain(){
	float height, tempFactor, precipFactor;
	while(NowYear < 2023){
		// If conditions are good, it will grow by GRAIN_GROWS_PER_MONTH
		// If conditions are not good, it won't.
		// You can calculate how good conditions are by seeing how close you are to an ideal temp degrees F) and precip. 
		// Do this by computing a temperature factor and a Precipitation Factor:
		tempFactor = exp(-SQR((NowTemp - MIDTEMP)/10.));
		precipFactor = exp(-SQR((NowPrecip - MIDPRECIP)/10.));

		// DoneComputing barrier:
		#pragma omp barrier
		NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
 		NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
 		if(NowHeight < 0){
 			NowHeight = 0;
 		}
		// DoneAssigning barrier:
		#pragma omp barrier
 		
		// DonePrinting barrier:
		#pragma omp barrier
	}
}
void HuntingSeason(){
	float remainingDeer;
	while(NowYear < 2023){
		// Hunting Season Months for White-Tailed Deer in Texas: November, December, and January
		if(NowMonth == 0 || NowMonth == 10 || NowMonth == 11){
			// 5 % of deer die a month each season, so 95% gives us the # of deer that remain
			// after the season is over. etc. 100 * (100 - 5/100) = 100 * (.95). Then, use floor
			// on the remaining # of deer to round down, as half a deer = a dead deer. 
			remainingDeer = floor(NowNumDeer*(100 - AVG_DEER_DEATHS_PER_MONTH)/100);
			NowDeadDeer = NowNumDeer - remainingDeer;
		}else{ // Off-season, no hunting allowed
			NowDeadDeer = 0;
		}
		// DoneComputing barrier:
		#pragma omp barrier
		// if NowNumDeer is set to 0, the population will have trouble stabilizing to be > 0
		if(remainingDeer > 1){
			NowNumDeer = remainingDeer;
		}
		// DoneAssigning barrier:
		#pragma omp barrier
 		
		// DonePrinting barrier:
		#pragma omp barrier
	}
}
void Watcher(){
	unsigned int seed = 0;
	float temp, height, precip;
	while(NowYear < 2023){

		// DoneComputing barrier:
		#pragma omp barrier
		
		// DoneAssigning barrier:
		#pragma omp barrier
		temp = (5. / 9.) * (NowTemp - 32);
		height = 2.54 * NowHeight;
		precip = 2.54 * NowPrecip;
		printf("%d, %-2f, %.2f, %.2f, %d, %d\n", getMonth(), temp, precip, height, NowNumDeer, NowDeadDeer);
		// printf("%-2d, %d, temp: %-6.2f°F, precip: %-5.2f, height: %-5.2fcm, Num of Deer:%d, Dead Deer: %d\n", getMonth(), NowYear, temp, precip, height, NowNumDeer, NowDeadDeer);

	
		if(++NowMonth > 11){
			NowMonth = 0;
			NowYear++;
		}


		float ang = (30.*(float)NowMonth + 15.)*(M_PI / 180.);
		// Set Temp
		float temp = AVG_TEMP - AMP_TEMP * cos(ang);
		NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);
		// Set Precip
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
		NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
		if(NowPrecip < 0.){
			NowPrecip = 0.;
		}
		// DonePrinting barrier:
		#pragma omp barrier
	}
}

int main(){
	#ifndef _OPENMP // does openmp exist on the current system?
        fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
        return 1;
    #endif
    // starting date and time:
	NowMonth =    0;
	NowYear  = 2017;

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	NowHeight =  1.;




    omp_set_num_threads(4);	// same as # of sections
	#pragma omp parallel sections
	{
		#pragma omp section
		{	
			GrainDeer();	
		}

		#pragma omp section
		{
			Grain();
		}

		#pragma omp section
		{
			Watcher();
		}

		#pragma omp section
		{
			HuntingSeason();	// your own
		}
	} // implied barrier -- all functions must return in order
	// to allow any of them to get past here
}