A hybrid algorithm for minimisation of non-convex functions

This program combines the particle swarm optimization (PSO) algorithm with the Nelder-Mead simplex algorithm in an attempt to converge on a minimum more quickly than either of those methods used individually. The PSO algorithm is used, but at the beginning of each iteration the N+1 lowest-valued particles according to the function of their positions (in an N dimensional problem) are "flipped" through an iteration of the NM algorithm.

I wrote this program for the LMU theoretical nanophysics group as part of my summer research internship under them.

This was written with reference to the pyswarm code (available at https://github.com/tisimst/pyswarm), though my code is thoroughly different as combining the two methods meant an object oriented design was easier in my case.

