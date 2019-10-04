int solve_laplace(int dims[2], double alpha, int N_iter, int N_samples, double psi[ dims[0] ][ dims[1] ], 
				  double hist_values[N_samples][N_iter]);
				  
int iterate_sequential_relax_record(int dims[2], double alpha, int N_iter, int N_samples, int sequence_length, 
									double psi[ dims[0] ][ dims[1] ], double hist_values[N_samples][N_iter],
									int coords_sequence[sequence_length][2], int sample_coords[N_samples][2]);
									
int check_point_converging(int N_samples, int N_iter, double hist_values[N_samples][N_iter], int sample_no, 
						   int cnvg_count[N_samples], int iter_no);
						   
int check_points_converged(int N_samples, int cnvg_count[N_samples]);

int find_greatest_boundaries(int dims[2], double psi[ dims[0] ][ dims[1] ], int highbounds[2]);

int gen_coords_sequence(int dims[2], int sequence_length, int coords_sequence[sequence_length][2], 
                      int highbounds[2]);
					  
int get_sample_coords(int dims[2], int N_samples, int sample_coords[N_samples][2]);

int over_relax(int dims[2], double alpha, double psi[ dims[0] ][ dims[1] ], int coords[2]);

int psi_gen(int dims[2], double psi[ dims[0] ][ dims[1] ]);

int set_zeros(int dims[2], double psi[ dims[0] ][ dims[1] ]);

int set_bound_funcs(int dims[2], double psi[ dims[0] ][ dims[1] ]);

int fprint_psi_nonuniform(FILE *stream, int dims[2], double psi[ dims[0] ][ dims[1] ]);

int normalise_axes(int dims[2], double x_axis[ dims[0] ], double y_axis[ dims[1] ]);

int fprint_hist_values(FILE *hist, int N_samples, int N_iter, int N_iter_cnvg, double hist_values[N_samples][N_iter]);

int contour_plot(char *address, char *title);

int plot_hist(char *address, int N_samples, int dims[2], double alpha);

int add_string_plot_hist(char *main_string, char *address, double alpha);

int add_string_each_series(char *main_string, int i, int N_samples, double sample_coords[2]);

int append_strings(int N, char *strings[N], char *main_string);

int gnuplot_pipe(char *string);

int get_analytic_values(int dims[2], double analytic_psi[ dims[0] ][ dims[1] ]);

int get_analytic_deviation(int dims[2], double psi[ dims[0] ][ dims[1] ], double analytic_psi[ dims[0] ][ dims[1] ], double psi_dev[ dims[0] ][ dims[1] ]);

int get_norm_sample_coords(int dims[2], int N_samples, double norm_sample_coords[N_samples][2]);