#include <iostream>
#include <chrono>
#include <thread>
#include <list>
#include <cmath>

using namespace std;

#define INF 999

const int ROWS = 20;
const int COLS = 40;

int srcx, srcy, src, dstx, dsty, dst;

const int V = ROWS * COLS;
int empty_grid[ROWS][COLS];
int adj_posX[4] = {-1, 0, 1, 0}; // x-1, x, x+1, x
int adj_posY[4] = {0, 1, 0, -1}; // y, y+1, y, y-1
int cost[V][V];
int dist[V];
bool visited[V];
int par[V];
list<int> path;

void input()
{
    cout << "Enter X position for point A (1 - " << ROWS << ") : ";
    cin >> srcx;
    srcx -= 1;
    while (srcx < 0 || srcx >= ROWS)
    {
        cout << "Please choose a number between [1 - " << ROWS << "] : ";
        cin >> srcx;
        srcx -= 1;
    }

    cout << "Enter Y position for point A (1 - " << COLS << ") : ";
    cin >> srcy;
    srcy -= 1;
    while (srcy < 0 || srcy >= COLS)
    {
        cout << "Please choose a number between [1 - " << COLS << "] : ";
        cin >> srcy;
        srcy -= 1;
    }

    cout << "Enter X position for point B (1 - " << ROWS << ") : ";
    cin >> dstx;
    dstx -= 1;
    while (dstx < 0 || dstx >= ROWS)
    {
        cout << "Please choose a number between [1 - " << ROWS << "] : ";
        cin >> dstx;
        dstx -= 1;
    }

    cout << "Enter Y position for point B (1 - " << COLS << ") : ";
    cin >> dsty;
    dsty -= 1;
    while (dsty < 0 || dsty >= COLS)
    {
        cout << "Please choose a number between [1 - " << COLS << "] : ";
        cin >> dsty;
        dsty -= 1;
    }

    src = srcx * COLS + srcy;
    dst = dstx * COLS + dsty;
}

void init()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            empty_grid[i][j] = i * COLS + j;
    }

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        par[i] = i;
        visited[i] = false;
        for (int j = 0; j < V; j++)
            cost[i][j] = INF;
    }
    dist[src] = 0;
}

bool is_valid_pos(int x, int y) { return x >= 0 && x < ROWS && y >= 0 && y < COLS; }

void init_cost()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {

            int row = empty_grid[i][j];
            int col = row;
            cost[row][col] = 0;

            for (int k = 0; k < 4; k++)
            {
                int tmpx = i + adj_posX[k];
                int tmpy = j + adj_posY[k];
                if (is_valid_pos(tmpx, tmpy))
                    cost[row][tmpx * COLS + tmpy] = 1;
            }
        }
    }
}

int getMin()
{
    int key = 0;
    int min = INT_MAX;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            key = i;
        }
    }
    return key;
}

void dijkstra()
{
    dist[src] = 0;
    par[src] = -1;

    for (int g = 0; g < V - 1; g++)
    {
        int u = getMin();
        visited[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && (dist[u] + cost[u][v]) < dist[v] && cost[u][v] != 999)
            {
                par[v] = u;
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }
}

void recreate_path()
{
    for (int i = 0; i < V; i++)
    {
        if (i == dst)
        {
            int tmp = par[i];
            while (tmp != -1)
            {
                path.push_back(tmp / COLS);
                path.push_back(fmod(tmp, COLS));
                // path{x,y,x2,y2,....}
                tmp = par[tmp];
            }
        }
    }
}

void display()
{
    while (!path.empty())
    {
        int x = path.front();
        path.pop_front();
        int y = path.front();
        path.pop_front();

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (i == x && j == y)
                    cout << "X";

                else if (i == srcx && j == srcy)
                    cout << "A";

                else if (i == dstx && j == dsty)
                    cout << "B";

                else
                    cout << "-";
            }
            cout << "\n";
        }
        this_thread::sleep_for(chrono::milliseconds(100));
        system("clear");
    }
}

int main()
{
    input();
    init();
    init_cost();
    dijkstra();
    recreate_path();
    display();

    return 0;
}