import numpy as np

class GWO:
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
        wolves = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(w) for w in wolves])
        order = np.argsort(fit)
        alpha, beta, delta = wolves[order[0]], wolves[order[1]], wolves[order[2]]
        self.best_pos = alpha.copy()
        self.best_val = fit[order[0]]

        for t in range(self.max_iter):
            a = 2 - 2 * t / self.max_iter
            for i in range(self.pop):
                for leader, label in [(alpha, 'A'), (beta, 'B'), (delta, 'D')]:
                    r1, r2 = np.random.rand(self.dim), np.random.rand(self.dim)
                    A, C = 2 * a * r1 - a, 2 * r2
                    D = abs(C * leader - wolves[i])
                    if label == 'A':
                        X1 = leader - A * D
                    elif label == 'B':
                        X2 = leader - A * D
                    else:
                        X3 = leader - A * D
                wolves[i] = (X1 + X2 + X3) / 3
                wolves[i] = np.clip(wolves[i], self.lb, self.ub)
                fit[i] = self.func(wolves[i])

            order = np.argsort(fit)
            alpha, beta, delta = wolves[order[0]], wolves[order[1]], wolves[order[2]]
            if fit[order[0]] < self.best_val:
                self.best_val = fit[order[0]]; self.best_pos = alpha.copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
