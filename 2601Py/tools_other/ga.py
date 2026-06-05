import numpy as np
from test_functions import sphere, rastrigin, griewank

class GA:
    def __init__(self, func, dim=2, pop=50, max_iter=200,
                 pc=0.8, pm=0.1, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.pc = pc
        self.pm = pm
        self.lb = lb
        self.ub = ub
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        pop = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(ind) for ind in pop])
        best_idx = np.argmin(fit)

        for _ in range(self.max_iter):
            new_pop = []
            for _ in range(self.pop // 2):
                p1, p2 = self._select(pop, fit), self._select(pop, fit)
                c1, c2 = self._crossover(p1, p2)
                c1, c2 = self._mutate(c1), self._mutate(c2)
                new_pop.extend([c1, c2])
            pop = np.array(new_pop)
            fit = np.array([self.func(ind) for ind in pop])
            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]
                self.best_pos = pop[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val

    def _select(self, pop, fit):
        i, j = np.random.randint(0, self.pop, 2)
        return pop[i] if fit[i] < fit[j] else pop[j]

    def _crossover(self, p1, p2):
        if np.random.rand() < self.pc:
            point = np.random.randint(1, self.dim)
            return (np.concatenate([p1[:point], p2[point:]]),
                    np.concatenate([p2[:point], p1[point:]]))
        return p1.copy(), p2.copy()

    def _mutate(self, c):
        if np.random.rand() < self.pm:
            idx = np.random.randint(self.dim)
            c = c.copy()
            c[idx] = np.random.uniform(self.lb, self.ub)
        return c

if __name__ == '__main__':
    for name, func in [('Sphere', sphere), ('Rastrigin', rastrigin), ('Griewank', griewank)]:
        ga = GA(func, dim=10, pop=80, max_iter=300)
        pos, val = ga.run()
        print(f'[{name}] 最优值: {val:.6f}  最优位置: {np.round(pos, 4)}')
