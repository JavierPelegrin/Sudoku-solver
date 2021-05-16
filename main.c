#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#include "structure.h"

int main(){

    char pwd[64];
    char c;
    // scanf("%s",pwd);
    strcpy(pwd,"./grid.txt");
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
    createSudoku(&s);
    printNode(s);
    close(grid);
    return 0;
}