CC ?= cc
BLOCK ?= 64
CFLAGS_O0 = -O0
CFLAGS_O2 = -O2
CFLAGS_O3 ?= -O3
N ?= 1024

all: matmul_O0 matmul_O2 matmul_O3

matmul_O0: matmul.c
	$(CC) $(CFLAGS_O0) -Wall -DBLOCK=$(BLOCK) -o $@ $<

matmul_O2: matmul.c
	$(CC) $(CFLAGS_O2) -Wall -DBLOCK=$(BLOCK) -o $@ $<

matmul_O3: matmul.c
	$(CC) $(CFLAGS_O3) -Wall -DBLOCK=$(BLOCK) -o $@ $<

# OpenMP: gcc sous Linux; sous macOS, brew install libomp puis make omp
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
OMPFLAGS = -Xpreprocessor -fopenmp -I$(shell brew --prefix libomp 2>/dev/null)/include -L$(shell brew --prefix libomp 2>/dev/null)/lib -lomp
else
OMPFLAGS = -fopenmp
endif

omp: matmul_omp
matmul_omp: matmul.c
	$(CC) $(CFLAGS_O3) $(OMPFLAGS) -Wall -DBLOCK=$(BLOCK) -o $@ $<

# Assembleur de la version -O3, pour y chercher les instructions SIMD
asm: matmul.c
	$(CC) $(CFLAGS_O3) -DBLOCK=$(BLOCK) -S -o matmul_O3.s $<
	@echo "voir matmul_O3.s, fonction mm_ikj ou mm_block"

# Toutes les mesures d'un coup
bench: all
	python3 matmul.py 256
	./matmul_O0 ijk $(N)
	./matmul_O2 ijk $(N)
	./matmul_O2 ikj $(N)
	./matmul_O2 jki $(N)
	./matmul_O2 block $(N)
	./matmul_O3 ikj $(N)
	./matmul_O3 block $(N)
	-[ -x matmul_omp ] && ./matmul_omp omp $(N)
	-python3 matmul_numpy.py $(N) 2>/dev/null | head -1

clean:
	rm -rf matmul_O0 matmul_O2 matmul_O3 matmul_omp matmul_O3.s *.dSYM

.PHONY: all omp asm bench clean
