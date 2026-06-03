import numpy as np

class ABC:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.limit = int(pop * dim * 0.5)
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        food = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(f) for f in food])
        trial = np.zeros(self.pop)
        idx = np.argmin(fit)
        self.best_pos = food[idx].copy()
        self.best_val = fit[idx]

        for _ in range(self.max_iter):
            for i in range(self.pop):
                k = np.random.randint(self.pop)
                while k == i: k = np.random.randint(self.pop)
                j = np.random.randint(self.dim)
                phi = np.random.uniform(-1, 1)
                new = food[i].copy()
                new[j] += phi * (food[i][j] - food[k][j])
                new = np.clip(new, self.lb, self.ub)
                new_fit = self.func(new)
                if new_fit < fit[i]:
                    food[i] = new; fit[i] = new_fit; trial[i] = 0
                else:
                    trial[i] += 1

            prob = 0.9 * (fit.max() - fit) / (fit.max() - fit.min() + 1e-12) + 0.1
            for i in range(self.pop):
                if np.random.rand() < prob[i]:
                    k = np.random.randint(self.pop)
                    while k == i: k = np.random.randint(self.pop)
                    j = np.random.randint(self.dim)
                    phi = np.random.uniform(-1, 1)
                    new = food[i].copy()
                    new[j] += phi * (food[i][j] - food[k][j])
                    new = np.clip(new, self.lb, self.ub)
                    new_fit = self.func(new)
                    if new_fit < fit[i]:
                        food[i] = new; fit[i] = new_fit; trial[i] = 0
                    else:
                        trial[i] += 1

            for i in range(self.pop):
                if trial[i] >= self.limit:
                    food[i] = np.random.uniform(self.lb, self.ub, self.dim)
                    fit[i] = self.func(food[i])
                    trial[i] = 0

            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = food[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
