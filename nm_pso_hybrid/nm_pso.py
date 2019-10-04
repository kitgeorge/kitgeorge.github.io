import numpy as np
import random as rd
from math import *

class Params:

    # We call an instance of this class whenever we want a parameter, not sure
    # if this is inefficient but it is somewhat concise
    def set_params(self, lb, ub, func, omega, phip, phig, eta, kappa,
                   minfunc, minstep, n_particles, max_iter):
        Params.lb = np.array(lb)
        Params.ub = np.array(ub)
        Params.dim = len(lb)
        Params.vhigh = np.abs(self.ub - self.lb)
        Params.vlow = -Params().vhigh
        Params.func = [func] # Storing in array as lazy fix for error when storing function as class variable
        Params.omega = omega
        Params.phip = phip
        Params.phig = phig
        Params.eta = eta
        Params.kappa = kappa
        Params.minfunc = minfunc
        Params.minstep = minstep
        Params.n_particles = n_particles
        Params.max_iter = max_iter


class Particle:
    # x refers to current position, p refers to particle's best position so
    # far, g refers to swarm's best position so far



    def __init__(self, coords):
        self.coords = coords
        self.fp = np.inf
        self.pso_init_flag = 1 # Flags that if in the swarm, this particle's
                               # velocity should be initialised randomly

    def evaluate_function(self):
        self.fx = Params().func[0](self.coords)
        if(self.fx < self.fp):
            self.fp = self.fx
            self.best_coords = self.coords

    def pso_iterate(self, global_best_coords):
        if(self.pso_init_flag):
            self.init_random_velocity()
        self.adjust_velocity(global_best_coords)
        self.update_coords()

    def init_random_velocity(self):
        self.v = Params().vlow + np.random.rand(Params().dim)\
                 * (Params().vhigh-Params().vlow)

    def adjust_velocity(self, global_best_coords):
        rp = np.random.uniform(Params().dim)
        rg = np.random.uniform(Params().dim)
        self.v = Params().omega * self.v + Params().phip * rp\
                 * (self.best_coords-self.coords)\
                 + Params().phig * rp * (global_best_coords-self.coords)

    def update_coords(self):
        self.coords = self.coords + self.v
        self.constrain_bounds()

    def constrain_bounds(self):
        maskl = self.coords < Params().lb
        masku = self.coords > Params().ub
        self.coords = self.coords*(~np.logical_or(maskl, masku))\
                    + Params().lb*maskl + Params().ub*masku


class ParticleList(list):
    # Subclass to add Particle-specific methods to lists

    def __init__(self, particles, coords=[]):
        if(np.any(coords)):
            particles = []
            # Each row particle_coords corresponds to a particle
            for particle_coords in coords:
                particles.append(Particle(particle_coords))
        super().__init__(particles)

    def combine_array(self):
        # A matrix of coordinates is useful for position averages etc.
        array = np.zeros((len(self), len(self[0].coords)))
        for i in range(len(self)):
            array[i] = self[i].coords
        return array

    def evaluate_all(self):
        for particle in self:
            particle.evaluate_function()

    def particle_sort(self):
        self.sort(key=lambda particle: particle.fx)

    def pso_iterate_swarm(self, global_best_coords):
        for particle in self:
            particle.pso_iterate(global_best_coords)

    def flip(self):
        self.evaluate_all()
        self.particle_sort()
        W = self[Params().dim].coords
        coords = self.combine_array()[:Params().dim]
        C = np.mean(coords, axis=0)
        R = C + (C-W)
        if(Params().func[0](R) < self[0].fx):
            R = C + Params().eta*(C-W)
        elif(Params().func[0](R) > self[Params().dim-1].fx):
            if(Params().func[0](R) > self[Params().dim].fx):
                R = C - Params().kappa*(C-W)
            else:
                R = C + Params().kappa*(C-W)
        self[Params().dim].coords = R
        self[Params().dim].constrain_bounds()

    def max_pair_separation(self):
        max_separation = 0
        for particle_a in self:
            for particle_b in [particle for particle in self\
                               if particle != particle_a]:
                separation = np.sqrt(np.sum((particle_a.coords
                                             - particle_b.coords) ** 2))
                if(separation > max_separation):
                    max_separation = separation
        return max_separation


class GlobalSwarm(ParticleList):


    def __init__(self, n_particles):
        self.randomly_position_particles(n_particles)
        super().evaluate_all()
        super().particle_sort()
        self.fg = np.inf
        self.fg_old = None
        self.elite_simplex = ParticleList([])
        self.main_swarm = ParticleList([])

    def randomly_position_particles(self, n_particles):
        particle_coords = Params().lb + np.random.rand(n_particles,
                          Params().dim) * (Params().ub-Params().lb)
        super().__init__(None, coords=particle_coords)

    def sort_hierarchy(self):
        for particle in self.elite_simplex:
            particle.pso_init_flag = 1
        for particle in self.main_swarm:
            particle.pso_init_flag = 0
            # We want a flag to identify particles which join the
            # main swarm from the simplex, so need a randomised velocity
        self.elite_simplex = ParticleList(self[:Params().dim+1]) # First N+1 particles
        self.main_swarm = ParticleList(self[Params().dim+1:])
        # (2N) remaining particles

    def loop_iterations(self):
        for i in range(Params().max_iter):
            if(self.total_iteration()):
                return i + 1
        return 0


    def total_iteration(self):
        self.sort_hierarchy()
        self.elite_simplex.flip()
        self.find_global_best()
        self.main_swarm.pso_iterate_swarm(self.global_best_coords)
        return self.check_convergence()

    def find_global_best(self):
        super().evaluate_all()
        super().particle_sort()
        if(self[0].fx < self.fg):
            self.global_best_coords = self[0].coords
            self.fg = self[0].fx

    def check_convergence(self):
        self.find_global_best()
        if(self.fg_old is None): # Maybe this shouldn't be in method, only relevant on first iteration
            self.fg_old = self.fg
            self.global_best_coords_old = self.global_best_coords
            return 0
        stepsize = np.sqrt(np.sum((self.global_best_coords_old\
                   - self.global_best_coords) ** 2))
        print(super().combine_array())
        print(stepsize)
        if(self.elite_simplex.max_pair_separation() <= Params().minstep):
            if(self.fg_old-self.fg <= Params().minfunc):
                print('Stopping search: Global best objective change less than {:}'\
                      .format(Params().minfunc))
                return 1
            if(stepsize <= Params().minstep):
                print('Stopping search: Global best position change less than {:}'\
                      .format(Params().minstep))
                return 1
        self.global_best_coords_old = self.global_best_coords
        self.fg_old = self.fg
        return 0

def nm_pso_hybrid(func, lb, ub, omega=0.5, phip=0.5, phig=0.5, eta=5,
                  kappa=0.5, minfunc=1e-8, minstep=1e-8, n_particles=7,
                  max_iter=100):
    parameters = Params()
    parameters.set_params(lb, ub, func, omega, phip, phig, eta, kappa,
                          minfunc, minstep, n_particles, max_iter)
    hybrid_swarm = GlobalSwarm(Params().n_particles)
    iterations = hybrid_swarm.loop_iterations()
    if(iterations):
        print('Convergence after {} iterations'.format(iterations))
    else:
        print('Max iterations ({}) reached before convergence'
              .format(Params().max_iter))
    print('Minimum approximated at {}, with cost function value {}'
          .format(hybrid_swarm.global_best_coords, hybrid_swarm.fg))
    return hybrid_swarm.global_best_coords, hybrid_swarm.fg
