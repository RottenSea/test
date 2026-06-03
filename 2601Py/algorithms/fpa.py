import numpy as np
from math import gamma as _gamma

class FPA:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.p = 0.8
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    @staticmethod
    def _levy(beta=1.5):
        sigma = (_gamma(1 + beta) * np.sin(np.pi * beta / 2)
                 / (_gamma((1 + beta) / 2) * beta * 2 ** ((beta - 1) / 2))) ** (1 / beta)
        u = np.random.randn() * sigma
        v = np.random.randn()
        return u / (abs(v) ** (1 / beta))

    def run(self):
        pop = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(p) for p in pop])
        idx = np.argmin(fit)
        self.best_pos = pop[idx].copy()
        self.best_val = fit[idx]

        for _ in range(self.max_iter):
            for i in range(self.pop):
                if np.random.rand() < self.p:
                    step = 0.01 * np.array([self._levy() for _ in range(self.dim)])
                    pop[i] += step * (pop[i] - self.best_pos)
                else:
                    j, k = np.random.choice(self.pop, 2, replace=False)
                    eps = np.random.rand()
                    pop[i] += eps * (pop[j] - pop[k])
                pop[i] = np.clip(pop[i], self.lb, self.ub)
                fit[i] = self.func(pop[i])
            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = pop[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
