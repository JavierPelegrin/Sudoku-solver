#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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


// --- Debug part ---

void printInfo(sudoku s, int i){
    printf("info:\n");
    printf("\testado del sudoku: %d\n",s->solved);
    printf("\tnode id: %d\n",s->tab[i]->id);
    printf("\tsizeT: %d\n", s->tab[i]->sizeT);
    printf("\troot: %d\n",s->tab[i]->root);
    for(int k = 0; k < 20; k++)
        printf("\tEnlaces: %d\n",s->tab[i]->node[k]->root);
    for(int k = 0; k < 9; k++)
        printf("\ttab: %d\n",s->tab[i]->t[k]);
}

void testLinks(const sudoku s){
    printf("\n");
    for (int j = 0; j < 81; j++){
        printf("links de nodo %d : ",j);
        for(int i = 0; i < 20; i++){
            printf("%d ",s->tab[j]->node[i]->id);
        }
        printf("\n");
    }
}

//--- structure of nodes ---

node createNode(int v, int id){
    node n = malloc(sizeof(struct s_node));
    n->id = id;
    n->sizeT = 9;
    if (v == 0){
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
            } else { // quadrant
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

void removeNode(node n){
    free(n);
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
    while(isSolved(*s) != true){
        if(((*s)->tab[i])->root == 0){
            for(int j = 0; j < 9; j++){
                for(int k = 0; k < 20; k++){
                    if ((*s)->tab[i]->t[j] == (*s)->tab[i]->node[k]->root){
                        (*s)->tab[i]->t[j] = -1;
                        (*s)->tab[i]->sizeT-=1;
                    }
                }
            }
        }


        if ((*s)->tab[i]->root == 0 && (*s)->tab[i]->sizeT == 1) {
            for(int j = 0; j < 9; j++){
                //printf("tab[%d]->t[%d]:  %d\n",i,j,(*s)->tab[i]->t[j] ); // nodo resuelto
                if((*s)->tab[i]->t[j] != -1){
                    (*s)->tab[i]->root = (*s)->tab[i]->t[j];
                }
            }
            (*s)->solved++;
            contador = -1;
            // printf("node : %d, num: %d\n",(*s)->tab[i]->id , (*s)->tab[i]->root); // nodo resuelto
        }
        else if ((*s)->tab[i]->sizeT == 0){
            // printf("pid = %d\n",getpid());
            exit(0);
        }
        i = (i+1)%81;
        if (i == 80){
            contador++;
        }

        if(contador == 20 ){
            int m = 2;
            int i = 0;
            while((*s)->tab[i]->sizeT != m){
                i = (i+1)%81;
                if(i == 80){
                    m++;
                }
            }
            int t[m];
            int j = 0;
            int a = 0;
            while(j < 9){
                if ((*s)->tab[i]->t[j] != -1){
                    t[a] = (*s)->tab[i]->t[j];
                    (*s)->tab[i]->t[j] = -1;
                    a++;
                }
                j = (j + 1);
            }

            pid_t p = fork();
            if (p == -1){
                perror("fork()");
                exit(1);
            }else if (p == 0){
                // padre simpre encuentra el ultimo


                // printf("padre : j = %d, id:%d, num %d\n",j,i,(*s)->tab[i]->t[j]);
                (*s)->tab[i]->root = t[0];
                (*s)->solved++;
                (*s)->tab[i]->sizeT = 1;
                contador = -1;
                //return *s;
                return solveSudoku(s);
            }else{
                // hijo
                if(m == 3){
                    pid_t p2 = fork();
                    if(p2 == -1){
                        perror("fork()");
                        exit(1);
                    }else if (p2 == 0){
                        // padre
                        (*s)->tab[i]->root = t[2];
                        (*s)->tab[i]->sizeT = 1;
                        (*s)->solved++;
                        contador = -1;
                        //return *s;
                        return solveSudoku(s);
                    }
                }

                // printf("hijo : j = %d, id:%d, num %d\n",j,i,(*s)->tab[i]->t[j]);
                
                // printInfo(*s, i);
                (*s)->tab[i]->root = t[1];
                (*s)->solved++;
                (*s)->tab[i]->sizeT = 1;
                contador = -1;
                //return *s;
                return solveSudoku(s);
            }
        }
    }
    return *s;
}


void removeSudoku(sudoku s){
    for(int i = 0; i < 81; i++){
        removeNode(s->tab[i]);
    }
    free(s);
}


//--- Utilities ---

char itoc(int numero){
    return numero + '0';
}

void exportSudoku(const sudoku s){
    char *c = malloc(sizeof(char));
    int f = open("./gridSolved.txt", O_CREAT|O_WRONLY|O_TRUNC);
    sprintf(c,"%d",s->tab[0]->root);
    write(f, c, 1);
    write(f," ",1);
    for(int i = 1; i < 80; i++){
        if (i%9 == 0){
            lseek(f, -1, SEEK_CUR);
            write(f,"\n",1);
        }
        sprintf(c,"%d",s->tab[i]->root);
        write(f, c, 1);
        write(f," ",1);
    }
    sprintf(c,"%d",s->tab[80]->root);
    write(f, c, 1);
    free(c);
    close(f);
}