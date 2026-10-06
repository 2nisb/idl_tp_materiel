"""Puissance crête d'un processeur en flop/s.

Exemples:
  python3 peak.py --cores 8 --ghz 3.5 --simd-bits 256 --units 2 --fma
  python3 peak.py --cores 4 --ghz 3.2 --simd-bits 128 --units 4 --fma   # Apple M (cœurs P)
"""
import argparse

p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
p.add_argument("--cores", type=int, required=True, help="nombre de cœurs")
p.add_argument("--ghz", type=float, required=True, help="fréquence en GHz (soutenue sur tous les cœurs)")
p.add_argument("--simd-bits", type=int, default=128, help="largeur des registres SIMD en bits")
p.add_argument("--units", type=int, default=1, help="unités SIMD flottantes par cœur")
p.add_argument("--fma", action="store_true", help="multiplication-addition fusionnée (2 flop par voie)")
a = p.parse_args()

for nom, bits in (("double", 64), ("simple", 32)):
    voies = a.simd_bits // bits
    flop_cycle = voies * a.units * (2 if a.fma else 1)
    gflops = a.cores * a.ghz * flop_cycle
    print(f"{nom:7s}: {voies} voies x {a.units} unités x {2 if a.fma else 1} = "
          f"{flop_cycle} flop/cycle/cœur -> {gflops:8.1f} Gflop/s sur {a.cores} cœurs")
