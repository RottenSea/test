import numpy as np
import csv, time, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from test_functions import sphere, rastrigin, griewank
from algorithms import ALGORITHMS

FUNCTIONS = {'Sphere': sphere, 'Rastrigin': rastrigin, 'Griewank': griewank}
DIM = 10
MAX_ITER = 500
POP = 50
LB, UB = -5.12, 5.12
N_RUNS = 10

results = []

for algo_name, AlgoClass in ALGORITHMS.items():
    row = {'Algorithm': algo_name}
    for func_name, func in FUNCTIONS.items():
        vals = []
        times = []
        for run in range(N_RUNS):
            np.random.seed(run * 42)
            algo = AlgoClass(func, dim=DIM, pop=POP, max_iter=MAX_ITER, lb=LB, ub=UB)
            t0 = time.time()
            pos, val = algo.run()
            elapsed = time.time() - t0
            vals.append(val)
            times.append(elapsed)
        mean_val = np.mean(vals)
        std_val = np.std(vals)
        best_val = np.min(vals)
        precision = mean_val
        row[f'{func_name}_best'] = f'{best_val:.6e}'
        row[f'{func_name}_mean'] = f'{mean_val:.6e}'
        row[f'{func_name}_std'] = f'{std_val:.6e}'
        row[f'{func_name}_time'] = f'{np.mean(times):.3f}s'
    results.append(row)
    print(f'{algo_name:6s} 完成')

csv_path = os.path.join(os.path.dirname(__file__), 'benchmark_results.csv')
fieldnames = ['Algorithm']
for fn in FUNCTIONS:
    fieldnames += [f'{fn}_best', f'{fn}_mean', f'{fn}_std', f'{fn}_time']

with open(csv_path, 'w', newline='', encoding='utf-8-sig') as f:
    writer = csv.DictWriter(f, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(results)

print(f'\n结果已保存至: {csv_path}')
print(f'\n{"="*90}')
print(f'{"算法":>8s}  {"Sphere 最优":>14s}  {"Rastrigin 最优":>16s}  {"Griewank 最优":>16s}')
print(f'{"="*90}')
for r in results:
    print(f'{r["Algorithm"]:>8s}  {r["Sphere_best"]:>14s}  {r["Rastrigin_best"]:>16s}  {r["Griewank_best"]:>16s}')
print(f'{"="*90}')
