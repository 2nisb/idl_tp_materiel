/* Produit de matrices C = A * B en double précision, plusieurs variantes.
 *
 * Usage: ./matmul <ijk|ikj|jki|block|omp> [n]
 * Compiler avec -DBLOCK=64 pour changer la taille de bloc, -fopenmp pour
 * la variante omp. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#ifndef BLOCK
#define BLOCK 64
#endif

static double now(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

/* Matrices n x n rangées ligne par ligne: M[i][j] est M[i * n + j]. */

static void mm_ijk(int n, const double *A, const double *B, double *C)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double s = 0;
            for (int k = 0; k < n; k++)
                s += A[i * n + k] * B[k * n + j];   /* B parcourue par colonne */
            C[i * n + j] = s;
        }
}

static void mm_ikj(int n, const double *A, const double *B, double *C)
{
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            double a = A[i * n + k];
            for (int j = 0; j < n; j++)
                C[i * n + j] += a * B[k * n + j];   /* B et C par ligne */
        }
}

static void mm_jki(int n, const double *A, const double *B, double *C)
{
    for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++) {
            double b = B[k * n + j];
            for (int i = 0; i < n; i++)
                C[i * n + j] += A[i * n + k] * b;   /* A et C par colonne */
        }
}

/* ikj par blocs: les trois sous-matrices BLOCK x BLOCK restent en cache. */
static void mm_block(int n, const double *A, const double *B, double *C)
{
    for (int ii = 0; ii < n; ii += BLOCK)
        for (int kk = 0; kk < n; kk += BLOCK)
            for (int jj = 0; jj < n; jj += BLOCK)
                for (int i = ii; i < ii + BLOCK && i < n; i++)
                    for (int k = kk; k < kk + BLOCK && k < n; k++) {
                        double a = A[i * n + k];
                        for (int j = jj; j < jj + BLOCK && j < n; j++)
                            C[i * n + j] += a * B[k * n + j];
                    }
}

/* Blocs distribués entre les threads: chaque thread a ses lignes de C. */
static void mm_omp(int n, const double *A, const double *B, double *C)
{
#ifdef _OPENMP
    #pragma omp parallel for schedule(static)
#endif
    for (int ii = 0; ii < n; ii += BLOCK)
        for (int kk = 0; kk < n; kk += BLOCK)
            for (int jj = 0; jj < n; jj += BLOCK)
                for (int i = ii; i < ii + BLOCK && i < n; i++)
                    for (int k = kk; k < kk + BLOCK && k < n; k++) {
                        double a = A[i * n + k];
                        for (int j = jj; j < jj + BLOCK && j < n; j++)
                            C[i * n + j] += a * B[k * n + j];
                    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <ijk|ikj|jki|block|omp> [n]\n", argv[0]);
        return 1;
    }
    const char *variant = argv[1];
    int n = argc > 2 ? atoi(argv[2]) : 1024;
    double *A = malloc(sizeof(double) * n * n);
    double *B = malloc(sizeof(double) * n * n);
    double *C = calloc((size_t)n * n, sizeof(double));
    if (!A || !B || !C) return 1;
    srand(1);
    for (long i = 0; i < (long)n * n; i++) {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
    }

    double t0 = now();
    if (!strcmp(variant, "ijk"))        mm_ijk(n, A, B, C);
    else if (!strcmp(variant, "ikj"))   mm_ikj(n, A, B, C);
    else if (!strcmp(variant, "jki"))   mm_jki(n, A, B, C);
    else if (!strcmp(variant, "block")) mm_block(n, A, B, C);
    else if (!strcmp(variant, "omp"))   mm_omp(n, A, B, C);
    else { fprintf(stderr, "variante inconnue: %s\n", variant); return 1; }
    double dt = now() - t0;

    double controle = 0;
    for (long i = 0; i < (long)n * n; i++) controle += C[i];
    double flop = 2.0 * n * n * n;
    int threads = 1;
#ifdef _OPENMP
    threads = omp_get_max_threads();
#endif
    printf("%-5s n=%d bloc=%d threads=%d: %.3f s, %.2f Gflop/s, controle=%.6e\n",
           variant, n, BLOCK, threads, dt, flop / dt / 1e9, controle);
    free(A); free(B); free(C);
    return 0;
}
