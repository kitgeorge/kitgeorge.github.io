#include <stdio.h>
#include <math.h>
#include "myfuncs.h"

int over_relax(int dims[2], double alpha, double psi[ dims[0] ][ dims[1] ], int coords[2]){
	/*
	 * Perform the over-relaxation method on an element of psi,
	 * using the values of adjacent matrix elements
	 *
	 * Input:
	 * * coords_sequence[i, j]: row and column indices of psi element to be manipulated.
	 * * dims: dimensions of psi matrix
	 *
	 * Input/output:
	 * * psi: subject matrix, whose element with indices \coords is manipulated
	 *   based on adjacent element values.
	 */
	int *x = coords;
	double R = psi[ x[0] ][ x[1] + 1 ] + psi[ x[0] ][ x[1] - 1 ] +
	           psi[ x[0] - 1 ][ x[1] ] + psi[ x[0] + 1 ][ x[1] ] -
			   4 * psi[ x[0] ][ x[1] ];
	
	psi[ x[0] ][ x[1] ] = psi[ x[0] ][ x[1] ] + alpha*R/4;
}

int check_point_converging(int N_samples, int N_iter, double hist_values[N_samples][N_iter], int sample_no, int cnvg_count[N_samples], int iter_no){
	/*
	 * Adds 1 to a sample's tally of convergence if its value is close enough to a previous one. Otherwise reverts tally to zero.
	 */
	if(pow((hist_values[sample_no][iter_no] - hist_values[sample_no][iter_no-1]), 2) < 0.00000000000001) cnvg_count[sample_no] = cnvg_count[sample_no] + 1;
	else cnvg_count[sample_no] = 0;
}

int check_points_converged(int N_samples, int cnvg_count[N_samples]){
	/*
	 * Returns 1 if every sample has a convergence tally above 100 (all have converged)
	 */
	for(int i = 0; i < N_samples; ++i){
		if(cnvg_count[i] < 100) return 0;
	}
	return 1;
}