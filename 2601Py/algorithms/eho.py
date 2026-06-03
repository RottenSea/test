import numpy as np

class EHO:
    def __init__(self, func, dim=10, pop=40, max_iter=500, lb=-5.12, ub=5.12):
        self.func = func
        self.dim = dim
        self.pop = pop
        self.max_iter = max_iter
        self.lb = lb
        self.ub = ub
        self.n_clan = 5
        self.clan_size = pop // self.n_clan
        self.alpha = 0.6
        self.beta = 0.3
        self.best_pos = None
        self.best_val = float('inf')
        self.history = []

    def run(self):
        elephants = np.random.uniform(self.lb, self.ub, (self.pop, self.dim))
        fit = np.array([self.func(e) for e in elephants])
        idx = np.argmin(fit)
        self.best_pos = elephants[idx].copy()
        self.best_val = fit[idx]

        for _ in range(self.max_iter):
            clans = [elephants[i:i+self.clan_size] for i in range(0, self.pop, self.clan_size)]
            if len(clans) > self.n_clan: clans = clans[:self.n_clan]

            new_elephants = []
            for clan in clans:
                clan_fit = np.array([self.func(e) for e in clan])
                center = clan.mean(axis=0)
                leader_idx = np.argmin(clan_fit)
                for i, e in enumerate(clan):
                    if i == leader_idx:
                        new_e = self.beta * center
                    else:
                        new_e = e + self.alpha * (clan[leader_idx] - e) * np.random.rand(self.dim)
                    new_e = np.clip(new_e, self.lb, self.ub)
                    new_elephants.append(new_e)

            elephants = np.array(new_elephants[:self.pop])
            for i, e in enumerate(elephants):
                fit[i] = self.func(e)

            worst_idx = np.argmax(fit)
            elephants[worst_idx] = np.random.uniform(self.lb, self.ub, self.dim)
            fit[worst_idx] = self.func(elephants[worst_idx])

            idx = np.argmin(fit)
            if fit[idx] < self.best_val:
                self.best_val = fit[idx]; self.best_pos = elephants[idx].copy()
            self.history.append(self.best_val)
        return self.best_pos, self.best_val
