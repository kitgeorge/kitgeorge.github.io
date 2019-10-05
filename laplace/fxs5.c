#include <stdio.h>
#include <math.h>
#include <string.h>
#include "myfuncs.h"

int get_analytic_values(int dims[2], double analytic_psi[ dims[0] ][ dims[1] ]){
    /*
	 * Sets matrix values to represent known solution for Laplace equation with these boundary conditions.
	 */
	for(int i = 0; i < dims[0]; ++i){
		for(int j = 0; j < dims[1]; ++j){
			analytic_psi[i][j] = sin((double)i / (dims[0] - 1)) * sinh((double)j / (dims[1] - 1));
		}
	}
}

int get_analytic_deviation(int dims[2], double psi[ dims[0] ][ dims[1] ], double analytic_psi[ dims[0] ][ dims[1] ], double psi_dev[ dims[0] ][ dims[1] ]){
	/*
	 * Subtracts analytic solution from psi matrix to give difference matrix.
	 */
	
	for(int i = 0; i < dims[0]; ++i){
		for(int j = 0; j < dims[1]; ++j){
			psi_dev[i][j] = psi[i][j] - analytic_psi[i][j];
		}
	}
}

int fprint_psi_nonuniform(FILE *stream, int dims[2], double psi[ dims[0] ][ dims[1] ]){
	/*
	 * Print psi matrix to text file, along with axis values for gnuplot nonuniform 
	 * matrix plotting.
	 */
	double x_axis[ dims[0] ];
	double y_axis[ dims[1] ];
	normalise_axes(dims, x_axis, y_axis);
	 
	fprintf(stream, "%d ", dims[0]);
	for(int i = 0; i < dims[0]; ++i){
		fprintf(stream, "%f ", x_axis[i]);
	} // Prints x axis on first line
	
	for (int j = 0; j < dims[1]; ++j){
		fprintf(stream, "\n%f ", y_axis[j]);
		for(int i = 0; i < dims[0]; ++i){
			fprintf(stream, "%f ", psi[i][j]);
		}
	} // Prints y axis value then row of psi values on each subsequent line.
}