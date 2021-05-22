#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>


#include "structure.h"

/*
https://www.sudoku-online.org/

gridUltraHard = #2231

gridHard = #26695

gridMedium = #25085

*/
int main(){

    char pwd[64];
    char c;
    printf("File : ");
    scanf("%s",pwd);
    // strcpy(pwd,"./gridUltraHard.txt");
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
    createLinks(&s);
    printNode(s);
    // testLinks(s);
    printf("\n\nSolving ....\n");
    s = solveSudoku(&s);
    printNode(s);
    printf("\n");

    exportSudoku(s);
    removeSudoku(s);
    close(grid);
    return 0;
}