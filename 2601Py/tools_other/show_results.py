import csv

with open('benchmark_results.csv', 'r', encoding='utf-8-sig') as f:
    reader = list(csv.DictReader(f))
    print(f'{"算法":>6s}  {"Sphere_best":>16s}  {"Sphere_mean":>16s}  {"Sphere_std":>14s}  {"Sphere_time":>10s}  {"Rastrigin_best":>16s}  {"Rastrigin_mean":>16s}  {"Griewank_best":>16s}  {"Griewank_mean":>16s}')
    print('=' * 160)
    for r in reader:
        if r['Algorithm'] == '说明': continue
        print(f'{r["Algorithm"]:>6s}  {r["Sphere_best"]:>16s}  {r["Sphere_mean"]:>16s}  {r["Sphere_std"]:>14s}  {r["Sphere_time"]:>10s}  {r["Rastrigin_best"]:>16s}  {r["Rastrigin_mean"]:>16s}  {r["Griewank_best"]:>16s}  {r["Griewank_mean"]:>16s}')
