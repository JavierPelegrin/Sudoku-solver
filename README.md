# Sudoku solver avec coloration de graph

Cette implementation est une maniere de resudre des sudoku en utilisent un algorithme de coloration de graphs.


## Installation

Ce code est entierement programmé en C

```
$ git clone https://github.com/JavierPelegrin/Sudoku-solver.git
```
Le répertoire telechagé contien un `makefile` et donc avec la commande `make solver` le code sera compilé.
Un binaire executable est généré appelé `solver`


## Test d'exécution
Après une exécution on reçoit sur le terminal:

```
$ ./solver
File : 
```
il faut ici donner la route a une grid de sudoku en format txt
par exemple `gridMedium.txt` qui vient inclue dans le repertoire.

Le résultat de l'execution du programme est donc:
```
$ ./solve
File : gridMedium.txt

0 0 0 0 0 8 2 0 0
2 0 5 7 0 0 0 0 0
3 6 0 0 0 0 0 8 0
4 2 0 0 3 5 0 0 7
0 0 3 0 0 0 0 0 0
0 0 0 8 2 0 4 6 0
9 7 0 4 0 0 5 0 2
0 3 0 0 5 0 0 0 4
5 4 0 2 0 0 6 0 8

Solving ....

1 9 7 3 4 8 2 5 6
2 8 5 7 6 9 3 4 1
3 6 4 5 1 2 7 8 9
4 2 8 6 3 5 1 9 7
6 1 3 9 7 4 8 2 5
7 5 9 8 2 1 4 6 3
9 7 6 4 8 3 5 1 2
8 3 2 1 5 6 9 7 4
5 4 1 2 9 7 6 3 8
```


## Le graph dans le sudoku

Pour pouvoir implementer un graph dans un sudoku il faut s'abstraire et voire chaque case du sudoku comme un node, au quelle on associe 21 nodes qui correspondent au nodes connectés à la casse que l'on etudie, on aurra donc 8 node en `vertical` et `horizontal` puis 4 autres nodes qui correspondent au nodes du `carré`.

## Algorithme de coloration

Mon algoritheme teste pour chaque node si il y a `une couleur` seule entre les neuf `couleur` posibles.

### Specification de l'algorithme

Le probleme de cette algorithme est de ne pas trouver un node avec une seule posibilité dans ce cas mon programme trouve un node avec deux posibilité et créée un processus fils, donc le père et le fils esseyent de résoudre le sudoku avec un chiffre different dans ce node. Le processus avec le chiffre erroné se termine quand il trouve un node ou il y a pas de posibilité.

## Specification

Pour implementer les nodes j'ai créée un TAD node et sudoku

**Implementation des nodes:**
```c
struct s_node{
    int id;
    int t[9];
    int sizeT;
    int root;
    node node[20];
}*node;
```
- La `id` est le identifiant du node entre `1` et `81`
- `t[9]` sont les posibilité `1` a `9` et remis a `-1` quand ce numero n'est pas une posibilité
- `sizeT` est le nombre de posibilité par node
- `root` est le chiffre qui correspond au chiffre du node, `0` si le node n'as pas encore de numero
- `node[20]` est un tableau de nodes associe au node

**Implementation du sudoku:**
```c
struct s_sudoku {
    int solved;
    node tab[81];
};
```

- `solved` est un nombre qui determine combien de node ont un nombre differnet de `0` solved vaut `81` quand le sudoku est résolu 
- `tab[81]` est un tableau de tous les nodes du sudoku


# Auteur du projet
- Javier Pelegrin Garcia - développeur - Documentation

## Remerciment 
Merci a Oriol Camps Perez pour l'idée et l'aide de la conseption de la partie des processus fils. 