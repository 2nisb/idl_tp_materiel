# Installer les outils pour les TP du chapitre 2

Il faut un compilateur C, `make`, Python 3 avec `numpy` et `matplotlib`, et
quelques outils d'inspection de la machine. Comptez 15 minutes. Les mêmes
outils servent aux TP d'assembleur.

## macOS

1. Les outils en ligne de commande d'Apple fournissent `clang` (appelé
   aussi `cc` et `gcc`), `make` et `git`:

   ```bash
   xcode-select --install
   ```

   Si une commande répond `xcrun: error: invalid active developer path`,
   c'est cette étape qui manque.

2. Python 3 est fourni avec ces outils. Créez un environnement virtuel pour
   y installer les bibliothèques, le `pip` du système refuse de le faire:

   ```bash
   python3 -m venv ~/idl-venv
   source ~/idl-venv/bin/activate     # à refaire dans chaque nouveau terminal
   pip install numpy matplotlib
   ```

3. Optionnel, avec [Homebrew](https://brew.sh):

   ```bash
   brew install hwloc      # lstopo, dessin de la topologie
   brew install libomp     # OpenMP pour le TP 3 (make omp)
   ```

   `powermetrics`, pour la mesure d'énergie, est déjà dans macOS
   (`sudo powermetrics`). Les commandes `sysctl` du TP 1 aussi.

Remarque: `clang` d'Apple ne connaît pas `-march=native`; sur Apple
Silicon, l'équivalent est `-mcpu=native` et le TP 3 le signale.

## Linux

Debian, Ubuntu et dérivés:

```bash
sudo apt update
sudo apt install -y build-essential git python3 python3-venv python3-pip hwloc
sudo apt install -y linux-tools-common linux-tools-$(uname -r)    # perf, mesure d'énergie
```

Fedora:

```bash
sudo dnf install -y gcc make git python3 python3-pip hwloc perf
```

Puis Python, dans un environnement virtuel (les distributions récentes
refusent `pip install` en dehors):

```bash
python3 -m venv ~/idl-venv
source ~/idl-venv/bin/activate
pip install numpy matplotlib
```

Pour la mesure d'énergie, `perf stat -e power/energy-pkg/` demande les
droits administrateur: lancez-le avec `sudo`, ou abaissez
`kernel.perf_event_paranoid`:

```bash
sudo sysctl kernel.perf_event_paranoid=1
```

OpenMP est inclus dans `gcc`, `make omp` fonctionne sans rien d'autre.

## Windows: WSL2

Installez d'abord WSL2 et Ubuntu en suivant le
[guide WSL2](https://github.com/criminesparis/idl_tp_asm_x86_64/blob/main/WSL2.md)
du dépôt des TP d'assembleur, puis suivez les instructions Linux ci-dessus
dans le terminal Ubuntu.

Ce que WSL2 ne permet pas, à savoir pour les TP:

- `lscpu` et `lstopo` décrivent la machine virtuelle, pas le PC: le nombre
  de cœurs et les caches sont corrects, mais la topologie est simplifiée.
- `perf` et les compteurs d'énergie ne sont pas disponibles: sautez la
  partie énergie du TP 1. Les mesures de temps des TP 2 et 3 sont fiables.
- Travaillez dans le système de fichiers Linux (`~`), pas dans `/mnt/c`.

## VS Code

Un éditeur suffit, mais VS Code apporte le débogueur intégré et la vue
désassemblage, utiles pour les TP d'assembleur. Installez-le depuis
<https://code.visualstudio.com>, puis les extensions suivantes (panneau
Extensions, ou `code --install-extension <identifiant>`):

| Extension | Identifiant | Pour quoi |
|---|---|---|
| C/C++ | `ms-vscode.cpptools` | complétion, erreurs à la frappe, débogage avec `gdb` ou `lldb`, vue désassemblage |
| CodeLLDB | `vadimcn.vscode-lldb` | débogueur `lldb`, plus fiable que le précédent sous macOS |
| Makefile Tools | `ms-vscode.makefile-tools` | lancer les cibles des `Makefile` depuis l'éditeur |
| Python | `ms-python.python` | les scripts de tracé et de calcul; choisir l'interpréteur de `~/idl-venv` |
| WSL | `ms-vscode-remote.remote-wsl` | sous Windows: VS Code tourne côté Windows, le terminal, le compilateur et le débogueur côté Linux. Ouvrir avec `code .` depuis le terminal Ubuntu |
| Dev Containers | `ms-vscode-remote.remote-containers` | travailler dans un conteneur Docker, par exemple un Linux de l'autre architecture pour les TP d'assembleur |
| x86 and x86_64 Assembly | `13xforever.language-x86-64-assembly` | coloration de l'assembleur x86-64 |
| ARM | `dan-c-underwood.arm` | coloration de l'assembleur Arm, y compris AArch64 |
| Hex Editor | `ms-vscode.hexeditor` | regarder un fichier objet ou un exécutable octet par octet |

Réglages utiles:

- **Déboguer de l'assembleur.** Avec C/C++ ou CodeLLDB, créez une
  configuration de lancement (`Run > Add Configuration`) pointant sur le
  binaire compilé avec `-g`; les points d'arrêt se posent dans les `.S` et
  les registres s'affichent dans le panneau Variables. Pendant une session,
  le clic droit dans le source propose *Open Disassembly View*, qui montre
  les instructions machine générées pour un programme C: c'est Compiler
  Explorer en local.
- **Un programme qui prend le terminal** (TP du jeu): lancez-le dans le
  terminal intégré, et attachez le débogueur avec une configuration de type
  *attach* (`"request": "attach"`), ou débogez les fonctions une par une
  dans un petit programme de test.
- **Terminal intégré**: `Ctrl+ù` sur un clavier français, `Ctrl+`\` sur un
  clavier américain; sous WSL c'est un terminal Ubuntu.

## Vérifier l'installation

```bash
cc --version
make --version
python3 -c "import numpy, matplotlib; print('ok')"
cd 02_montagne && make && ./mountain | head -3 && cd ..
cd 03_matmul && make && ./matmul_O2 ikj 256 && cd ..
```

Les trois premières commandes doivent répondre sans erreur; les deux
dernières compilent et lancent brièvement les programmes des TP 2 et 3.

## Problèmes fréquents

- **`pip install` refuse avec `externally-managed-environment`**: vous
  n'êtes pas dans l'environnement virtuel; `source ~/idl-venv/bin/activate`.
- **`matplotlib` se plaint de l'absence d'affichage**: les scripts des TP
  écrivent des fichiers PNG et n'ouvrent pas de fenêtre, cette erreur ne
  devrait pas apparaître; sinon, `export MPLBACKEND=Agg`.
- **Les mesures varient beaucoup d'une exécution à l'autre**: fermez les
  autres programmes, branchez le portable sur secteur, et sous macOS
  désactivez le mode économie d'énergie le temps des mesures.
- **`make omp` échoue sous macOS**: `brew install libomp` manque, ou
  Homebrew n'est pas dans le `PATH` du terminal.
