# RobotMCU

## Procédure d'installation

1 - Installez l'IDE de votre choix :
  - Eclipse (Linux, Mac et Windows) : voir section Eclipse (plus bas)
    - Installez les plug-ins de AC6 (voir plus bas)
  - System Workbench (Linux et Windows) : voir section System Workbench (plus bas)
  
2 - Installez CubeMX (Linux, Mac et Windows)
  - Téléchargez [ici](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html?sc=stm32cubemx) (dans le bas de la page).

3 - Clonez le repo localement. **Faites un checkout sur la branche develop pour modifier le code**.

4 - Ouvrez le fichier .ioc à l'aide de CubeMX et cliquez sur générer le code.

5 - À l'aide de votre IDE, créez un workspace à la racine du repo et importer le projet :
  ->File->Import...->General->Existing Projects into Workspace
  
6 - Pour flasher le MCU, utilisez l'option Debug de l'IDE.

## Logiciels nécessaires
### CubeMX
Compatible avec Linux, Mac et Windows. Logiciel utilisé pour générer le code de base avec l'initialisation des périphériques du STM32. Téléchargez [ici](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html?sc=stm32cubemx) (dans le bas de la page).

[Documentation](http://www.st.com/content/ccc/resource/technical/document/data_brief/7a/81/a9/b5/72/99/4b/be/DM00103564.pdf/files/DM00103564.pdf/jcr:content/translations/en.DM00103564.pdf)

### IDE
Deux choix selon votre OS :

#### System Workbench
Compatible avec Linux et Windows.
Détails à venir...

#### Eclipse
Compatible avec Linux, Mac et Windows.

##### Installation :
- Téléchargez Eclipse [ici](https://eclipse.org/downloads/). Sélectionnez la version pour C/C++ selon votre OS.
- Installez Eclipse sur votre machine.
- Ouvrez Eclipse et allez dans Help->Install new software...
- Ajoutez une nouvelle source, avec le nom que vous désirez (ex: stm32) et avec comme "Location" : http://www.openstm32.org/Eclipse-updates/org.openstm32.system-workbench.site
- Vous pouvez maintenant sélectionnez les items à installer. Vous aurez besoin du ARM Compiler, de OpenOCD et de External Tools. Vous n'avez qu'à cocher les items correspondant à votre OS.
- Faites Next... jusqu'à ce que l'installation soit complété.
- Vous devriez maintenent être capable d'importer le projet et le compiler.

## Ressources
### STM32Cube
Librairies et logiciel de ST
- [RTOS et STM32Cube](http://www.st.com/content/ccc/resource/technical/document/user_manual/2d/60/ff/15/8c/c9/43/77/DM00105262.pdf/files/DM00105262.pdf/jcr:content/translations/en.DM00105262.pdf)
- [Library HAL User manual](http://www.st.com/content/ccc/resource/technical/document/user_manual/2f/71/ba/b8/75/54/47/cf/DM00105879.pdf/files/DM00105879.pdf/jcr:content/translations/en.DM00105879.pdf)
- [CubeMX documentation](http://www.st.com/content/ccc/resource/technical/document/data_brief/7a/81/a9/b5/72/99/4b/be/DM00103564.pdf/files/DM00103564.pdf/jcr:content/translations/en.DM00103564.pdf)

### FreeRTOS
RTOS utilisé pour le projet
- [Site officiel](http://www.freertos.org/)

### STM32F4
MCU utilisé pour le projet
- [STM32F4Discovery kit user manual](http://www.st.com/content/ccc/resource/technical/document/user_manual/70/fe/4a/3f/e7/e1/4f/7d/DM00039084.pdf/files/DM00039084.pdf/jcr:content/translations/en.DM00039084.pdf)
- [STM32F4  Datasheet](http://www.st.com/content/ccc/resource/technical/document/datasheet/ef/92/76/6d/bb/c2/4f/f7/DM00037051.pdf/files/DM00037051.pdf/jcr:content/translations/en.DM00037051.pdf)
- [STM32F4 Reference manual](http://www.st.com/content/ccc/resource/technical/document/reference_manual/3d/6d/5a/66/b4/99/40/d4/DM00031020.pdf/files/DM00031020.pdf/jcr:content/translations/en.DM00031020.pdf)
