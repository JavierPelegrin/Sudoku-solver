# Sudoku solver avec coloration de graph 
Cette implémentation est un algorithme de résoudre des sudokus en utilisent un algorithme de coloration de graphs. 

## Installation 

Ce code est entièrement programmé en C
``` 
$ git clone https://github.com/JavierPelegrin/Sudoku-solver.git 
``` 

Le répertoire téléchargé contient un `makefile` et donc avec la commande `make solver` le code sera compilé. 

Un binaire exécutable est généré appelé `solver` 

## Test d'exécution 

Après une exécution on reçoit sur le terminal : 

``` 
$ ./solver 
File :  
```
Il faut ici donner la route a une grid de sudoku en format txt 
Par exemple `gridMedium.txt` qui vient inclue dans le répertoire. 

Le résultat de l'exécution du programme est donc : 

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

A la sortie du programme le sudoku résolu est exporté en `.txt` a un fichier appelle `gridSolved.txt` 

## Le graph dans le sudoku 

Pour pouvoir implémenter un graph dans un sudoku il faut s'abstraire et voire chaque case du sudoku comme un Node, au quelle on associe 21 Nodes qui correspondent au Nodes connectés à la casse que l'on étudie, on aura donc 8 Node en `vertical` et `horizontal` puis 4 autres Nodes qui correspondent au Nodes du `carré`. 

## Algorithme de coloration 

Mon algorithme teste pour chaque Node s'il y a `une couleur` seule entre les neuf `couleurs` possibles. 

### Spécification de l'algorithme  

Le problème de cet algorithme est de ne pas trouver un Node avec une seule possibilité dans ce cas mon programme trouve un Node avec deux possibilités et créée un processus fils, donc le père et le fils essayent de résoudre le sudoku avec un chiffre diffèrent dans ce Node. Le processus avec le chiffre erroné se termine quand il trouve un Node ou il n'y a pas de possibilité. 

## Spécification 

Pour implémenter les Nodes j'ai créé un TAD Node et sudoku 

**Implémentation des Nodes:** 

```c 

struct s_node{ 
    int id; 
    int t[9]; 
    int sizeT; 
    int root; 
    node node[20]; 
}*node; 

``` 

- La `id` est l'identifiant du Node entre `1` et `81` 

- `t[9]` sont les possibilités `1` a `9` et remis a `-1` quand ce numéro n'est pas une possibilité 

- `sizeT` est le nombre de possibilité par Node 

- `root` est le chiffre qui correspond au chiffre du Node, `0` si le Node n'a pas encore de numéro 

- `node[20]` est un tableau de Nodes associe au Node 


**Implementation du sudoku : ** 

```c 

struct s_sudoku { 
    int solved; 
    node tab[81]; 
}; 

``` 

- `solved` est un nombre qui détermine combien de Node ont un nombre diffèrent de `0`, `solved` vaut `81` quand le sudoku est résolu  

- `tab[81]` est un tableau de tous les Nodes du sudoku 


# Auteur du projet 

- **Javier Pelegrin Garcia** - développeur - Documentation 

 
## Remercîment  

Merci à **Oriol Camps Perez** pour l'idée et l'aide de la conception de la partie des processus fils. 