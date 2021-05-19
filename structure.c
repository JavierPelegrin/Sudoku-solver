#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "structure.h"


struct s_node{
    int id;
    int t[9];
    int sizeT;
    int root;
    node node[20];
};

struct s_sudoku {
    int solved;
    node tab[81];
};


//--- structure des nodes ---

node createNode(int v, int id){
    node n = malloc(sizeof(struct s_node));
    n->id = id;
    n->sizeT = 1;
    if (v == 0){
        for(int i = 0; i < 9; i++){
            n->t[i] = i+1;
        }
        n->sizeT = 9;
    }
    n->root = v;
    return n;
}

node getNode(node i[], int id){
    return i[id];
}

void createLinks(sudoku *s){

    int matrix[9][9];
    int k = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            matrix[i][j] = k;
            k++;
        }
    }

    int multiplicator = 0;
    k = 0;
    int i;
    int cur;
    for(int p = 0; p < 81; p++){
        if (multiplicator+9 == p){
            multiplicator +=9; 
        }
        i = 0;
        cur = 0;
        while (i < 17){
            if (i < 8){ //horizontal
                if ((*s)->tab[p]->id != (*s)->tab[((cur)%9)+multiplicator]->id ){
                    (*s)->tab[p]->node[i] = (*s)->tab[((cur)%9)+multiplicator];
                    i++;
                }
                k = p;
            }else if(i < 16){ //vertical
                if ((*s)->tab[p]->id != (*s)->tab[k]->id){
                    (*s)->tab[p]->node[i] = (*s)->tab[(k)];
                    i++;
                }
                k = (k+9)%81;
            } else { // cuadrado
                //como creamos los enlaces del nodo a el cuadrado ?
                int c = (multiplicator / 9);
                int l = (p % 9);
                if(c%3 == 0){
                    if (l % 3 == 0){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c+1][l+1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c+1][l+2]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+2][l+1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+2][l+2]];
                    }else if(l % 3 == 1){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c+1][l-1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c+1][l+1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+2][l-1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+2][l+1]];
                    }else if(l% 3 == 2){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c+1][l-2]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c+1][l-1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+2][l-2]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+2][l-1]];
                    }
                }else if (c%3 == 1) {
                    if (l % 3 == 0){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-1][l+1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-1][l+2]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+1][l+1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+1][l+2]];
                    }else if(l% 3 == 1){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-1][l-1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-1][l+1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+1][l-1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+1][l+1]];
                    }else if(l % 3 == 2){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-1][l-2]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-1][l-1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c+1][l-2]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c+1][l-1]];
                    }
                }else if (c%3 == 2) {
                    if (l % 3 == 0){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-2][l+1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-2][l+2]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c-1][l+1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c-1][l+2]];
                    }else if(l % 3 == 1){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-2][l-1]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-2][l+1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c-1][l-1]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c-1][l+1]];
                    }else if(l % 3 == 2){
                        (*s)->tab[p]->node[i]   = (*s)->tab[matrix[c-2][l-2]];
                        (*s)->tab[p]->node[i+1] = (*s)->tab[matrix[c-2][l-1]];
                        (*s)->tab[p]->node[i+2] = (*s)->tab[matrix[c-1][l-2]];
                        (*s)->tab[p]->node[i+3] = (*s)->tab[matrix[c-1][l-1]];
                    }
                }
                
                i++;
            }
            cur++;
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
    if (v != '0'){
        (*s)->solved++;
    }
    (*s)->tab[id] = createNode(atoi(&v), id);
}

bool isSolved(const sudoku s){
    return s->solved >= 81;
}

void printNode(const sudoku s){
    for(int i = 0; i < 81; i++){
        if (i%9 == 0){
            printf("\n");
        }
        printf("%d ", s->tab[i]->root);
    }
}


sudoku solveSudoku(sudoku *s){
    int i = 0;
    int contador = 0;
    int backtraquing = 0;
    int n,m;
    struct s_sudoku cp_s;
    printf("\n\nresolviendo ...\n");
    while(isSolved(*s) != true){
        if(((*s)->tab[i])->root  == 0){
            // printf("este %d, %d \n",(*s)->tab[i]->id,(*s)->tab[i]->sizeT);
            for(int j = 0; j < 9; j++){
                for(int k = 0; k < 20; k++){ // cambiar a 20
                    // if(i == 44){ // Listar imformacion sobre un nodo
                    //     printf("root : %d \n enlaces: ",(*s)->tab[i]->root);
                    //     for(int j = 0; j < 20; j++){
                    //         printf("%d ",(*s)->tab[i]->node[j]->root);
                    //     }
                    //     printf("\ntab:");
                    //     for(int j = 0; j < 9; j++){
                    //         printf("%d ",(*s)->tab[i]->t[j]);
                    //     }
                    //     printf("\n");
                    // }
                    if ((*s)->tab[i]->t[j] == (*s)->tab[i]->node[k]->root){
                        (*s)->tab[i]->t[j] = -1;
                        (*s)->tab[i]->sizeT-=1;
                        if ((*s)->tab[i]->sizeT == 1) {
                            for(int h = 0; h < 9; h++){
                                if((*s)->tab[i]->t[h] != -1){
                                    (*s)->tab[i]->root = (*s)->tab[i]->t[h];
                                }
                            }
                            (*s)->solved++;
                            contador = -1;
                            printf("node : %d, num: %d\n",(*s)->tab[i]->id , (*s)->tab[i]->root); // nodo resuelto
                        }
                        break;
                    }
                }
            }
        }
        i = (i+1)%81;
        if (i == 80){
            contador++;
        }

        if(contador == 10 && backtraquing == 0){
            cp_s = (**s);
            n = 0;
            m = 2;
            while((*s)->tab[n]->sizeT == m){
                n++;
                if (n >= 81){
                    m++;
                    n = 0;
                }
            }
            for(int h = 0; h < 9; h++){
                if((*s)->tab[n]->t[h] != -1){
                    (*s)->tab[n]->root = (*s)->tab[n]->t[h];
                }
            }
            printf("sizeT :%d, node : %d, num: %d\n", (*s)->tab[n]->sizeT, (*s)->tab[n]->id, (*s)->tab[n]->root);
            (*s)->solved++;
            backtraquing = (backtraquing + 1) % m; contador = -1;
        }

        if (contador == 10 && backtraquing == 1){
            int cp;
            printf("backtraking ...\n");
            for(int h = 0; h < 9; h++){
                if((*s)->tab[n]->t[h] != -1 && (*s)->tab[n]->t[h] != (*s)->tab[n]->root){
                    cp = (*s)->tab[n]->t[h];
                }
            }
            (**s) = cp_s;
            (*s)->tab[n]->root = cp;
            backtraquing = (backtraquing + 1) % m; contador = -1;
        }

        if (contador == 10 && backtraquing == 2){
            int cp;
            printf("backtraking ...\n");
            for(int h = 0; h < 9; h++){
                if((*s)->tab[n]->t[h] != -1 && (*s)->tab[n]->t[h] != (*s)->tab[n]->root){
                    cp = (*s)->tab[n]->t[h];
                }
            }
            (**s) = cp_s;
            (*s)->tab[i]->root = cp;
            backtraquing = (backtraquing + 1) % m; contador = -1;
        }
        
        // if(i == 67){
        //     printf("links ");
        //     for(int j = 0; j < 20; j++){
        //         printf("%d ",(*s)->tab[i]->node[j]->root);
        //     }
        //     break;
        // }
    }
    return *s;
}




void testLinks(const sudoku s){
    printf("\n");
    for (int j = 0; j < 81; j++){
        printf("links de nodo %d : ",j+1);
        for(int i = 0; i < 20; i++){
            printf("%d ",s->tab[j]->node[i]->id+1);
        }
        printf("\n");
    }

    // printf("links de nodo 21 : ");
    // for(int i = 0; i < 20; i++){
    //     printf("%d ",s->tab[20]->node[i]->id+1);
    // }
    // printf("\n");

    // printf("links de nodo 41 : ");
    // for(int i = 0; i < 20; i++){
    //     printf("%d ",s->tab[40]->node[i]->id+1);
    // }
    // printf("\n");
}

char itoc(int numero){
    return numero + '0';
}

void exportSudoku(const sudoku s){
    char *c = malloc(sizeof(char));
    int f = open("./gridSolved.txt", O_CREAT|O_WRONLY|O_TRUNC);
    sprintf(c,"%d",s->tab[0]->root);
    write(f, c, 1);
    write(f," ",1);
    for(int i = 1; i < 81; i++){
        if (i%9 == 0){
            write(f,"\n",1);
        }
        sprintf(c,"%d",s->tab[i]->root);
        write(f, c, 1);
        write(f," ",1);
    }
    free(c);
    close(f);
}