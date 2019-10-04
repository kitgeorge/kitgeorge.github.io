#include <stdio.h>
#include "myfuncs.h"

int solve_laplace(int dims[2], double alpha, int N_iter, int N_samples,
				  double psi[ dims[0] ][ dims[1] ], 
				  double hist_values[N_samples][N_iter + 1]){
	/*
	 * Author: Kit George, Date: 30/04/2019
	 * This function solves the Laplace equation using the over-relaxation method
	 * Input:
	 * * psi: 2D matrix containing the initial \psi, including boundaries.
	 * * dims: dimensions of init_psi matrix {no. rows, no. columns}
	 * * alpha: the coefficient of over-relaxation.
	 * * N_iter: maximum number of iterations performed.
	 * * N_samples: number of sample points to be tracked
	 *
	 * Output: 
	 * * Returns number of iterations done (until converged)
	 * * Overwritten input variables:
	 * * * psi: 2D matrix of the value of \psi after (up to) N_iter iterations.
	 * * * hist_values: (N_iter x N_samples) matrix that contains historical values of 
	 *   	  N_samples points during the iteration (spread evenly down the middle of 
	 *   	  the matrix). Includes initial and final values.
	 *
	 * Constraints:
	 * * The boundaries of \psi are kept constant during the iterations.
	 *
	 * Example use:
	 * >> int dims[2] = {7, 7};
	 * >> int N_iter = 30 
	 * >> double alpha = 1.1;
	 * >> double init_psi[dims[0]][dims[1]], psi[dims[0]][dims[1]];
	 * >> int hist_values[3][N_iter + 1];
	 * >> for(int i = 0; i < dims[0]; ++i){
	 * >> 	for(int j = 0; j < dims[1]; ++j){
	 * >> 		if(i == 0 || j == 0 || i == dims[0] || j == dims[1]) init_psi[i][j] = 1;
	 * >> 		else init_psi[i][j] = 0;
	 * >> 	}
	 * >> }
	 * >> solve_laplace(dims, alpha, N_iter, 3, psi, hist_values);
	 */

	int highbounds[2];
	find_greatest_boundaries(dims, psi, highbounds);
	
	int sequence_length = (dims[0] - 2) * (dims[1] - 2); // boundaries not included in coordinates for over-relaxation
	int coords_sequence[sequence_length][2];
	gen_coords_sequence(dims, sequence_length, coords_sequence, highbounds); // gives "snake" path through coordinates for over-relaxation
	
	int sample_coords[N_samples][2];
	get_sample_coords(dims, N_samples, sample_coords); // coords for hist. sampling
							
	return(iterate_sequential_relax_record(dims, alpha, N_iter, N_samples, sequence_length, psi, hist_values, 
									coords_sequence, sample_coords));
}