#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structure.h"


struct s_node{
    int id;
    int t[9];
    char root;
    node node[21];
};

struct s_sudoku {
    int solved;
    node tab[81];
};


//--- structure des nodes ---

node createNode(char v,int id){
    node n = malloc(sizeof(struct s_node));
    n->id = id;
    if (v != '0'){
        for(int i = 0; i < 9; i++){
            n->t[i] = i+1;
        }
    }
    n->root = v;
    return n;
}

node getNode(node i[], int id){
    return i[id];
}

void createlinks(sudoku *s){
    int multiplicator = 0;
    int k;
    for(int p = 0; p < 81; p++){
        if (multiplicator+9 == p){
            multiplicator +=9; 
        }
        for(int i = 0; i < 20; i++){
            if (i < 9){
                (*s)->tab[p]->node[i] =  (*s)->tab[((i)%9)+multiplicator];
                k = p;
            }else if(i < 17){
                (*s)->tab[p]->node[i] = (*s)->tab[((k)%81)];
                k = (k+9)%81;
            }else {
                //como creamos los enlaces del nodo a el cuadrado ?
                (*s)->tab[p]->node[i] = NULL;
            }
        }
    }
}


//--- Sudoku ---

sudoku createSudoku(){
    sudoku s = malloc(sizeof(struct s_sudoku));
    s->solved = 0;
    return s;
}

void addNode(sudoku *s, char v, int id){
    (*s)->tab[id] = createNode(v, id);
}

bool isSolved(const sudoku s){
    return s->solved == 81;
}

void printNode(const sudoku s){
    for(int i = 0; i < 81; i++){
        printf("%c ", s->tab[i]->root);
    }
}

void testLinks(const sudoku s){
    
}