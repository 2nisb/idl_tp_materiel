# Résultats: produit de matrices sur ma machine

Machine: … Crête (TP 1): … Gflop/s double précision sur … cœurs.

| # | Version | n | Temps (s) | Gflop/s | Acc. absolue | Acc. relative | % crête |
|---|---|---|---|---|---|---|---|
| 1 | Python ijk | 256 | | | 1 | — | |
| 2 | C ijk -O0 | 1024 | | | | | |
| 3 | C ijk -O2 | 1024 | | | | | |
| 4 | C ikj -O2 | 1024 | | | | | |
| 5 | C block -O2 | 1024 | | | | | |
| 6 | C block -O3 (vectorisé) | 1024 | | | | | |
| 7 | C block -O3 -march=native | 1024 | | | | | |
| 8 | C omp, tous les cœurs | 1024 | | | | | |
| 9 | numpy / BLAS | 1024 | | | | | |

Pour comparer à Python, ramener au même n: le temps croît comme n³.

Réponses aux questions 1 à 8:

