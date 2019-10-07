A hybrid algorithm for minimisation of non-convex functions

This function combines the particle swarm optimization (PSO) algorithm with the Nelder-Mead simplex algorithm in an attempt to converge on a minimum more quickly than either of those methods used individually. The PSO algorithm is used, but at the beginning of each iteration the N+1 lowest-valued particles according to the function of their positions (in an N dimensional problem) are "flipped" through an iteration of the NM algorithm.

I wrote this function for the LMU theoretical nanophysics group as part of my summer research internship under them.

This was written with reference to the pyswarm code (available at https://github.com/tisimst/pyswarm), though my code is thoroughly different as combining the two methods meant an object oriented design was easier in my case.

Parameters:
func: function to be optimised
lb, ub: lower and upper bounds between which to search for minimum
omega: Factor by which velocity of each particle in the swarm decays between each iteration (drag)
phip: Parameter affecting force on particles from their own individual historic best positions
phig: Parameter affecting force on particles from best historic position of any particle
eta: Factor by which simplex expands when flipped, if the predicted new position has a lower value than all initial vertices
kappa: Factor by which simplex multiplies (to shrink) if the predicted new position has a higher value than the previous vertices
minfunc: If the function's value at the minimum changes by less than this amount between iterations, convergence may have been reached.
minstep: If all the top N+1 particles (simplex) are within this distance of each other, and the minimum position has moved less than this distance in the last iteration, convergence may have been reached.
n_particles: Number of particles used
max_iter: Number of iterations taken if convergence not reached.
