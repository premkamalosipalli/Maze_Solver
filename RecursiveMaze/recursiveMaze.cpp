#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
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

    //Reading the file using fopen.
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

            //Stroring the start and end vertex of the maze.
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

//Creating a maze to check whether we have visited the wall or not.
void allocateVisited()
{
	mazeVisited = new int*[ROW];
	int i;
	for (i = 0; i < ROW; ++i){
		mazeVisited[i] = new int[COL];
	}
}

//Checking the path by visiting every wall and find the path.
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

//Generate the maze from the input taken.
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

//Adding path with (.) from start to end.
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

//Fucntion used to find the path for the given Maze.
int rMazeSearch(int row, int col)
{
	int* current = &mazeVisited[row][col];

	if (*current == goal) {
		return 1;
	}

	if (*current == empty) {
		*current = wall;

        // Mark this position as explored, then go up one position
		if (rMazeSearch(row - 1, col)){
			*current = crumb;
			return 1;		
		} 
        // Mark this position as explored, then go right one position
		if (rMazeSearch(row, col + 1)){
			*current = crumb;
			return 1;
		}
        // Mark this position as explored, then go down one position
		if (rMazeSearch(row + 1, col)){
			*current = crumb;
			return 1;
		} 
        // Mark this position as explored, then go left one position
		if (rMazeSearch(row, col - 1)){
			*current = crumb;
			return 1;
		}
	}

	return 0;
}

int main()
{
    //Creating Clock variables to calculate the time taken to generate maze.
    clock_t start, stop;
    double totalTime;

    //Reading input from a file.
    char *intputMaze = (char *)"maze.txt";

    //Creating a maze from the input given.
    getInputMaze(intputMaze);
    initializeVisited();

    //Generating the maze and taking this as inital maze.
    std::cout << "Initial Maze: " << std::endl;
    generateMaze();

    //Start clock begin at this time.
    start = clock();
    if (!rMazeSearch(mazeEntrance.x, mazeEntrance.y)) {
    	printf("Dint find a path form source to destination");
    } else {

        //Adding path from the start to destination for the maze.
    	addCrumbs();
        std::cout << "\nMaze Traversal: " << std::endl;
    	generateMaze();
    }
    //Stop clock end at the time.
    stop = clock();

    //Calculating the time difference from start to end of maze search.
    totalTime = (stop - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Time taken to Recursive Maze:  " << std::fixed << std::setprecision(2) << totalTime * 1000 << " ms " << std::endl;
    return 0;
}
