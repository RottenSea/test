import numpy as np
import csv, time, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from test_functions import sphere, rastrigin, griewank

DIM = 10
MAX_ITER = 500
POP = 50
LB, UB = -5.12, 5.12
N_RUNS = 10
FUNCTIONS = {'Sphere': sphere, 'Rastrigin': rastrigin, 'Griewank': griewank}
CSV_PATH = os.path.join(os.path.dirname(__file__), 'benchmark_results.csv')

def run_algorithm(algo_name, AlgoClass):
    row = {'Algorithm': algo_name}
    print(f'\n===== {algo_name} =====')
    for func_name, func in FUNCTIONS.items():
        vals = []; times = []
        for run in range(N_RUNS):
            np.random.seed(run * 42)
            algo = AlgoClass(func, dim=DIM, pop=POP, max_iter=MAX_ITER, lb=LB, ub=UB)
            t0 = time.time()
            _, val = algo.run()
            elapsed = time.time() - t0
            vals.append(val); times.append(elapsed)
            print(f'  {func_name} run {run+1:2d}: {val:.6e} ({elapsed:.1f}s)')
        row[f'{func_name}_best'] = f'{np.min(vals):.6e}'
        row[f'{func_name}_mean'] = f'{np.mean(vals):.6e}'
        row[f'{func_name}_std']  = f'{np.std(vals):.6e}'
        row[f'{func_name}_time'] = f'{np.mean(times):.1f}s'
    # 重写 CSV（保留已有结果）
    fieldnames = ['Algorithm']
    for fn in FUNCTIONS:
        fieldnames += [f'{fn}_best', f'{fn}_mean', f'{fn}_std', f'{fn}_time']
    existing = []
    if os.path.exists(CSV_PATH):
        with open(CSV_PATH, 'r', encoding='utf-8-sig') as f:
            reader = csv.DictReader(f)
            for r in reader:
                if r['Algorithm'] != algo_name:
                    existing.append(r)
    existing.append(row)
    with open(CSV_PATH, 'w', newline='', encoding='utf-8-sig') as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        w.writerows(existing)
    print(f'  -> 完成，已保存')

if __name__ == '__main__':
    import importlib
    for name in ['ABC', 'FA', 'PGSA', 'CS', 'BA', 'FPA', 'GWO', 'DA', 'EHO', 'WOA']:
        mod = importlib.import_module(f'algorithms.{name.lower()}')
        AlgoClass = getattr(mod, name)
        run_algorithm(name, AlgoClass)
    print(f'\n全部完成! 结果: {CSV_PATH}')
