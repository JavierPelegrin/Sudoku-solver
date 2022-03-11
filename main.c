
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <omp.h>

#include "structure.h"

/*
https://www.sudoku-online.org/

girdUltraHard2 = #589

gridUltraHard = #2231

gridHard = #26695

gridMedium = #25085

*/
int main(){

    char pwd[64];
    char c;
    double start, stop;
    printf("File : \n");
    //scanf("%s",pwd);
    strcpy(pwd,"./grid/gridUltraHard2.txt");
    int grid = open(pwd, O_RDONLY);
    if(grid == -1){
        perror("File");
        exit(EXIT_FAILURE);
    }
    sudoku s = createSudoku();
    int i  = 0;
    while (i < 81){
        read(grid, &c, 1);
        if (c != ' ' && c != '\n' && c != '\0'){
            addNode(&s, c, i);
            i++;
        }
    }
    start = omp_get_wtime();
    createLinks(&s);
    stop = omp_get_wtime();
    printf("Creation des links : %f\n",stop-start);
    printNode(s);
    // testLinks(s);
    printf("\n\nSolving ....\n");
    start = omp_get_wtime();
    s = solveSudoku(&s);
    
    wait(NULL);
    stop = omp_get_wtime();
    printf("Résoudre le sudoku : %f",stop-start);
    printNode(s);
    printf("\n");

    exportSudoku(s);
    removeSudoku(s);
    close(grid);
    return 0;
}