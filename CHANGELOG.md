[![GitHub license](https://img.shields.io/github/license/Chucky2401/Minecraft-Advancements)](https://github.com/Chucky2401/Minecraft-Advancements/blob/master/LICENSE.md) [![GitHub issues](https://img.shields.io/github/issues/Chucky2401/Minecraft-Advancements?style=plastic)](https://github.com/Chucky2401/Minecraft-Advancements/issues) [![GitHub stars](https://img.shields.io/github/stars/Chucky2401/Minecraft-Advancements)](https://github.com/Chucky2401/Minecraft-Advancements/stargazers) [![Twitter](https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2FGoCChucky2401)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2FChucky2401%2FMinecraft-Advancements) [![Twitter](https://img.shields.io/twitter/url?label=Facebook&logo=facebook&style=social&url=https%3A%2F%2Fwww.facebook.com%2FChucky2401.GoC%2F)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2FChucky2401%2FMinecraft-Advancements)

# Minecraft Advancements

Suivis des version

## **V1.0.0** - 16/06/2020

### Correction

+ Pour certains progrès, ce n'était pas une apostrophe du clavier AZERTY, mais un caractère similaire. Ajout d'un *remplace* pour mettre le caractère de nos claviers.

### Modification

+ Suite à l'achat d'un serveur avec nom de domaine, modification des repository :wink:

## **V0.2.5 Hotfix 3 (0.2.5.3)** - 14/06/2020

### Correction

+ Si recherche mise à jour Bêta, mauvais paramètre passer à l'outils de maintenance.

  Vous avez deux solutions pour avoir cette mise à jour :

  1. Désinstaller toutes version précédentes et réinstaller cette version.
  2. Suivre le tuto [ici](https://github.com/Chucky2401/Minecraft-Advancements/wiki/Mise-à-jour-en-bêta-avant-v0.2.5.3) !
  
+ Utilisation d'une fonction pour activation/désactivation des boutons d'extraction, car bug lors de changement de version de Minecraft ou autres.

### Ajout

+ Message indiquant que l'outils de maintenance va démarrer pour guider dans la mise à jour.

## **V0.2.5 Hotfix 2 (0.2.5.2)** - *Non déployer*

### Correction

+ Oublie des dates dans le bouton "Effacer les filtres"
+ Ajout du *Microsoft Visual C++ 2010 x86 Runtime* pour le support SSL. Sinon la recherche de mise à jour auto ne fonctionne pas sans. Si besoin vous pouvez le télécharger [ici](https://download.microsoft.com/download/5/B/C/5BC5DBB3-652D-4DCE-B14A-475AB85EEF6E/vcredist_x86.exe). En gros, le programme dit toujours être dans la version la plus récente, alors que non.

### Ajout

+ Un bouton pour supprimer le filtre sur les dates seulement

  ![Imgur](https://i.imgur.com/CMExm5mm.png)

## **V0.2.5 Hotfix 1 (0.2.5.1)** - 13/06/2020

### Correction

+ La recherche de mise à jour ne fonctionne pas du tout depuis la 0.2.4.1. Correction du code.
  **Il est nécessaire de réinstaller complètement l'applications !**

## **V0.2.5** - *Non déployer*

### Ajout

+ Bouton Imprimer dans le menu Outils
  
  ![Imgur](https://i.imgur.com/62Lgtfpm.png)
  
+ [Issue#4](https://github.com/Chucky2401/Minecraft-Advancements/issues/4) **Mémorisation des saisis** Vous pouvez maintenant utiliser ce paramètre ! Il permet de mémoriser et restaurer au démarrage :
  
  + Version
  + Dossier 'Blaze and Cave'
  + Afficher les Milestones ?
  + Afficher les Statistiques ?
  + Fichier Progrès
  
+ [Issue#13](https://github.com/Chucky2401/Minecraft-Advancements/issues/13) **Nettoyage nom condition** Traduction du maximum possible en utilisant les fichiers de Minecraft. Cela ne peut tout traduire, mais plus facile déjà pour tout le monde je pense.
Attention, cette partie ralenti pas mal lors de la comparaison pour Blaze And Cave
  
  ![Imgur](https://i.imgur.com/wt1KvbKm.png)

### Modification

+ Ajout d'icônes pour les *Opérations*
  
  ![Imgur](https://i.imgur.com/tLQhBJwm.png)
  
+ Ajout de raccourcis clavier pour le menu
  + *Ctrl+Q* - **Quitter**
  + *Ctrl+I* - **Préférences**
  + *Ctrl+H* - **A Propos**
  + *Ctrl+U* - **Vérifier les mise à jour**
  + *Ctrl+P* - **Imprimer la vue**
  
+ Même si les mises à jour Bêta sont recherchés. Une vérification sur le canal Release sera effectué en suivant pour être sûr de ne pas louper une version. Car aucun intérêt de mettre à jour un canal Bêta, alors que la Release apporte toutes les fonctionnalitées de ce dernier voir plus.

### Divers

+ Gros refactoring du code
  + Commentaire
  + Modification de fonction pour l'arriver de la restauration des saisis précédente
  + Position de certaines fonctions dans le fichier
+ Clôture [Issue#7](https://github.com/Chucky2401/Minecraft-Advancements/issues/7) **Réglages** Car la mémorisation des saisis et fait ! **Quand tout sera cocher dans *Ajout* - Je prends de l'avance sur le Changelog :stuck_out_tongue_closed_eyes:**
+ Je repousse l'[Issue#3](https://github.com/Chucky2401/Minecraft-Advancements/issues/3) **Masquer progrès**, car beaucoup de travail dessus. Et les filtres permettent de se *dépatouiller* pour le moment je pense.
+ Modification pour ignorer les commentaires dans les fichiers JSON de langue BACAP qui n'est pas un standard...
+ Utilisation de fonction pour éviter le code répétitif

### Notes

+ Il reste des commentaires à ajouter
+ ~~Alléger le fichier de la classe à mettre dans plusieurs fichiers pour clarter~~

## **V0.2.4.1** - *03/02/2020*

### Correction

+ **Mise à jour automatique** Oublie de fichier DLL et déplacement d'un fichier, car manque d'autorisation.

## **v0.2.4** - *02/06/2020*

### Ajouts

+ [Issue#10](https://github.com/Chucky2401/Minecraft-Advancements/issues/10) **Mise à jour auto** Possibilité d'activer la recherche de mise à jour et/ou de faire une recherche de mise à jour manuelle ! Possible de choisir le canal Beta (instable).

+ **Icones** Ajout d'icones sur les boutons du menu :wink:

+ **Légende** Ajout d'une légende pour les couleurs

+ **Images** *Pour les chats seulement* Les chats se voient leurs images ajouté à côté du texte et en plus grand avec la souris dessus.
  
  ![Imgur](https://i.imgur.com/DjYZVkPm.png)
  
+ [Issue#16](https://github.com/Chucky2401/Minecraft-Advancements/issues/16) **Filtrer sur la date de réalisation** Il est maintenant possible de filtrer entre deux dates.
  
  ![Date Filtre](https://i.imgur.com/vSTXtwQm.png)
  
+ [Issue#14](https://github.com/Chucky2401/Minecraft-Advancements/issues/14) **Masquer les milestones** Possibilités de ne pas afficher les progrès sur les milestones et/ou les statistiques.

### Modifications

+ **Installeur** Encore des changements sur l'installeur ! Retrait du dépôts *Beta* ce dernier est ajouté temporairement si l'installeur est fait pour installer une version Beta. Et il est aussi ajouter temporairement, si l'utilisateur choisis les mise à jour Beta dans l'application. Plus aucune mention de ce dernier ailleurs, il est *invisible*.
  Plus facile à gérer pour vous et pour moi :wink:
+ **Type de condition** Modification des couleurs, du moins ajout d'une couleur pour les conditions unique (jaune foncé).
  + <span style=" color:#808000;">Condition Unique</span>
+ **Condition pour les chats** Au lieu du chemin vers la texture, seulement le nom est affiché

### Correction

+ **Colonne Type** La colonne *Type* qui affichait **ET** ou **OU** pour le type de condition, n'était pas masqué pour les progrès *Vanilla* seulement. C'est un oublie, une ligne de code commenté lors d'un test 😲
+ [Issue#15](https://github.com/Chucky2401/Minecraft-Advancements/issues/15) **Filtre sur type et condition fait** Si on filtrait sur la condition fait ou non, puis sur le type, le filtre sur la condition fait sauté et ne pouvait plus être appliquée.

## **v0.2.3** - *21/05/2020*

### Ajouts

+ [Issue#12](https://github.com/Chucky2401/Minecraft-Advancements/issues/12) **Type Condition (ET ou OU)** Si une condition et de type **ET** : *toutes les conditions sont nécessaires au progrès* ; De type **OU** : *une condition est suffisante*

+ **Couleurs** Ajout de couleurs en fonction du type ou si le progrès est finis. (cf. [Screenshot](https://github.com/Chucky2401/Minecraft-Advancements/issues/12#issuecomment-631973057))
  + <span style=" color:#006400;">Progrès réalisé</span>
  + <span style=" color:#8b0000;">Condition de type ET</span>
  + <span style="color: blue;">Condition de type OU</span>

+ **Effacer les filtres** Ajout d'un bouton pour effacer les filtres.

+ **Écran de démarrage** ou *Splash Screen* en anglais. Petite funitude :yum:
  
  ![SplashScreen](https://i.imgur.com/hwnkLdqm.png)

## **v0.2.1** - *15/05/2020*

### Ajout

+ [Issue#5](https://github.com/Chucky2401/Minecraft-Advancements/issues/5) **Bouton Imprimer** *Permet d'imprimer la vue des progrès en cours.*

+ [Issue#6](https://github.com/Chucky2401/Minecraft-Advancements/issues/6) **Ajout d'un menu**

  + Menu Principale
    

  ![Menu](https://i.imgur.com/htvqUpSm.png)

  Contient :

    + Fichier -> Quitter (Raccourcis : CTRL + Q)
    + Outils -> Préférences (Raccourcis : CTRL + I)
  + ? -> A Propos
    
  + Par la même occasion, ajout d'une fenêtre *A Propos*. Contient un lien vers *GitHub*, *Discord des GoC*, chaine YouTube de *Olchladir* et *Athlif*
    

  ![About](https://i.imgur.com/FvIXU8wm.png)

  + Ajout de la fenêtre de préférences **/!\\ En cours d'écriture /!\\**
    

  ![Settings](https://i.imgur.com/NhVQ5Zcm.png)

  + Ajout d'une confirmation de fermeture
    
    ![Confirmation](https://i.imgur.com/cWujerSm.png)

+ **Mémorisation taille et position** En ajoutant la fenêtres des préférences *(repris d'un autre de mes programmes)*, ajout de cette fonctionnalité. Au redémarrage du programme, si cette option est active la fenêtre sera remise à la même taille qu'à la fermeture.


### Modification

+ [Issue#8](https://github.com/Chucky2401/Minecraft-Advancements/issues/8)

  - **Filtre sur les titres** *Ajout d'une option activable / désactivable pour filtrer sous forme d'Expressions Régulière. [Par ici](https://www.lucaswillems.com/fr/articles/25/tutoriel-pour-maitriser-les-expressions-regulieres) si vous ne connaissez pas.*

    ![Filtre et bouton imprimer](https://i.imgur.com/iZGgNvlm.png)
  
  - **Taille filtre des titres** Agrandissement sur le nombre d'éléments visibles à la fois
  
    ![Taille Filtre Titre](https://i.imgur.com/kEKiI9Im.png)
  
  - **Affichage autocomplétions** Affichage dans un pop-up. Il est plus facile de voir toutes les propositions lors de la recherche du titre.
  
    ![Affichage autocomplétion](https://i.imgur.com/b2OBpeom.png)
  
  - **Activer/désactiver autocomplétions** Possibilité de l'activé ou non :wink:
  
    ![activation](https://i.imgur.com/6FrUSDJm.png)
  
  - **Ajout d'un séparateur** dans le champ de filtre sur le titre avant *----- Blaze and Cave -----* lors de la comparaison de tous *Vanilla + Blaze and Cave*


+ **Filtres et Opérations** Déplacement du bouton *Imprimer* dans un group *Opérations* avec le bouton *Effacer les filtres*
  
  ![Filtres et Opérations](https://i.imgur.com/wQeZGWim.png)
  
+ **Installeur** Ajout du dépôt *Beta* activable par l'utilisateur

### Correction

+ [Issue#2](https://github.com/Chucky2401/Minecraft-Advancements/issues/2) **Oublie de dll** (**D**ynamic **L**ink **L**ibrary => Bibliothèque de lien Dynamique [Qu'est-ce que c'est ?](https://support.microsoft.com/fr-fr/help/815065/what-is-a-dll#section-2 "Microsoft")) dans le premier déploiement qui empêcher le fonctionnement.
+ [Issue#9](https://github.com/Chucky2401/Minecraft-Advancements/issues/9) **Correction sur le déblocage** pour comparer seulement les progrès *Blaze and Cave*, le choix de la version n'est plus nécessaire.
+ [Issue#1](https://github.com/Chucky2401/Minecraft-Advancements/issues/1) **Lecture Blaze and Cave** Erreur lors de lecture de deux fichiers. *Blaze and Cave* ont corrigé le problème avec [l'update 10](http://www.mediafire.com/file/ns5scgclysp08oy/BlazeandCave%2527s_Advancements_Pack_1.10_Beta_Build_10.zip/file).

### Divers

+ **Refactoring** ou *Réusinage de code* est l'opération consistant à retravailler le code source d'un programme informatique. (<u>Source</u> : [Wikipédia](https://fr.wikipedia.org/wiki/Réusinage_de_code))

## **v0.1.1** - *07/05/2020*

Première version en Bêta
