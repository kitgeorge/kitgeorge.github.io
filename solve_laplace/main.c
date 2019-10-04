#include <stdio.h>
#include <math.h>
#include "myfuncs.h"
			
int main(){
		
	double alpha = 1.94;
	int N_iter = 10000;
	int N_samples = 5;
	int dims[2] = {101, 101};
	
	double psi[ dims[0] ][ dims[1] ];
	double analytic_psi[ dims[0] ][ dims[1] ];
	double psi_dev[ dims[0] ][ dims[1] ];
	double hist_values[N_samples][N_iter + 1];
	
	psi_gen(dims, psi); // Initial psi (with boundary conditions) now represented by matrix psi.
	int N_iter_cnvg = solve_laplace(dims, alpha, N_iter, N_samples, psi, hist_values);
	// Matrix psi now represents Laplace solution. Hist_values recorded for sample points.
	
	get_analytic_values(dims, analytic_psi);
	get_analytic_deviation(dims, psi, analytic_psi, psi_dev);
	
	FILE *f_psi;
	FILE *f_dev;
	FILE *f_hist;
	
	f_psi = fopen("psi.txt", "w"); 
	f_dev = fopen("psi_dev.txt", "w");
	f_hist = fopen("hist.txt", "w");
	
	fprint_psi_nonuniform(f_psi, dims, psi);
	fprint_psi_nonuniform(f_dev, dims, psi_dev);
	fprint_hist_values(f_hist, N_samples, N_iter, N_iter_cnvg, hist_values);
	
	contour_plot("psi.txt", "Psi");
	contour_plot("psi_dev.txt", "Difference from analytic solution");
	plot_hist("hist.txt", N_samples, dims, alpha);
}