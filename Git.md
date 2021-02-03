# NMV - Git

## Définitions

**Historique** : un graphe orienté acyclique composé d’un ensemble de versions pouvant être recalculées à partir des versions adjacentes en appliquant les patchs modélisés par les arcs sortants.

**Branche** : un sous graphecomposé de l’ensemble des versions accessibles depuis vi (la branche de la version vi d’un historique) dans le graphe de l’historique.

**Branche distante** : une branche qui pointe sur des dépôts distants en lecture et/ou écriture. Ces dépôts distants peuvent être référencés par une ou plusieurs personnes.

**branche locale** : une branche propre au dépôt local. Pour être envoyées, les données d’une telle branche doivent être fusionnées avec une branche distante.

**Tronc** ou **branche principale** : la branche issue de la dernière version stable.

**Merge** : toute version ayant un degré sortant strictement supérieur à 1. Cette version correspond alors à la fusion des patchs
de plusieurs branches.

**Blob** :  l’élément de base qui permet de stocker le contenu d’un fichier.

**Tree** : stocke la liste des fichiers d’un répertoire.  Un Tree est un ensemble de pointeurs vers des Blobs et d’autres Trees.

**Commit** : stocke l’état d’une partie du dépôt à un instant donné.  
Il contient : 
* un pointeur vers un Tree dont on souhaite sauver l’état.
* un pointeur vers un ou plusieurs autres Commits pour constituer un historique

**Tag** : permet d’identifier un des objets précédents à l’aide d’un nom.  
Il contient :
* un pointeur vers un Blob, un Tree ou un Commit.
* une signature.

**Conflits** : toute modification d’un fichier dans un dépôt
qui n’a pas été élaborée à partir de la version actuelle du fichier sur
ce dépôt, i.e.,lorsqu’il y a une modification de ce fichier sur le
dépôt pendant son édition.

------

## Les 4 types d'objets
Git utilise quatre types d’objets :
* **Blob** : Stocke le contenu des fichiers.
* **Tree** : Stocke l’arborescence.
* **Commit** : Stocke les versions du dépôt.
* **Tag** : Identifie certaines versions du dépôt.

**Attention** : Les objets de types Blob, Tree ou Commit ne sont **pas mutables**
et ne doivent normalement pas être supprimés.

------
## Les références d'objets
Git a été conçu comme un : **système de fichiers versionnés**.  
Les objets sont organisés sous formes d’un **graphe orienté acyclique**.

------

**SHA-1** est une fonction de hachage cryptographique.

**Git** utilise une numérotation globale des versions des fichiers :
* chaque numéro de version correspond à un état cohérent ;
* accès direct aux versions du système.

**Commiter** un fichier : enregistrer une version de ce dernier (le plus souvent la version actuelle, mais pas toujours) dans un gestionnaire de versions. Par extension, si le fichier est déjà versionné, on dit que l’on commit une modification du fichier.

------

**Les points forts** :
+ Certainement le plus rapide à appliquer des patchs
+ Simple à mettre en place (mode sans serveur)
+ Petits outils puissants (esprit Unix)
+ Git est distribué sous licence GNU GPL 2
+ Développement actif
+ Linus
  
**Les points faibles** :
- Courbe d’apprentissage
- Linus
J. Sopena (INRIA/UPMC) G