#include <stdio.h>
#include <math.h>
#include <string.h>
#include "myfuncs.h"

int normalise_axes(int dims[2], double x_axis[ dims[0] ], double y_axis[ dims[1] ]){
	/*
	 * Assigns equally spaced axis values between 0 and 1 to an array of defined dimension for each axis
	 */
	for(int i = 0; i < dims[0]; ++i){
		x_axis[i] = (double) i / (dims[0] - 1);
	}
	for(int j = 0; j < dims[1]; ++j){
		y_axis[j] = (double) j / (dims[1] - 1);
	}
}

int fprint_hist_values(FILE *hist, int N_samples, int N_iter, int N_iter_cnvg, double hist_values[N_samples][N_iter]){
	/*
	 * Prints in sequence numbered lists of historical values for each sample point to a text file.
	 */
	for(int i = 0; i < N_samples; ++i){
		for(int j = 0; j < N_iter_cnvg; ++j){
			fprintf(hist, "%d %f\n", j, hist_values[i][j]);
		}
		fprintf(hist, "\n\n");
	}
}

int contour_plot(char *address, char *title){
	/*
	 * Constructs and sends to gnuplot command string to plot nonuniform matrix psi from text file at address
	 */
	char input[512] = "\0";
	
	char *strings[]={"set contour\nset cntrparam levels incr 0, 0.05, 1\nset pm3d map\nset title \"",
					  title,
					  "\"\nsplot '",
					  address,
					  "' nonuniform matrix\n"};

	append_strings(5, strings, input);
	gnuplot_pipe(input);
	//printf("%s", input);
}