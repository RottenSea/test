import numpy as np

class BA:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.f_min = 0
        self.f_max = 2
        self.A = 0.5
        self.r = 0.5
        self.alpha = 0.95
        self.gamma = 0.95
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        pos = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        vel = np.zeros((self.pop, self.dim))
        fit = np.array([self.func(p) for p in pos])
        idx = np.argmin(fit)
        self.best_pos = pos[idx].copy()
        self.best_val = fit[idx]

        for _ in range(self.max_iter):
            freq = self.f_min + (self.f_max - self.f_min) * np.random.rand(self.pop, self.dim)
            vel += (pos - self.best_pos) * freq
            pos += vel
            pos = np.clip(pos, self.lb, self.ub)

            for i in range(self.pop):
                if np.random.rand() > self.r:
                    pos[i] = self.best_pos + 0.001 * np.random.randn(self.dim)
                    pos[i] = np.clip(pos[i], self.lb, self.ub)
                new_fit = self.func(pos[i])
                if new_fit <= fit[i] and np.random.rand() < self.A:
                    fit[i] = new_fit
                    if new_fit < self.best_val:
                        self.best_val = new_fit; self.best_pos = pos[i].copy()

            self.A *= self.alpha
            self.r *= (1 - np.exp(-self.gamma * _))
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
