CC ?= cc
CFLAGS = -O2 -Wall -g

mountain: mountain.c
	$(CC) $(CFLAGS) -o $@ $<

mountain.csv: mountain
	./mountain > $@

plots: mountain.csv
	python3 plot_mountain.py mountain.csv

clean:
	rm -rf mountain mountain.dSYM mountain.csv mountain_3d.png mountain_stride1.png

.PHONY: plots clean
