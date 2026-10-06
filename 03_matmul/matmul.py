"""Produit de matrices naïf en Python pur, comme dans Leiserson et al. (2020).

Usage: python3 matmul.py [n]   (n = 256 par défaut; n = 1024 prend des minutes)
"""
import sys
import time
import random

n = int(sys.argv[1]) if len(sys.argv) > 1 else 256
random.seed(1)
A = [[random.random() for _ in range(n)] for _ in range(n)]
B = [[random.random() for _ in range(n)] for _ in range(n)]
C = [[0.0] * n for _ in range(n)]

t0 = time.perf_counter()
for i in range(n):
    for j in range(n):
        for k in range(n):
            C[i][j] += A[i][k] * B[k][j]
dt = time.perf_counter() - t0

flop = 2.0 * n ** 3
print(f"python ijk n={n}: {dt:.2f} s, {flop / dt / 1e9:.4f} Gflop/s, "
      f"controle={sum(map(sum, C)):.6e}")
