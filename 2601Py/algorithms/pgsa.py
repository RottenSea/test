import numpy as np

class PGSA:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.branch_len = (ub - lb) * 0.1
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        nodes = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        vals = np.array([self.func(n) for n in nodes])
        idx = np.argmin(vals)
        self.best_pos = nodes[idx].copy()
        self.best_val = vals[idx]

        for _ in range(self.max_iter):
            f_min, f_max = vals.min(), vals.max()
            if f_max == f_min:
                conc = np.ones(self.pop) / self.pop
            else:
                conc = (f_max - vals) / (f_max - f_min + 1e-12)
            conc /= (conc.sum() + 1e-12)

            new_nodes = []
            for i in range(self.pop):
                num_growth = max(1, int(conc[i] * self.pop * 2))
                for _ in range(num_growth):
                    step = self.branch_len * np.random.uniform(-1, 1, self.dim)
                    new = nodes[i] + step
                    new = np.clip(new, self.lb, self.ub)
                    new_nodes.append(new)
            new_nodes = np.array(new_nodes)
            new_vals = np.array([self.func(n) for n in new_nodes])

            all_nodes = np.vstack([nodes, new_nodes])
            all_vals = np.concatenate([vals, new_vals])
            order = np.argsort(all_vals)
            nodes = all_nodes[order[:self.pop]]
            vals = all_vals[order[:self.pop]]

            if vals[0] < self.best_val:
                self.best_val = vals[0]; self.best_pos = nodes[0].copy()
            self.history.append(self.best_val)
            self.branch_len *= 0.98
        return self.best_pos, self.best_val
