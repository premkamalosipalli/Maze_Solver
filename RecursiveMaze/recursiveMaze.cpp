#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip> // std:setprecision
#include <ctime>
#include "Position.h"


int **mazeVisited;
int ROW;
int COL;
char** recursiveMaze;

Position mazeEntrance, mazeExit;

enum terrain
{
    empty,
    wall,
    goal,
    crumb
};

void createMaze()
{
    recursiveMaze = new char*[ROW];
	
	int i;
	for (i = 0; i < ROW; ++i){
		recursiveMaze[i] = new char[COL];
	}
}

void getInputMaze(char *fileName)
{
    char c;
    char rows[3] = {'\0'};
    char cols[3] = {'\0'};
    int row = 0;
    int col = 0;
    int switched = 0;

    FILE *inputMazeFile = fopen(fileName, "r");

    if (inputMazeFile)
    {
        while ((c = getc(inputMazeFile)) != EOF)
        {
            if (c == '\n')
            {
                break;
            }
            else if (c == ',')
            {
                switched = 1;
            }
            else if (!switched)
            {
                rows[row] = c;
                row++;
            }
            else
            {
                cols[col] = c;
                col++;
            }
        }
    }
    else
    {
        std::cout << "No such file!" << std::endl;
        return;
    }

    ROW = atoi(rows);
    COL = atoi(cols);

    createMaze();

    int i, j;

    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {

            if ((c = getc(inputMazeFile)) == '\n')
            {
                c = getc(inputMazeFile);
            }

            recursiveMaze[i][j] = c;

            if (c == 's')
            {
                mazeEntrance.x = i;
                mazeEntrance.y = j;
            }else if (c == 'g'){
                mazeExit.x = i;
                mazeExit.y = j;
            }
        }
    }

    fclose(inputMazeFile);
}

void allocateVisited()
{
	mazeVisited = new int*[ROW];
	int i;
	for (i = 0; i < ROW; ++i){
		mazeVisited[i] = new int[COL];
	}
}

void initializeVisited()
{
	allocateVisited();

	int i, j;
	for (i = 0; i < ROW; ++i) {
		for (j = 0; j < COL; ++j) {
			if (recursiveMaze[i][j] == '+') {
				mazeVisited[i][j] = wall;
			} else if (recursiveMaze[i][j] == 'g') {
				mazeVisited[i][j] = goal;
			} else {
				mazeVisited[i][j] = empty;
			}
		}
	}
}

void generateMaze()
{
    int i, j;
    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            std::cout << recursiveMaze[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void addCrumbs()
{
	int i, j;
	for (i = 0; i < ROW; ++i) {
		for (j = 0; j < COL; ++j) {
			if (recursiveMaze[i][j] != 's'){
                if(mazeVisited[i][j] == crumb){
                    recursiveMaze[i][j] = '.';
                }
            } 
		}
	}
}

int dfs(int row, int col)
{
	int* current = &mazeVisited[row][col];

	if (*current == goal) {
		return 1;
	}

	if (*current == empty) {
		*current = wall;

		if (dfs(row + 1, col)){
			*current = crumb;
			return 1;
		} 
		if (dfs(row, col - 1)){
			*current = crumb;
			return 1;
		} 
		if (dfs(row - 1, col)){
			*current = crumb;
			return 1;		
		} 
		if (dfs(row, col + 1)){
			*current = crumb;
			return 1;
		}
	}

	return 0;
}

int main()
{
    clock_t start, stop;
    double totalTime;

    char *intputMaze = (char *)"maze.txt";
    getInputMaze(intputMaze);
    initializeVisited();

    std::cout << "Initial Maze: " << std::endl;
    generateMaze();

    start = clock();
    if (!dfs(mazeEntrance.x, mazeEntrance.y)) {
    	printf("Dint find a path form source to destination");
    } else {
    	addCrumbs();
        std::cout << "\nMaze Traversal: " << std::endl;
    	generateMaze();
    }
    stop = clock();
    totalTime = (stop - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Time taken to Recursive Maze:  " << std::fixed << std::setprecision(2) << totalTime * 1000 << " ms " << std::endl;
    return 0;
}