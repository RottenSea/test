import numpy as np

class FA:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.beta0 = 1.0
        self.gamma = 0.5
        self.alpha = 0.5
        self.delta = 0.9
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        pos = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(p) for p in pos])
        idx = np.argmin(fit)
        self.best_pos = pos[idx].copy()
        self.best_val = fit[idx]

        for t in range(self.max_iter):
            for i in range(self.pop):
                for j in range(self.pop):
                    if fit[j] < fit[i]:
                        r2 = np.sum((pos[i] - pos[j]) ** 2)
                        beta = self.beta0 * np.exp(-self.gamma * r2)
                        pos[i] += beta * (pos[j] - pos[i]) + self.alpha * (np.random.rand(self.dim) - 0.5)
                        pos[i] = np.clip(pos[i], self.lb, self.ub)
                        fit[i] = self.func(pos[i])
            self.alpha *= self.delta
            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = pos[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
