# Travaux pratiques STM32

## Étapes préliminaires

- Installer le plugin VSCode "[STM32Cube for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension)"
- Installation de [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html) (1.19.0)
  - Sur mac, installation `st-stm32cubeclt_1.19.0_25876_20250729_1159-macosx_x86_64.pkg`
  - Sur mac, installation de `st-stlink-server.2.1.1-2.pkg`
  - Sur Mac, l'installation de fait sous `/opt/ST/STM32CubeCLT_1.19.0`
- Installation de [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) (6.15.0)
- Installation de [ST-MCU-FINDER](https://www.st.com/en/development-tools/st-mcu-finder-pc.html)

## Exercices

- Faire clignoter la LED bleue toutes les 100 ms.
- Envoyer la chaîne de caractères "hello, world!" toutes les 100ms sur le port série de la liaison USB avec le ST-Link, en faisant clignoter la LED rouge à chaque envoi de message
  - Minicom (macOS et Linux): `minicom -D /dev/ttyACM0` (quitter avec CTRL-a x)
  - Screen (macOS et Linux): `screen /dev/ttyACM0 115200` (quitter avec CTRL-a k)
  - Putty (Windows et Linux)
  - Hyperterminal (Linux)
- Modifier votre code pour que le STM32 soit pilotable par un mini "shell". Par défaut le STM32 affichera une invite de commandes `commande?>` et attendra des commandes. Parmi les commandes, on peut par exemple définir une commande `led (red|blue|green) (on|off)` qui allume ou éteint la LED correspondante, ou `show 'MESSAGE' 10 200` qui affiche 10 fois `MESSAGE` avec un délai de 200 ms entre chaque affichage avant de rendre la main à l'invite de commandes. La commande `help`

## Ressources

### STMicroelectronics

- [UM1739 User manual, Getting started with STM32CubeF2 firmware package for STM32F2 Series](https://www.st.com/resource/en/user_manual/um1739-getting-started-with-stm32cubef2-firmware-package-for-stm32f2-series-stmicroelectronics.pdf)
- Librairies logicielles à la base de STM32CubeMX: [STM32Cube MCU Full
  Package for the STM32F2
  series](https://github.com/STMicroelectronics/STM32CubeF2), avec de
  nombreux exemples (Pilotes HAL et LL,
  [CMSIS](https://arm-software.github.io/CMSIS_5/General/html/index.html),
  midleware libraries). Voir également: [AN4733, Application note,
  STM32Cube firmware examples for STM32F2
  Series](https://www.st.com/resource/en/application_note/an4733-stm32cube-firmware-examples-for-stm32f2-series-stmicroelectronics.pdf)
- [STM32 Nucleo-144 development board with STM32F207ZG MCU, supports Arduino, ST Zio and morpho connectivity](https://www.st.com/en/evaluation-tools/nucleo-f207zg.html)
- [PM0056 Programming manual,STM32F10xxx/20xxx/21xxx/L1xxxx Cortex-M3 programming manual](https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortexm3-programming-manual-stmicroelectronics.pdf)
- [PM0059 Programming manual, STM32F205/215, STM32F207/217 Flash programming manual](https://www.st.com/resource/en/programming_manual/pm0059-stm32f205215-stm32f207217-flash-programming-manual-stmicroelectronics.pdf)
- [RM0033 Reference manual, STM32F205xx, STM32F207xx, STM32F215xx and STM32F217xx advanced Arm-based 32-bit MCUs](https://www.st.com/resource/en/reference_manual/cd00225773-stm32f205xx-stm32f207xx-stm32f215xx-and-stm32f217xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [Datasheet STM32F205xx, STM32F207xx, Arm-based 32-bit MCU, 150 DMIPs, up to 1 MB Flash/128+4KB RAM, USB OTG HS/FS, Ethernet, 17 TIMs, 3 ADCs, 15 comm. interfaces and camera](https://www.st.com/resource/en/datasheet/stm32f207vg.pdf)
- [TN1235 Technical note, Overview of ST-LINK derivatives](https://www.st.com/resource/en/technical_note/tn1235-overview-of-stlink-derivatives-stmicroelectronics.pdf)
- [UM1713 User manual, Developing applications on STM32Cube with LwIP TCP/IP stack](https://www.st.com/resource/en/user_manual/dm00103685-developing-applications-on-stm32cube-with-lwip-tcpip-stack-stmicroelectronics.pdf)
- [UM1721 User manual, Developing applications on STM32Cube™ with FatFs](https://www.st.com/resource/en/user_manual/um1721-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf)
- [UM1722 User manual, Developing applications on STM32Cube with RTOS](https://www.st.com/resource/en/user_manual/um1722-developing-applications-on-stm32cube-with-rtos-stmicroelectronics.pdf)
- [UM1727 User manual, Getting started with STM32 Nucleo board software development tools](https://www.st.com/resource/en/user_manual/um1727-getting-started-with-stm32-nucleo-board-software-development-tools-stmicroelectronics.pdf)
- [UM1940 User manual, Description of STM32F2 HAL and low-layer drivers](https://www.st.com/resource/en/user_manual/um1940-description-of-stm32f2-hal-and-lowlayer-drivers-stmicroelectronics.pdf)
- [UM1974 User manual, STM32 Nucleo-144 boards (MB1137)](https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf)
- [UM2298 User manual, STM32Cube BSP drivers development guidelines](https://www.st.com/resource/en/user_manual/dm00440740-stm32cube-bsp-drivers-development-guidelines-stmicroelectronics.pdf)
