#include <stdio.h>
#include <math.h>
#include "myfuncs.h"

int get_sample_coords(int dims[2], int N_samples, int sample_coords[N_samples][2]){
	/*
	 * Returns array of coordinates of approximately evenly spaced matrix elements
	 * approximately down the middle of the matrix. (Every coordinate is rounded up)
	 */
	 
	int j = dims[1]/2;
	
	for(int i = 0; i < N_samples; ++i){
		sample_coords[i][0] = (i + 1) * dims[0] / (N_samples + 1);
		sample_coords[i][1] = j;
	}
}

int iterate_sequential_relax_record(int dims[2], double alpha, int N_iter, int N_samples, int sequence_length, 
									double psi[ dims[0] ][ dims[1] ], double hist_values[N_samples][N_iter],
									int coords_sequence[sequence_length][2], int sample_coords[N_samples][2]){
	/*
	 * Runs over-relaxation on each coordinate in "snake path" sequence around matrix psi, then records values at coordinates
	 * sample_coords to hist_values. Repeats for at most N_iter iterations, but checks for convergence of hist_values and stops
	 * if converged. Returns number of iterations done. Inputted psi is overwritten without.
	 */
	int cnvg_count[N_samples];
	
	for(int iter_no = 1; iter_no <= N_iter; ++iter_no){
		
		for(int i = 0; i < sequence_length; ++i){
			over_relax(dims, alpha, psi, coords_sequence[i]);
		}
		
		for(int j = 0; j < N_samples; ++j){
			hist_values[j][iter_no] = psi[ sample_coords[j][0] ][ sample_coords[j][1] ];
			check_point_converging(N_samples, N_iter, hist_values, j, cnvg_count, iter_no);
		}
		
		if(check_points_converged(N_samples, cnvg_count)) return iter_no;
	}
}