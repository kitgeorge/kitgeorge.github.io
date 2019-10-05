Laplace equation solver for a square region with fixed boundary conditions

This program solves the Laplace equation by the over-relaxation method, for a square region between (0,0) and (1,1), which it splits into a grid of interval 0.01*0.01. The boundaries are fixed at zero along the axes, and sin(x)*sinh(1) and sinh(y)*sin(1) along the opposite edges. These boundaries can be quite simply modified by rewriting the set_bound_funcs function. However, the program also plots the difference between its solution and the analytic solution sin(x)sinh(y) to demonstrate its accuracy, but if the boundaries are changed the analytic solution must also be manually changed in the get_analytic_values function (for obvious reasons). The solution is then contour plotted, and a specified number (5) of points equally spaced vertically along x=0.5 are plotted in a graph of their historical values, to demonstrate rates of convergence across the region. The program runs until the specified maximum iterations are reached, or the square of the change in each tracked point's value between iterations is below a certain threshold for 100 consecutive iterations (our convergence condition).

In main.c, alpha can be set between 1 and 2 as the over-relaxation parameter (alpha >= 2 does not lead to convergence). N_iter sets the maximum number of iterations and N_samples sets the number of sample points to be tracked.

This program is tested on linux, and depends on gnuplot being installed. It can be compiled with make from within this directory, and run with ./laplace

This program was written for a second year physics computing practical at Oxford University. However, wanting to learn C rather than using MATLAB as recommended, I made this significantly more challenging.
