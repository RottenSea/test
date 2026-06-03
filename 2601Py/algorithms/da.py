import numpy as np
from math import gamma as _gamma

class DA:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def _levy(self):
        beta = 1.5
        sigma = (_gamma(1 + beta) * np.sin(np.pi * beta / 2)
                 / (_gamma((1 + beta) / 2) * beta * 2 ** ((beta - 1) / 2))) ** (1 / beta)
        u = np.random.randn(self.dim) * sigma
        v = np.random.randn(self.dim)
        step = u / (np.abs(v) ** (1 / beta))
        return step

    def run(self):
        pos = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        vel = np.zeros((self.pop, self.dim))
        fit = np.array([self.func(p) for p in pos])
        idx = np.argmin(fit)
        self.best_pos = pos[idx].copy()
        self.best_val = fit[idx]
        food = pos[idx].copy()
        enemy = pos[np.argmax(fit)].copy()

        for t in range(self.max_iter):
            w = 0.9 - 0.5 * t / self.max_iter
            s_scale = 0.1 * (1 - t / self.max_iter)
            a_scale = 0.1 * (1 - t / self.max_iter)
            c_scale = 0.7 * (1 - t / self.max_iter)
            f_scale = 2 * np.random.rand()
            e_scale = 0.1 * (1 - t / self.max_iter)
            r_neighbor = (self.ub - self.lb) * 0.5 * (1 - t / self.max_iter)

            for i in range(self.pop):
                diff = pos[i] - pos
                dist = np.linalg.norm(diff, axis=1)
                neighbors = [j for j in range(self.pop) if j != i and dist[j] < r_neighbor]

                if not neighbors:
                    pos[i] += self._levy()
                else:
                    S = np.sum(pos[i] - pos[neighbors], axis=0)
                    A = np.sum(vel[neighbors], axis=0)
                    C = np.mean(pos[neighbors], axis=0) - pos[i]
                    F = food - pos[i]
                    E = enemy + pos[i]
                    vel[i] = (s_scale * S + a_scale * A + c_scale * C
                              + f_scale * F + e_scale * E)
                    vel[i] = np.clip(vel[i], -1, 1)
                    pos[i] += w * pos[i] + vel[i]
                pos[i] = np.clip(pos[i], self.lb, self.ub)
                fit[i] = self.func(pos[i])

            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = pos[idx].copy()
                food = pos[idx].copy()
            enemy = pos[np.argmax(fit)].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
