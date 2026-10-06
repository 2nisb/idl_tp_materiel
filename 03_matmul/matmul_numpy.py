"""Produit de matrices avec numpy, donc avec la bibliothèque BLAS de la machine.

Usage: python3 matmul_numpy.py [n]
"""
import sys
import time
import numpy as np

n = int(sys.argv[1]) if len(sys.argv) > 1 else 1024
rng = np.random.default_rng(1)
A = rng.random((n, n))
B = rng.random((n, n))
A @ B                                   # échauffement
t0 = time.perf_counter()
C = A @ B
dt = time.perf_counter() - t0
print(f"numpy n={n}: {dt:.3f} s, {2.0 * n ** 3 / dt / 1e9:.1f} Gflop/s, "
      f"controle={C.sum():.6e}")
try:
    np.show_config()
except Exception:
    pass
