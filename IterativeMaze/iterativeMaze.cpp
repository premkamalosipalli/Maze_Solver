#include <iostream>
#include <unistd.h>
#include <iomanip> 
#include <ctime>
#include "Stack.h"
#include "Position.h"

using namespace std;

//Storing the charcter constants to generate maze.
const char ENTRANCE = 's';
const char EXIT = 'g';
const char WALL = '+';
const char ROAD = ' ';
const char EXPLORED = 'e';

const int ROW = 12;
const int COLUMN = 21;

int finalSize;

Position mazeEntrance, currentPosition;
Position *rightPath;

char mazeCopy[ROW][COLUMN];
char mazeDisplay[ROW][COLUMN];

Stack path(ROW *COLUMN);

//Taking input as character matrix.
char maze[ROW][COLUMN] =
    {
"++++++++++++++++++++",
"+                  +",
"+  s+ ++++ + +++++ +",
"+ + +++ ++ + ++ ++ +",
"+ +   +    + ++    +",
"+ +++ ++++++ +++++++",
"+   +     ++ + +   +",
"+ +++++++ ++ + + +g+",
"+ +       ++ +   + +",
"+ ++++++++++ +++++ +",
"+                  +",
"++++++++++++++++++++",
};

class MazeSearch
{
public:
    void ImazeSearch();
    void printPath();
    void printMaze();
    void enterMaze();
    void stepPath();
    void copyMaze();
};

int main()
{
    MazeSearch mazeGeneration;

    //Creating Clock variables to calculate the time taken to generate maze.
    clock_t start, stop;
    double totalTime;

    //Creating a maze from the input given.
    mazeGeneration.enterMaze();

    mazeGeneration.copyMaze();

    //Generating the maze and taking this as inital maze.
    cout << "Initial Maze: " << endl;
    mazeGeneration.printMaze();

    //Start clock begin at this time.
    start = clock();
    mazeGeneration.ImazeSearch();

    //Adding path from the start to destination for the maze.
    mazeGeneration.printPath();

    cout << "\nMaze Traversal: " << endl;
    mazeGeneration.printMaze();

    //Stop clock end at the time.
    stop = clock();

    //Calculating the time difference from start to end of maze search.
    totalTime = (stop - start) / (double)CLOCKS_PER_SEC;
    cout << "Time taken to Iterative Maze:  " << fixed << setprecision(2) << totalTime * 1000 << " ms " << endl;
    return 0;
}

//This function is used to traverse the maze.
void MazeSearch::ImazeSearch()
{
    currentPosition = mazeEntrance;

    while (true)
    {
        if (mazeCopy[currentPosition.x][currentPosition.y] == EXIT)
            break;

        // Get the maze element at each direction of the current position
        char positionUp = mazeCopy[currentPosition.x - 1][currentPosition.y];
        char positionRight = mazeCopy[currentPosition.x][currentPosition.y + 1];
        char positionDown = mazeCopy[currentPosition.x + 1][currentPosition.y];
        char positionLeft = mazeCopy[currentPosition.x][currentPosition.y - 1];

        // Mark this position as explored, then go up one position
        if ((positionUp == ROAD || positionUp == EXIT) && currentPosition.x - 1 >= 0)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.x--;
        }

        // Mark this position as explored, then go right one position
        else if ((positionRight == ROAD || positionRight == EXIT) && currentPosition.y + 1 < COLUMN)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.y++;
        }

        // Mark this position as explored, then go down one position
        else if ((positionDown == ROAD || positionDown == EXIT) && currentPosition.x + 1 < ROW)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.x++;
        }

        // Mark this position as explored, then go left one position
        else if ((positionLeft == ROAD || positionLeft == EXIT) && currentPosition.y >= 0)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.y--;
        }

        // Mark this position as a WALL, then go back one position
        else
        {
            mazeCopy[currentPosition.x][currentPosition.y] = WALL;
            currentPosition = path.Pop();
        }
    }

    finalSize = path.GetLength();

    rightPath = new Position[ROW * COLUMN];

    for (int i = finalSize - 1; i >= 0; i--)
    {
        rightPath[i] = path.Pop();
    }
}

//This method is to crate copy for the input maze.
void MazeSearch::copyMaze()
{

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            mazeCopy[i][j] = maze[i][j];
            mazeDisplay[i][j] = maze[i][j];
        }
    }
}

//Method used to enter the maze with start location.
void MazeSearch::enterMaze()
{
    for (int a = 0; a < ROW; a++)
    {
        for (int b = 0; b < COLUMN; b++)
        {
            if (maze[a][b] == 's')
            {
                mazeEntrance.x = a;
                mazeEntrance.y = b;
            }
            else
            {
                continue;
            }
        }
    }
}

//Method used to print the maze.
void MazeSearch::printMaze()
{
    for (int a = 0; a < ROW; a++)
    {
        for (int b = 0; b < COLUMN; b++)
        {
            cout << maze[a][b];
        }
        cout << endl;
    }
}

//Method used to print path with (.) from start to end.
void MazeSearch::printPath()
{
    for (int i = 0; i < finalSize; i++)
    {
        Position temp = rightPath[i];
        for (int a = 0; a < ROW; a++)
        {
            for (int b = 0; b < COLUMN; b++)
            {
                if (maze[temp.x][temp.y] == ENTRANCE || maze[temp.x][temp.y] == EXIT)
                {
                    continue;
                }
                else
                {
                    maze[temp.x][temp.y] = '.';
                }
            }
        }
    }
}
