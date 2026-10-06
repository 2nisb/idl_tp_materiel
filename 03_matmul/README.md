# TP 3: produit de matrices, de Python à BLAS

Objectif: refaire sur votre machine le tableau de Leiserson et al. (2020)
vu en introduction: le même produit de matrices, du Python naïf au code
optimisé, en mesurant à chaque étape le temps, les Gflop/s et le
pourcentage de la crête calculée au TP 1. Durée: 3 h. Rendu: `resultats.md`
avec le tableau complété et les réponses.

Le produit de deux matrices n x n demande 2n³ flop. On prend n = 1024
en C (2,1 Gflop) et n = 256 en Python (34 Mflop, déjà long).

## 1. Python naïf

```bash
python3 matmul.py 256
```

Notez le temps et les Gflop/s. Estimez le temps qu'il faudrait pour
n = 1024 (le temps croît comme n³) et pour n = 4096 comme dans l'article.

## 2. C naïf, trois ordres de boucles

`matmul.c` contient plusieurs variantes choisies par le premier argument:

- `ijk`: les trois boucles dans l'ordre naturel, celui du Python;
- `ikj`: boucle `j` à l'intérieur: on parcourt `B` et `C` par lignes;
- `jki`: boucle `i` à l'intérieur: on parcourt `A` et `C` par colonnes;
- `block`: version `ikj` par blocs de 64 x 64 (*tiling*);
- `omp`: version `ikj` parallélisée avec OpenMP sur tous les cœurs.

```bash
make                      # matmul_O0, matmul_O2, matmul_O3 (et matmul_omp)
./matmul_O0 ijk 1024
./matmul_O2 ijk 1024
./matmul_O2 ikj 1024
./matmul_O2 jki 1024
```

Chaque exécution affiche le temps, les Gflop/s et une somme de contrôle
qui doit être la même pour toutes les variantes.

1. Pourquoi `ikj` est-il plus rapide que `ijk`, et `jki` plus lent? Faites
   un dessin des accès mémoire de la boucle interne pour les trois ordres,
   en vous souvenant qu'en C une matrice est rangée ligne par ligne et
   qu'une ligne de cache contient 8 `double`.
2. Combien d'octets la boucle interne de `ijk` lit-elle par flop? Et
   `ikj`? Comparez à l'intensité arithmétique d'équilibre du TP 1.

## 3. Blocage, optimisation, vectorisation

```bash
./matmul_O2 block 1024
./matmul_O3 ikj 1024
./matmul_O3 block 1024
```

3. Pourquoi le blocage aide-t-il? Quelle taille de bloc fait tenir les trois
   sous-matrices dans votre L1? Dans votre L2? Essayez `BLOCK=32`, `128`
   (`make clean; make BLOCK=128`).
4. `-O3` autorise le compilateur à **vectoriser**: regardez l'assembleur de
   la boucle interne (`make asm`, ou sur <https://godbolt.org>) et cherchez
   les instructions SIMD (`vfmadd` et registres `ymm` sur x86-64, `fmla` et
   registres `v` sur AArch64). Combien de `double` par instruction?
5. Sur x86-64, ajoutez `-march=native` (`make CFLAGS_O3="-O3
   -march=native"`): le compilateur peut alors utiliser AVX2 ou AVX-512.
   Sur Apple Silicon, l'option s'appelle `-mcpu=native`. Quel gain?

## 4. Plusieurs cœurs

```bash
./matmul_omp block 1024
OMP_NUM_THREADS=1 ./matmul_omp block 1024
OMP_NUM_THREADS=2 ./matmul_omp block 1024
```

Sous macOS, OpenMP demande `brew install libomp` puis `make omp`; sinon
sautez cette étape ou utilisez Docker.

6. Tracez l'accélération en fonction du nombre de threads. Est-elle
   linéaire? Que se passe-t-il au-delà du nombre de cœurs physiques, et sur
   les cœurs efficacité d'un Apple M?

## 5. Ce que fait un professionnel: BLAS

```bash
python3 matmul_numpy.py 1024
python3 matmul_numpy.py 4096
```

`numpy` appelle une bibliothèque BLAS (OpenBLAS, MKL, Accelerate sous
macOS) écrite par des spécialistes de votre processeur.

7. Quel pourcentage de la crête BLAS atteint-il? Et votre meilleure
   version C? D'où vient l'écart restant (regardez ce que fait un noyau
   `dgemm`: blocage à plusieurs niveaux, assembleur, *packing*)?

## 6. Le tableau

Remplissez `resultats.md` sur le modèle de l'article: version, temps,
Gflop/s, accélération absolue par rapport à Python, accélération relative à
la ligne précédente, pourcentage de la crête.

8. Combien de fois plus vite que le Python naïf va votre meilleure
   version? L'article trouve 62 806 pour n = 4096: pourquoi vos chiffres
   diffèrent-ils (taille, machine, nombre de cœurs, AVX-512)?
