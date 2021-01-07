# TP1 - NMV: Gestion de la mémoire virtuelle

## Objectif:
Programmer la gestion de la MMU dans un mini système d'exploitation: "Rackdoll". 

## Exercice 1
Implémenter une fonction qui affiche la structure de la table des pages courantes.

Hypothèse: 
* Un niveau intermédiaire de la table des pages est mappé
par une identité (il est accessible par une adresse virtuelle égale à son adresse physique).

### Question 1

En supposant toujours qu’un niveau intermédiaire de la table des pages est mappé par une identité. Cele nous évite à traduire une adresse virtuelle en une adresse physique.

### Question 2
Dans une architecture 64 bits, il y a 2⁹, soit 512 entrées par niveau de table des pages.

La MMU détermine si une entrée est valide grâce au bit P qui vaut 1 quand l'entrée est valide.

Les entrées de PML4 et PML3 son non terminals. Celles de PML2 sont potentiellement terminals car elles peuvent contenir des huges pages que l'on peut déterminer avec le bit PS. Quant aux entrées de PML1, elles sont toutes terminales, chaque entrée valide est une page.

## Exercice 2
Implémenter une fonction qui permet de mapper une adresse virtuelle sur une adresse physique.

Hypothèses :
* Les niveaux intermédiaires de la table des pages sont tous mappés par une identité (l’adresse virtuelle
est égale à l’adresse physique).
* Tous les nouveaux mappings seront faits avec les droits utilisateurs (bit 2) et en écriture (bit 1).
* On ne cherche pas à gérer les huge pages.
* Si un mapping est demandé pour une adresse virtuelle α, l’adresse virtuelle α n’est pas déjà mappée.

### Question 1

A partir d'une adresse virtuelle donnée, on veut récupérer les 9 bits qui compose la PML.  
On commence par retirer les 12 bits de droite (Page offset) puis selon le niveau, on retire les bits des autres PML. Par exemple, pour le niveau 4, on retire 3*9 bits + 12 bits.  
Ensuite, pour récupérer les 9 bits de poids faible correspondant à l'index, on fait un décalage à gauche de 64-9 = 55 bits puis un décalage à droite de 55 bits.

Soit la formule suivante: 
```C
index = ((vaddr>>(12+((lvl-1)*9)))<<55)>>55;
```

### Question 2

On peut bien accéder à l'adresse 0x201000.
```
(qemu) x/8g 0x201000
0000000000201000: 0x0000000000000000 0x0000000000000000
0000000000201010: 0x0000000000000000 0x0000000000000000
0000000000201020: 0x0000000000000000 0x0000000000000000
0000000000201030: 0x0000000000000000 0x0000000000000000
```

### Divers

En général, la mémoire virtuelle et la mémoire physique sont structurées en unités d’allocations (pages pour la mémoire virtuelle et cadres pour la mémoire physique).

Les adresses virtuelles référencées par l’instruction en cours doivent
être traduites en adresses physiques. Cette conversion d’adresse est effectuée par des circuits matériels de gestion. Si cette adresse correspond à une
adresse en mémoire physique, on transmet sur le bus l’adresse réelle, sinon
il se produit un défaut de page.

## Exercice 3

Implémenter les fonctions nécessaires au chargement d’une tâche en mémoire.

### Question 1


