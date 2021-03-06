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


## Exercice 3

Implémenter les fonctions nécessaires au chargement d’une tâche en mémoire.

### Question 1

```C
 * +----------------------+ 0x00007fffffffffff
 * | User                 |
 * | (text + data + heap) | 0x2000000030 -> page fault
 * +----------------------+ 0x2000000000 = 128 GiB
 * | User                 |   
 * | (stack)              |
 * +----------------------+ 0x40000000 = 1 GiB
 * | Kernel               |
 * | (valloc)             |
 * +----------------------+ 0x201000
 * | Kernel               |
 * | (APIC)               |
 * +----------------------+ 0x200000 = 2 MiB
 * | Kernel               |
 * | (text + data)        |
 * +----------------------+ 0x100000
 * | Kernel               |
 * | (BIOS + VGA)         |
 * +----------------------+ 0x0
```
Seules les premières 2 MiB adresses sont mappées. L'adresse 0x2000000030 n'étant pas mappée, cela produit alors une faute de page.


### Question 2

Il faut conserver le code kernel, soit entre 0x0 et 0x40000000, qui ne doit jamais être jamais changé quelque soit la tâche courante.


### Question 3

Adresses virtuelles:
* début du _payload_: ctx->load_vaddr  
* fin du _payload_: ctx->load_vaddr + (ctx->load_end_paddr - ctx->load_paddr)
* début du _bss_: ctx->load_vaddr + (ctx->load_end_paddr - ctx->load_paddr) + 0x1
* fin du _bss_: ctx->bss_end_vaddr


## Exercice 4

Implémenter les fonctions d'allocation.

### Question 2
```
 * +----------------------+ 0x2000000000
 * | User                 | 0x1ffffffff8  -> page fault
 * | (stack)              |	
 * +----------------------+ 0x40000000
```
Etant donné que l'adresse se trouve dans la pile, la faute de page est causée par un accès mémoire légitime.

### Question 3
(Cours) Sous Linux, l’allocation mémoire est paresseuse: 
* Conséquence : malloc(1 << 40) retourne une adresse utilisable
* La mémoire ne sera allouée quand l’adresse sera utilisée

## Exercice 5

Implémenter la fonction de libération.

### 