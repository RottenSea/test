import numpy as np

class WOA:
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

    def run(self):
        whales = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(w) for w in whales])
        idx = np.argmin(fit)
        self.best_pos = whales[idx].copy()
        self.best_val = fit[idx]

        for t in range(self.max_iter):
            a = 2 - 2 * t / self.max_iter
            a2 = -1 + 2 * (1 - t / self.max_iter)
            for i in range(self.pop):
                r1, r2 = np.random.rand(), np.random.rand()
                A = 2 * a * r1 - a
                C = 2 * r2
                b = 1
                l = np.random.uniform(-1, 1)
                p = np.random.rand()

                if p < 0.5:
                    if abs(A) < 1:
                        D = abs(C * self.best_pos - whales[i])
                        whales[i] = self.best_pos - A * D
                    else:
                        rand_idx = np.random.randint(self.pop)
                        rand_whale = whales[rand_idx]
                        D = abs(C * rand_whale - whales[i])
                        whales[i] = rand_whale - A * D
                else:
                    D = abs(self.best_pos - whales[i])
                    whales[i] = D * np.exp(b * l) * np.cos(2 * np.pi * l) + self.best_pos
                whales[i] = np.clip(whales[i], self.lb, self.ub)
                fit[i] = self.func(whales[i])

            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = whales[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
