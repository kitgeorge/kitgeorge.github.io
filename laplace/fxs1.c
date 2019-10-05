#include <stdio.h>
#include <math.h>
#include "myfuncs.h"

int psi_gen(int dims[2], double psi[ dims[0] ][ dims[1] ]){
	/*
	 * Sets matrix elements to cover initial psi function, with boundary conditions, 
	 * between (0, 0) and (1, 1).
	 * Index [0] corresponds to x values, index [1] corresponds to y values
	 */
	
	set_zeros(dims, psi);
	
	set_bound_funcs(dims, psi);
}

int set_zeros(int dims[2], double psi[ dims[0] ][ dims[1] ]){
	/*
	 * Sets matrix of specified dimensions to zero
	 */
	for(int i = 0; i < dims[0]; ++i){
		for(int j = 0; j < dims[1]; ++j){
			psi[i][j] = 0;
		}
	}
}

int set_bound_funcs(int dims[2], double psi[ dims[0] ][ dims[1] ]){
	/*
	 * Sets psi values to match boundary conditions at x = 1 and y = 1
	 */
	
	const double sin1 = sin(1);
	const double sinh1 = sinh(1); // avoids repeated calculation of sin(1), sinh(1)
	for(int i = 0; i < dims[0]; ++i){
		psi[i][ dims[1] - 1 ] = sin((double)i / (dims[0] - 1)) * sinh1;
	}
	for(int j = 0; j < dims[1] - 1; ++j){
		psi[ dims[0] - 1 ][j] = sin1 * sinh((double)j / (dims[1] - 1));
	}
}	