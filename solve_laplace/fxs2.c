#include <stdio.h>
#include <math.h>
#include "myfuncs.h"

int find_greatest_boundaries(int dims[2], double psi[ dims[0] ][ dims[1] ], int highbounds[2]){
	/*
	 * This function checks which of each pair of opposing sides of a matrix \psi has
	 * the greater mean square value of elements, and returns a pair of booleans.
	 *
	 * Input:
	 * * psi: 2D matrix to be checked.
	 * * dims: dimensions of psi matrix
	 * 
	 * Output (externally declared):
	 * * highbounds: [0] = 1 for bottom row, [1] = 1 for rightmost column respectively
	 *	 having greater mean square of elements than top row and leftmost column,
	 *   zero otherwise in each case
	 */
	double meansquare[2][2]; 
	for(int j = 0; j < dims[1]; ++j){
		meansquare[0][0] = meansquare[0][0] + pow(psi[0][j], 2)/dims[1];
		meansquare[0][1] = meansquare[0][1] + pow(psi[ dims[0] - 1 ][j], 2)/dims[1];
	}
	for(int i = 0; i < dims[0]; ++i){
		meansquare[1][0] = meansquare[1][0] + pow(psi[i][0], 2)/dims[0];
		meansquare[1][1] = meansquare[1][1] + pow(psi[i][ dims[1] - 1 ], 2)/dims[0];
	}
	for(int a = 0; a < 2; ++a){
		highbounds[a] = meansquare[a][1] > meansquare[a][0];
	}
}

int gen_coords_sequence(int dims[2], int sequence_length, int coords_sequence[sequence_length][2], 
                      int highbounds[2]){
	/*
	 * Knowing which sides of the matrix in question have greater mean square of  
	 * elements than their opposing sides, this function gives a sequence of 
	 * coordinates of all elements except all edge elements of the matrix, starting 
	 * at the corner of said sides and ending at the opposing corner, which goes 
	 * along each row in sequence, always in the same direction.
	 *
	 * Input:
	 * * dims: dimensions of matrix
	 * * highbounds: [0] = 1 for top row, [1] = 1 for rightmost column respectively
	 *	 having greater mean square of elements than bottom row and leftmost column,
	 *   zero otherwise in each case
	 *
	 * Output (externally declared):
	 * * coords_sequence: sequence of matrix element coordinate pairs.
	 */
	
	int start_coords[2];
	int coords_step[2];
	for(int a = 0; a < 2; ++a){
		start_coords[a] = highbounds[a] * (dims[a]-3) + 1;
		coords_step[a] = 1 - 2*highbounds[a];
	}
	int count = 0;
	for(int i = start_coords[0]; 0 < i && i < dims[0] - 1; i = i + coords_step[0])
	{
		for(int j = start_coords[1]; 0 < j && j < dims[1] - 1; j = j + coords_step[1])
		// for(int j = dims[1] - 1 - start_coords[1]; 0 < j && j < dims[1] - 1; j = j - coords_step[1])
		{
			coords_sequence[count][0] = i;
			coords_sequence[count][1] = j;
			++count;
		}
	}
}