// +---------------------------------------------------------------------------+
// |                                                                           |
// | CATSOFT STUDIOS: Marti-Joan Nogue Coll (2011)                             |
// |                                                                           |
// | http://catsoft-studios.com                                                |
// |                                                                           |
// | This code was created for demonstration purposes only. We do not take     |
// | any responsabilities of the injueries that may cause.                     |
// |                                                                           |
// | if you want to change the position of the objects (player, target or      |
// | obstacles) do it within the code. There is a special comment marked as    |
// | ** MODIFICABLE ** from where you can tweak variables to view different    |
// | results.                                                                  |
// |                                                                           |
// | RECOMENDATIONS:                                                           |
// |                                                                           |
// | The code provied does not take into account strange variable values (like |
// | placing the player onto an obstacle or out of the world space grid.       |
// | If so, you will be alerted with segmentation faults or wierd results      |
// +---------------------------------------------------------------------------+

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

// STRUCTURES: -----------------------------------------------------------------

struct Position
{
    int x;
    int y;
};

// OTHER FUNCTIONS: ------------------------------------------------------------

void displayGrid(vector< vector<int> >& matrix, Position t, Position p)
{
    int n = matrix.size();
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == t.x and j == t.y) cout << "T ";
            else if (i == p.x and j == p.y) cout << "P ";
            else if (matrix[i][j] == -1) cout << "X ";
            else if (matrix[i][j] == -2) cout << "· ";
            else cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
}

void fillGrid(vector< vector<int> >& matrix, Position target)
{
    int n = matrix.size();
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] != -1)
            {
                matrix[i][j] = max(abs(i - target.x), abs(j - target.y));
            }
        }
    }
}

void getPath(vector< vector<int> >& matrix, Position target, Position player)
{
    int n = matrix.size();
    
    bool pathFound = false;
    
    int X[4] = { 0,  0,  1, -1 };
    int Y[4] = { 1, -1,  0,  0 };
    
    while (!pathFound)
    {
        Position nextDir;
        nextDir.x = 0;
        nextDir.y = 0;
        
        int minValue = 9999;
        
        for (int i = 0; i < 4; ++i)
        {
            int u = player.x + X[i];
            int v = player.y + Y[i];
            
            if (u == target.x and v == target.y)
            {
                // target found:
                return;
            }
            else if (u >= 0 and u < n and v >= 0 and v < n)
            {
                // if we are inside the map:
                if (matrix[u][v] > 0 and matrix[u][v] < minValue)
                {
                    // candidate to be next position:
                    minValue = matrix[u][v];
                    nextDir.x = u;
                    nextDir.y = v;
                }
            }
        }
        
        matrix[nextDir.x][nextDir.y] = -2;
        
        player.x = nextDir.x;
        player.y = nextDir.y;
    }
}

// MAIN PROGRAM: ---------------------------------------------------------------

int main()
{
    // N: size of the matrix NxN:
    int N = 10;
    
    // create world space grid:
    vector< vector<int> > matrix(N, vector<int>(N, 0));
    
    // *************************************************************************
    // ** MODIFICABLE **********************************************************
    
    Position target;
    Position player;
    
    target.x = 2; /* CHANGE TARGET INITIAL POSITION: Column */
    target.y = 6; /* CHANGE TARGET INITIAL POSITION: Row    */
    
    player.x = 8; /* CHANGE PLAYER INITIAL POSITION: Column */
    player.y = 2; /* CHANGE PLAYER INITIAL POSITION: Row    */
    
    matrix[4][2] = -1; /* OBSTACLE POSITION. Value of -1 means obstacle */
    matrix[4][3] = -1; /* OBSTACLE POSITION. Value of -1 means obstacle */
    matrix[4][4] = -1; /* OBSTACLE POSITION. Value of -1 means obstacle */
    matrix[4][5] = -1; /* OBSTACLE POSITION. Value of -1 means obstacle */
    matrix[4][6] = -1; /* OBSTACLE POSITION. Value of -1 means obstacle */
    
    // ** END MODIFICABLE ******************************************************
    // *************************************************************************
        
    // display world space grid:
    cout << endl << "0: No obstacle" << endl << "X: Obstace" << endl << endl;
    displayGrid(matrix, target, player);
    
    // fill world space grid:
    fillGrid(matrix, target);
    
    // display world space grid:
    cout << endl << "World map with waypoints:" << endl << endl;
    displayGrid(matrix, target, player);
    
    // find path in world space gid:
    getPath(matrix, target, player);
    
    // display world space grid:
    cout << endl << "Final path is:" << endl << endl;
    displayGrid(matrix, target, player);
}
