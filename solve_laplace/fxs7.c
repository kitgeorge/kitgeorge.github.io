#include <stdio.h>
#include <math.h>
#include <string.h>
#include "myfuncs.h"

int append_strings(int N, char *strings[N], char *main_string){
	for(int i = 0; i < N; ++i){
		strcat(main_string, strings[i]);
	}
}

int gnuplot_pipe(char *string){
	/*
	 * Passes command string to gnuplot.
	 */
	FILE *gpipe = popen("gnuplot -persistent", "w");
	fprintf(gpipe, "%s", string);
	fflush(gpipe);
}

int plot_hist(char *address, int N_samples, int dims[2], double alpha){
	/*
	 * Constructs and send to gnuplot command string to plot historical values of sample plots 
	 * from text file at address.
	 */
	 
	char input[512] = "\0";
	double norm_sample_coords[N_samples][2];
	
	get_norm_sample_coords(dims, N_samples, norm_sample_coords); // Coordinates for line labels
		
	add_string_plot_hist(input, address, alpha);
	
	for(int i = 0; i < N_samples; ++i){
		add_string_each_series(input, i, N_samples, norm_sample_coords[i]);
	}	
	gnuplot_pipe(input);

}