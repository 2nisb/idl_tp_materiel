# Travaux pratiques du chapitre 2: matériel

Dépôt des TP du chapitre "matériel" du cours *Introduction au développement
logiciel* (Mines Paris, PSL). Les transparents sont sur
[la page du cours](https://www.cri.minesparis.psl.eu/people/silber/cours/2026/idl/).

Trois TP qui s'enchaînent, sur votre propre machine (Linux, macOS, ou
Windows avec WSL2). Ils réutilisent la même façon de chronométrer et
aboutissent au chiffre qui a motivé le cours: le pourcentage de la
puissance crête de votre machine que votre code utilise réellement.

1. [`01_machine`](01_machine): lire sa machine et calculer sa puissance
   crête (1 h).
2. [`02_montagne`](02_montagne): la montagne mémoire, mesurer ses caches
   (2 h).
3. [`03_matmul`](03_matmul): produit de matrices, de Python à BLAS, le
   tableau de Leiserson refait par vous (3 h).

Le TP [STM32](stm32.md) sur carte Nucleo vient plus tard dans l'année.

Prérequis: un compilateur C, `make`, Python 3 avec `numpy` et
`matplotlib`. Voir [INSTALL.md](INSTALL.md) pour macOS, Linux et Windows
avec WSL2.
