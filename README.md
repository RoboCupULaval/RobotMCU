# RobotMCU

## Procédure d'installation

1 - Installer l'IDE de votre choix (a ou b) et le toolchain :
  - Eclipse (Linux, Mac et Windows) : voir section Eclipse (plus bas)
    - Installer les plug-ins de AC6 (voir plus bas)
  - System Workbench (Linux et Windows) : voir section System Workbench (plus bas)
  
2 - Installer CubeMX (Linux, Mac et Windows)
  - http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html?sc=stm32cubemx (dans le bas de la page)

3 - Cloner le repo localement.

4 - Ouvrir le fichier .ioc à l'aide de CubeMX et cliquer sur générer le code.

5 - À l'aide de votre IDE, créer un workspace à la racine du repo et importer le projet :
  ->File->Import...->General->Existing Projects into Workspace
  
6 - Pour flasher le MCU, utilisez l'option Debug de l'IDE.

## Logiciels nécessaires
### CubeMX
Compatible avec Linux, Mac et Windows. Logiciel utilisé pour générer le code de base avec l'initialisation des périphériques du STM32.

### IDE
Deux choix selon votre OS :

#### System Workbench
Compatible avec Linux et Windows.
Détails à venir...

#### Eclipse
Compatible avec Linux, Mac et Windows.
Détails à venir...
