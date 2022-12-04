#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include "IterativeStack.h"
#include "IterativePosition.h"

using namespace std;

//Storing the charcter constants to generate maze.
const char PACMAN = 's';
const char GHOST = 'g';
const char BLOCK = '+';
const char PATH = ' ';
const char VISITED = 'e';

const int firstIndex = 12;
const int secondIndex = 21;

int finalSize;

Position mazeEntrance, present;
Position *correctPath;

char copiedMaze[firstIndex][secondIndex];

Stack path(firstIndex *secondIndex);

//Taking input as character matrix.
char maze[firstIndex][secondIndex] =
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
    present = mazeEntrance;

    while (true)
    {
        if (copiedMaze[present.first][present.second] == GHOST)
            break;

        // Obtain the maze element at the below positions.
        char top = copiedMaze[present.first - 1][present.second];
        char right = copiedMaze[present.first][present.second + 1];
        char down = copiedMaze[present.first + 1][present.second];
        char left = copiedMaze[present.first][present.second - 1];

        // note the presetn postion as visited and then move to one postion top.
        if ((top == PATH || top == GHOST) && present.first - 1 >= 0)
        {
            path.Push(present);
            copiedMaze[present.first][present.second] = VISITED;
            present.first--;
        }

        // note the presetn postion as visited and then move to one postion right.
        else if ((right == PATH || right == GHOST) && present.second + 1 < secondIndex)
        {
            path.Push(present);
            copiedMaze[present.first][present.second] = VISITED;
            present.second++;
        }

        // note the presetn postion as visited and then move to one postion down.
        else if ((down == PATH || down == GHOST) && present.first + 1 < firstIndex)
        {
            path.Push(present);
            copiedMaze[present.first][present.second] = VISITED;
            present.first++;
        }

        // note the presetn postion as visited and then move to one postion left.
        else if ((left == PATH || left == GHOST) && present.second >= 0)
        {
            path.Push(present);
            copiedMaze[present.first][present.second] = VISITED;
            present.second--;
        }

        // If there is way to move further then backtrack.
        else
        {
            copiedMaze[present.first][present.second] = BLOCK;
            present = path.Pop();
        }
    }

    finalSize = path.GetLength();

    correctPath = new Position[firstIndex * secondIndex];

    for (int i = finalSize - 1; i >= 0; i--)
    {
        correctPath[i] = path.Pop();
    }
}

//This method is to crate copy for the input maze.
void MazeSearch::copyMaze()
{

    for (int i = 0; i < firstIndex; i++)
    {
        for (int j = 0; j < secondIndex; j++)
        {
            copiedMaze[i][j] = maze[i][j];
        }
    }
}

//Method used to enter the maze with start location.
void MazeSearch::enterMaze()
{
    for (int a = 0; a < firstIndex; a++)
    {
        for (int b = 0; b < secondIndex; b++)
        {
            if (maze[a][b] == 's')
            {
                mazeEntrance.first = a;
                mazeEntrance.second = b;
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
    for (int a = 0; a < firstIndex; a++)
    {
        for (int b = 0; b < secondIndex; b++)
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
        Position temp = correctPath[i];
        for (int a = 0; a < firstIndex; a++)
        {
            for (int b = 0; b < secondIndex; b++)
            {
                if (maze[temp.first][temp.second] == PACMAN || maze[temp.first][temp.second] == GHOST)
                {
                    continue;
                }
                else
                {
                    maze[temp.first][temp.second] = '.';
                }
            }
        }
    }
}
