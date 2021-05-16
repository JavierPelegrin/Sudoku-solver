#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <stdbool.h>



typedef struct s_node *node;
typedef struct s_sudoku *sudoku;


//--- nodes --- 

node createNode(char v, int id);

node getNode(node i[], int id);

void createLinks(sudoku *sudoku);


//--- Sudoku ---

sudoku createSudoku();

void addNode(sudoku *s, char v, int id);

bool isSolved(const sudoku s);

void printNode(const sudoku s);

void testLinks(const sudoku s);

#endif