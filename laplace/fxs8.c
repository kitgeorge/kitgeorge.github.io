#include <stdio.h>
#include <math.h>
#include <string.h>
#include "myfuncs.h"

int get_norm_sample_coords(int dims[2], int N_samples, double norm_sample_coords[N_samples][2]){
	/*
	 * Caculates x-y coordinates of sample points
	 */
	
	int sample_coords[N_samples][2];
	get_sample_coords(dims, N_samples, sample_coords);
	for(int i = 0; i < N_samples; ++i){
		for(int j = 0; j < 2; ++j){
			norm_sample_coords[i][j] = (double)sample_coords[i][j] / (dims[j] - 1);
		}
	}
}

int add_string_plot_hist(char *main_string, char *address, double alpha){
	/*
	 * Generates initial string for plot_hist.
	 */
	char string_a[20];
	sprintf(string_a, "%.2f", alpha);
	char *strings[] = {"set title \"Alpha = ",
					   string_a,
					   "\"\nplot '",
					   address,
					   "' "};
	
	append_strings(5, strings, main_string);
}

int add_string_each_series(char *main_string, int i, int N_samples, double sample_coords[2]){
	/*
	 * Generates section of string for given sample point for plot_hist.
	 */
	char string_b[20];	
	char string_c[10];	
	
	char string_a[] = {(char)('0' + i), '\0'};
	sprintf(string_b, "\"(%.2f, %.2f)\"", sample_coords[0], sample_coords[1]);
	if(i < N_samples - 1){
		strcpy(string_c, ", '' ");
	}
	else {
		strcpy(string_c, "\n");
	}
	
	char *strings[] = {"index ",
					   string_a, 
					   " with lines title ",
					   string_b, string_c};
	
	append_strings(5, strings, main_string);
}