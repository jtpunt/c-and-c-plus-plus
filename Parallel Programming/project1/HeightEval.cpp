/*
 * HeightEval.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: jtpunt
 */

#include <omp.h>
#include <stdio.h>
#include <math.h>
// Data coordinates to get Delta Height
#define XMIN	 0. // Grid of nodes goes from
#define XMAX	 3. // 0 to 3 in terms of x
#define YMIN	 0. // Grid of nodes goes from
#define YMAX	 3. // 0 to 3 in terms of y
// x/y tells you that the title size is going to be 3 / NUMNODES - 1
#define TOPZ00  0.
#define TOPZ10  1.
#define TOPZ20  0.
#define TOPZ30  0.

#define TOPZ01  1.
#define TOPZ11  6.
#define TOPZ21  1.
#define TOPZ31  0.

#define TOPZ02  0.
#define TOPZ12  1.
#define TOPZ22  0.
#define TOPZ32  4.

#define TOPZ03  3.
#define TOPZ13  2.
#define TOPZ23  3.
#define TOPZ33  3.

#define BOTZ00  0.
#define BOTZ10  -3.
#define BOTZ20  0.
#define BOTZ30  0.

#define BOTZ01  -2.
#define BOTZ11  10.
#define BOTZ21  -2.
#define BOTZ31  0.

#define BOTZ02  0.
#define BOTZ12  -5.
#define BOTZ22  0.
#define BOTZ32  -6.

#define BOTZ03  -3.
#define BOTZ13   2.
#define BOTZ23  -8.
#define BOTZ33  -3.
/***********************************************************************************
* Param: iu - current x coordinate
* Param: iv - current y coordinate
* Post:  Height is calculated based on the distance between two surfaces
* Ret:   Height between two surfaces is returned
************************************************************************************/
float Height(int iu, int iv){	// iu,iv = 0 .. NUMNODES-1
	float u = (float)iu / (float)(NUMNODES-1); // Tile size
	float v = (float)iv / (float)(NUMNODES-1); // Tile size

	// the basis functions:
	// Bezier surface 1
	float bu0 = (1.-u) * (1.-u) * (1.-u);
	float bu1 = 3. * u * (1.-u) * (1.-u);
	float bu2 = 3. * u * u * (1.-u);
	float bu3 = u * u * u;
	// Bezier surface 2
	float bv0 = (1.-v) * (1.-v) * (1.-v);
	float bv1 = 3. * v * (1.-v) * (1.-v);
	float bv2 = 3. * v * v * (1.-v);
	float bv3 = v * v * v;

	// finally, we get to compute something:
	// Top
    float top = bu0 * (bv0*TOPZ00 + bv1*TOPZ01 + bv2*TOPZ02 + bv3*TOPZ03) + 
    			bu1 * (bv0*TOPZ10 + bv1*TOPZ11 + bv2*TOPZ12 + bv3*TOPZ13) + 
    			bu2 * (bv0*TOPZ20 + bv1*TOPZ21 + bv2*TOPZ22 + bv3*TOPZ23) + 
    			bu3 * (bv0*TOPZ30 + bv1*TOPZ31 + bv2*TOPZ32 + bv3*TOPZ33);
    // Bottom
    float bot = bu0 * (bv0*BOTZ00 + bv1*BOTZ01 + bv2*BOTZ02 + bv3*BOTZ03) + 
    			bu1 * (bv0*BOTZ10 + bv1*BOTZ11 + bv2*BOTZ12 + bv3*BOTZ13) + 
    			bu2 * (bv0*BOTZ20 + bv1*BOTZ21 + bv2*BOTZ22 + bv3*BOTZ23) + 
    			bu3 * (bv0*BOTZ30 + bv1*BOTZ31 + bv2*BOTZ32 + bv3*BOTZ33);
    // Top - Bottom = Height at that uv combination
    return top - bot;	// if the bottom surface sticks out above the top surface
						// then that contribution to the overall volume is negative
}
/***********************************************************************************
* Param: iu - current x coordinate
* Param: iv - current y coordinate
* Param: volume - current volume of a full tile
* Post:  volume is halved if iu coordinate is at an edge parallel to the y-axis
*        to adjust the volume for a half tile
* Post:  volume is halved if iv coordinate is at an edge parallel to the x-axis
*        to adjust the volume for a half tile
* Post:  volume is halved if both iv/iu is at an edge parallel to the y/x-axis
*        to adjust the volume for a quarter tile
* Ret:   The correct volume for a full tile, half tile, or quarter tile is returned
************************************************************************************/
double adjVolume(int &iu, int &iv, double volume){
	// Are we looking at an edge point that's parallel to the y-axis?
	if(iu == 0 || iu == NUMNODES - 1){
		volume *= 0.5;
	}
	// Are we looking at an edge point that's parallel to the x-axis?
	if(iv == 0 || iv == NUMNODES - 1){
		volume *= 0.5;
	}
	return volume;
}
int main(int argc, char *argv[]){
	#ifndef _OPENMP // does openmp exist on the current system?
        fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
        return 1;
   	#endif
    double maxMegaMults = 0.;
    double sumMegaMults = 0.;
	double totalVolume = 0.;
	double elapsedTime;
    // the area of a single full-sized tile:
    float fullTileArea = (XMAX - XMIN)/(float)(NUMNODES-1) * (YMAX - YMIN)/(float)(NUMNODES-1);
	omp_set_num_threads(NUMTHREADS);

	// sum up the weighted heights into the variable "volume" using an OpenMP for loop and a reduction:
	double start = omp_get_wtime();
	#pragma omp parallel for default(none), shared(fullTileArea), reduction(+:totalVolume)
	for(int i = 0; i < NUMNODES*NUMNODES; i++){
		int iu = i % NUMNODES; // X = 0 .. NUMNODES - 1
		int iv = i / NUMNODES; // Y = 0 .. NUMNODES - 1
		// calculate the full volume, where fullTileArea = length * width of the current node at iu, iv on the x/y axis
		totalVolume += adjVolume(iu, iv, fullTileArea*Height(iu, iv));
	}
	double stop = omp_get_wtime();
	elapsedTime = stop - start;
	double megaMults = (double)(NUMNODES*NUMNODES)/(elapsedTime)/1000000.; // correct - according to piazza
    sumMegaMults += megaMults;
    if(megaMults > maxMegaMults){
        maxMegaMults = megaMults;
    }
	printf("NUMTHREADS: %d, NUMNODES: %d, volume: %lf, maxMegaMults: %lf, time: %lf\n", NUMTHREADS, NUMNODES, totalVolume, maxMegaMults, elapsedTime);
}

