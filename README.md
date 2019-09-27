# RobotMCU

## Structure des projets
- Src :
  - main.c : contient le code qui fait le lien entre tous les fichiers
  - freertos.c : contient le code d'initialisation et gestion des tasks 
  - Fichiers .c de configuration
  - robocup :
    - **fichiers sources spécifique à robocup**
- Inc :
  - Headers des fichiers de configuration
- *.ioc : fichier pour CubeMX


## Mode du robot
Le robot a divers modes pour facilité la détection de disfonctionnement.

#### Test senseurs de balles
Les senseurs de balles du robot peuvent être testé mettant la switch debug→ à OFF, en appuyant sur le bouton user pendant plus de 5 secondes. Les led sur l'avant du robot vont allumé en fonction à quel point quelque chose est proche des senseurs de balles.

#### Test le kick
Normalement, une commande de kick nécessite qu'une balle soit détecté pour des raisons de sécurité. Pour forcer un kick, il faut mettre le robot à l'id 0 et mettre la switch debug→ à ON.
Lorsque le bouton user est appuyé, le robot va kicker.

#### Test les moteurs et encodeurs
Pour testé si tout les moteurs et encodeurs marchent: mettez la switch debug→ à ON, ensuite fermez le robot complétement et réouvrez le (attention il faut utiliser la power switch, pas le bouton reset!). **Attention le robot va tourner sur lui-même, ne pas faire cela sur une table à moins qu'aucune des roues ne touchent le sol.** Si tous les tests réussissent le robot va arrêter de tourné sur lui-même. Si le robot continue de touné sur lui-même veuillez regarder avec le module bluetooth quel moteur ou encodeur est disfonctionelle.

## Procédure d'installation pour flasher un robot

1 - Installez l'IDE System Workbench (Linux et Windows) : voir section System Workbench (plus bas)
  
2 - Installez CubeMX (Linux, Mac et Windows)
  - Téléchargez [ici](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html?sc=stm32cubemx) (dans le bas de la page).

3 - Clonez le repo localement. `git clone https://github.com/RoboCupULaval/RobotMCU.git`

4 - Ouvrez le fichier `Robot_stm32f4discovery/Robot_stm32f4discovery_protoboard.ioc` à l'aide de CubeMX et cliquez sur générer le code en appuyant sur le bouton *GENERATE CODE*.

5 - À l'aide de votre IDE, créez un workspace à la racine du repo et importer le projet :
  ->File->Import...->General->Existing Projects into Workspace

6 - Compiler le programme en appuyant sur le marteau 🔨. Si vous avez des messages d'erreur relié a des fichiers dupliqué. Supprimé le fichier `Src/syscall.c`.

7 - Une fois que le programme compile sans erreur, pour flasher le MCU, il faut créer une configuration de débug. L'icone de débug est un insect 🐞. Allez dans Debug -> Debug Configurations... . Dans la nouveau fenêtre qui ouvre, créez un nouvelle configuration de debug de type 'Ac6 STM32 Debugging'. Ensuite, selectionné le C/C++ Application en appuyant sur le bouton 'Seach Project..' et selectionné `Debug/Robot_stm32f4discovery_protoboard.elf`. Ensuite, aller dans l'onglet 'Startup' pour mettre décoché l'option 'Set breakpoint at: `main`'.


![system workbench debug conf](https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/system_workbench_debug_conf.png)

8 - Maintenant, vous être prêt a flasher un robot. Il faut brancher dans votre port usb le flasher de robocup, connecter le cable ayant un connecteur bleu dans le port JTAG du robot. Oubliez pas de brancher une batterie et de démarrer le robot. **ATTENTION lorsque le robot est flasher il va se mettre à tourner sur lui-même, ne jamais flasher un robot donc les roues touchent le sol!** Lorsque tout cela est accomplie, vous pouvez flasher le robot en appuyant sur l'icone de l'insect 🐞.

## Logiciels nécessaires

### System Workbench
Compatible avec Linux et Windows. Pour le télécharger, vous devez créer un accompte [ici](https://www.openstm32.org/System+Workbench+for+STM32). Ensuite, [télécharger la dernière version](https://www.openstm32.org/Installing%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Bwith%2Binstaller) pour votre système d'exploitation.

### CubeMX
Compatible avec Linux, Mac et Windows. Logiciel utilisé pour générer le code de base avec l'initialisation des périphériques du STM32. Téléchargez [ici](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html?sc=stm32cubemx) (dans le bas de la page).

[Documentation](http://www.st.com/content/ccc/resource/technical/document/data_brief/7a/81/a9/b5/72/99/4b/be/DM00103564.pdf/files/DM00103564.pdf/jcr:content/translations/en.DM00103564.pdf)


## Procédure pour calibré les senseurs détecteurs de balle

Le robot de team ULtron utiliser deux senseurs infrarouges pour détecter la balle. Il est important de bien calibré ses senseurs. Pour ce faire le tutoriel suivant montre les étapes pour échantionné des positions de la balle, traitrer ses informations pour connaître les paramètres de configuration et comment flasher le robot pour qu'il utilise ses nouveaux paramètres.

1 - Branché un module bluetooth HC-05 dans le port bluetooth du robot. Attention, des fois le module bluetooth doit être branché dans le sense opposé de celui sur l'image. Si le module ne clignote pas et il se met à chauffer il est dans le mauvais sense.

<img alt="module bluetooth" src="https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/bluetooth_module.jpg" width="400" />

2 - Installé l'application [Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_CA). Il y a beaucoup d'application similaire qui font la même chose. Pairez le module bluetooth avec votre cellulaire et rajoutez le à l'application Bluetooth Terminal. Après avoir rajouté device module connectez vous, vous devriez voir les messages ci-dessous.

![android bluetooth terminal](https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/android_1.png?v=4&s=200)


3 - Pour procédé à la calibration, il faut que le robot soit en mode débug, pour ce faire, mettez la switch debug→ sur robot à on et appuyez une fois sur le bouton reset. Si le robot ce met à tourné sur lui-même, appuyez une fois sur le bouton reset pour l'arrêter.

4 - Maintenant pour tester si le robot est en bien en mode debug, envoyé la commande `help` en utilisant l'application Android. Vous devriez voir défilez une liste des commandes supporté par le robot. Note: pour envoyez des commandes vous pouvez les entrer manuellement, cela peut être un peu fatiguant. Pour vous facilité la vie, l'application Android supporte la mémorization de commandes en créant des macros.


![android macro](https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/android_2.png?v=4&s=200)

5 - Pour commencer la calibration tapez la commande `calib-start`. Ensuite, placé la balle en avant du robot. Si la balle est à un endroit où le kicker peut frapper la balle tapez la commande `calib-sample-good`, si au contraire le robot ne devrait pas être capable de détecté la balle à cette position envoyez la commande `calib-sample-bad`. Prenez votre temps pour bien échantionner toutes les positions possibles.

6 - Une fois que vous jugez avoir pris assez de sample, envoyer la commande `calib-stop`. Vous devriez voir un tableau csv des données que vous avez enregistré apparaître. Exemple de sortie:
```txt
12756|R5|B16.2|id,left,right,good
INFO|112757|R5|B16.2|0,378,569,1
INFO|112757|R5|B16.2|1,378,569,1
INFO|112758|R5|B16.2|2,374,597,1
INFO|112758|R5|B16.2|3,377,621,1
INFO|112758|R5|B16.2|4,373,646,1
INFO|112759|R5|B16.2|5,374,675,1
INFO|112759|R5|B16.2|6,365,766,1
INFO|112760|R5|B16.2|7,367,817,1
INFO|112760|R5|B16.2|8,365,791,1
INFO|112760|R5|B16.2|9,364,808,1
INFO|112761|R5|B16.2|10,361,867,1
INFO|112761|R5|B16.2|11,364,810,1
INFO|112762|R5|B16.2|12,365,786,1
INFO|112762|R5|B16.2|13,364,786,1
INFO|112762|R5|B16.2|14,361,780,1
INFO|112763|R5|B16.2|15,372,715,1
INFO|112763|R5|B16.2|16,460,518,1
INFO|112764|R5|B16.2|17,537,461,1
INFO|112764|R5|B16.2|18,596,453,1
INFO|112765|R5|B16.2|19,616,448,1
INFO|112765|R5|B16.2|20,636,451,1
INFO|112765|R5|B16.2|21,650,437,1
INFO|112766|R5|B16.2|22,583,443,1
INFO|112766|R5|B16.2|23,584,443,1
INFO|112767|R5|B16.2|24,572,440,1
INFO|112767|R5|B16.2|25,561,437,1
INFO|112768|R5|B16.2|26,536,432,1
INFO|112768|R5|B16.2|27,528,430,1
INFO|112768|R5|B16.2|28,367,426,-1
INFO|112769|R5|B16.2|29,379,421,-1
INFO|112769|R5|B16.2|30,374,416,-1
INFO|112770|R5|B16.2|31,370,415,-1
INFO|112770|R5|B16.2|32,367,415,-1
INFO|112771|R5|B16.2|33,369,408,-1
INFO|112771|R5|B16.2|34,371,416,-1
INFO|112771|R5|B16.2|35,374,428,-1
INFO|112772|R5|B16.2|36,373,425,-1
INFO|112772|R5|B16.2|37,365,439,-1
INFO|112773|R5|B16.2|38,371,439,-1
INFO|112773|R5|B16.2|39,374,434,-1
INFO|112774|R5|B16.2|40,378,423,-1
INFO|112774|R5|B16.2|41,382,420,-1
INFO|112774|R5|B16.2|42,381,420,-1
INFO|112775|R5|B16.2|43,375,432,-1
INFO|112775|R5|B16.2|44,376,429,-1
INFO|112776|R5|B16.2|45,373,434,-1
INFO|112776|R5|B16.2|46,372,488,-1
INFO|112777|R5|B16.2|47,373,525,-1
INFO|112777|R5|B16.2|48,366,565,-1
INFO|112777|R5|B16.2|49,372,521,-1
INFO|112778|R5|B16.2|50,404,437,-1
INFO|112778|R5|B16.2|51,462,425,-1
INFO|112779|R5|B16.2|52,485,431,-1
INFO|112779|R5|B16.2|53,466,427,-1
INFO|112779|R5|B16.2|54,446,429,-1
INFO|112780|R5|B16.2|55,433,566,1
INFO|112780|R5|B16.2|56,402,628,1
```

7 - Envoyez ce tableau sur votre pc et enregister sur un fichier csv par exemple `robot_6.csv`. Clonez le répertoire git des scripts de calibration et installez les dépendences:
```bash
git clone https://github.com/RoboCupULaval/embeddedTools.git
cd embeddedTools/ir_sensor_calib
python3 -m pip install install matplotlib numpy
```

8 - Ensuite, pour calibrer en utilisant notre fichier de configuration `robot_6.csv`. Entrez la commande:
```bash
python3 is_this_ai.py chemin/vers/ce/fichier/robot_6.csv
``` 

9 - Vous devriez voir ce graphique, les points oranges sont les samples où la balle n'était pas visible et les points bleues où la balle était visible. L'axe des x est la valeur du senseur de balle gauche, tandis que l'axe des y est la valeur du senseur droit.

![calibration no line](https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/calibration_no_line.png?v=4&s=200)

10 - Pour calibré vous devez dessinez une ligne qui sépare le mieux possible les points bleues des points oranges. Pour ce faire cliquez à deux endroits dans l'image pour dessinez une ligne:

![calibration no line](https://github.com/RoboCupULaval/RobotMCU/raw/develop/imgs/calibration_line.png?v=4&s=200)

11 - Lorsque vous dessinez une ligne les paramètres de cette lignes sont affichées dans la console:
```
Best weight [w0, w1, w2]: [1.0207495564366167, 1, -953.4778380748176]
Limit define by plane 1.0207x + 1.0000y + -953.4778 > 0
[test good points]
[test bad points]
Error 0/57
```

12 - Dans ce cas les paramètres sont donc `[1.0207495564366167, 1, -953.4778380748176]`.

13 - Changez la valeur des paramètres pour un robot ouvrez System Workbench (voir plus haut pour comment l'installer). Allez dans le fichier `Src/robocup/ball_detector.c`, il va y avoir un tableau comme celui-ci:
```c
ball_detector_config_t ID_TO_CONFIG[] = {
    // Each weight define a plane:  w0*x + w1*y + w2 = 0
    [0] = {{0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}, {0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}},
    [1] = {{0.6219987684566657, 1, -1036.919135431913}, {0.6219987684566657, 1, -1036.919135431913}},
    [2] = {{0.651431636200172, 1, -759.583743294228}, {0.651431636200172, 1, -759.583743294228}},
    [3] = {{0.8146000642262786, 1, -2092.9839388965}, {0.8146000642262786, 1, -2092.9839388965}}, // Actually robot 7, but it is in robot 3's tactic
    [4] = {{1.0966176108427819, 1, -2889.212766588539}, {1.0966176108427819, 1, -2889.212766588539}},
    [5] = {{1.0740060550333093, 1, -980.2164819285152}, {1.0740060550333093, 1, -980.2164819285152}},
    [6] = {{0.22124966030510002, 1, -690.7252221777143}, {0.22124966030510002, 1, -690.7252221777143}},
    [7] = {{-0.21673214791103368, 1, -983.663221668164}, {3.5655081406339626, 1, -5796.75941785768}}
};
```

14 - Pour changer la configuration du robot 4, il faut changer ligne `[4] = {{...}, {...}},`. Notre calibration nous a donnez 3 paramètres, alors pourquoi il y a 6 paramètres sur une ligne? Chaque robot peut avoir jusqu'à deux lignes pour la calibration, la plupart des robots en utilisent d'une seule. Si une seule ligne suffit alors il faut écrire deux fois les paramètres. Si on utilise les paramètres calculé à l'étape 12, alors la ligne du robot 4 est changé pour:
```
[4] = {{1.0207495564366167, 1, -953.4778380748176}, {1.0207495564366167, 1, -953.4778380748176}},
```

15 - Maintenant, la dernière étape est flasher le robot et tester la nouveau configuration. Utilisez la commandes `kick 15` pour tester le kick du robot. Une autre commande utile pour tester la detection de balle est `print-ball-sensors -1`. Attention, cette commande nécessite le redémarrage du robot pour pouvoir envoyer d'autres commandes.



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
