import numpy as np
from test_functions import sphere, rastrigin, griewank

class PSO:
    def __init__(self, func, dim=2, pop=30, max_iter=200,
                 w=0.7, c1=1.5, c2=1.5, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.w = w
        self.c1 = c1
        self.c2 = c2
        self.lb = lb
        self.ub = ub
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        pos = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        vel = np.random.uniform(-1, 1, (self.pop, self.dim))
        pbest_pos = pos.copy()
        pbest_val = np.array([self.func(p) for p in pos])
        gbest_idx = np.argmin(pbest_val)
        gbest_pos = pbest_pos[gbest_idx].copy()
        gbest_val = pbest_val[gbest_idx]

        for _ in range(self.max_iter):
            for i in range(self.pop):
                r1, r2 = np.random.rand(self.dim), np.random.rand(self.dim)
                vel[i] = (self.w * vel[i]
                          + self.c1 * r1 * (pbest_pos[i] - pos[i])
                          + self.c2 * r2 * (gbest_pos - pos[i]))
                pos[i] += vel[i]
                pos[i] = np.clip(pos[i], self.lb, self.ub)
                val = self.func(pos[i])
                if val < pbest_val[i]:
                    pbest_val[i] = val
                    pbest_pos[i] = pos[i].copy()
                    if val < gbest_val:
                        gbest_val = val
                        gbest_pos = pos[i].copy()
            self.history.append(gbest_val)

        self.best_pos = gbest_pos
        self.best_val = gbest_val
        return gbest_pos, gbest_val

if __name__ == '__main__':
    for name, func in [('Sphere', sphere), ('Rastrigin', rastrigin), ('Griewank', griewank)]:
        pso = PSO(func, dim=10, pop=50, max_iter=300)
        pos, val = pso.run()
        print(f'[{name}] 最优值: {val:.6f}  最优位置: {np.round(pos, 4)}')
