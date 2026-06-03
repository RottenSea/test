import numpy as np
from math import gamma as _gamma

class CS:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.pa = 0.25
        self.beta = 1.5
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def _levy(self, d):
        sigma = (_gamma(1 + self.beta) * np.sin(np.pi * self.beta / 2)
                 / (_gamma((1 + self.beta) / 2) * self.beta * 2 ** ((self.beta - 1) / 2))) ** (1 / self.beta)
        u = np.random.randn(d) * sigma
        v = np.random.randn(d)
        return u / (np.abs(v) ** (1 / self.beta))

    def run(self):
        nest = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(n) for n in nest])
        idx = np.argmin(fit)
        self.best_pos = nest[idx].copy()
        self.best_val = fit[idx]

        for _ in range(self.max_iter):
            step = 0.1 * self._levy(self.dim)
            new = nest + step * (nest - self.best_pos)
            new = np.clip(new, self.lb, self.ub)
            new_fit = np.array([self.func(n) for n in new])
            mask = new_fit < fit
            nest[mask] = new[mask]; fit[mask] = new_fit[mask]

            perm = np.random.permutation(self.pop)
            for i in range(self.pop):
                if np.random.rand() < self.pa:
                    j = np.random.randint(self.pop)
                    while j == i: j = np.random.randint(self.pop)
                    nest[i] += np.random.rand(self.dim) * (nest[perm[i]] - nest[j])
            nest = np.clip(nest, self.lb, self.ub)
            fit = np.array([self.func(n) for n in nest])

            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = nest[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
