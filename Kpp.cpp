#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Location
{
    int VP, HP, M;    // VP = Vertical Point, HP = Horizontal Point, M = Moves
    vector<string> D; // D = Direction
};

class Maze
{
private:
    vector<vector<char>> L; // L = Layout
    int CV = 1, CH = 1;     // SV = Start Vertical, SH = Start Horizontal, TM = Total Moves

public:
    Maze(vector<vector<char>> Layout)
    {
        L = Layout;
    }

    vector<vector<char>> getL() { return L; }
    int getV() { return CV; }
    int getH() { return CH; }

    vector<string> TF, TG; // TF = To Flag, TG = To Goal
    void UP(int v, int h)
    { // Update Possiton
        CV = v;
        CH = h;
    }
};

class BFS
{
private:
    int MV[4] = {0, 0, 1, -1};                      // MV = Move Vertical
    int MH[4] = {-1, 1, 0, 0};                      // MH = Move Horizontal
    string MD[4] = {"Left", "Right", "Down", "Up"}; // MD = Move Direction
    void findExit(Maze &Maze, char Target, int &TM, vector<string> &TP)
    {
        vector<vector<char>> L = Maze.getL();
        int V = L.size();
        int H = L[0].size();
        int SV = Maze.getV();
        int SH = Maze.getH();

        vector<vector<bool>> visited(V, vector<bool>(H, false));
        queue<Location> R;
        R.push({SV, SH, 0, {}});
        visited[SV][SH] = true;
        while (R.size() != 0)
        {
            Location Now = R.front();
            R.pop();
            if (L[Now.VP][Now.HP] == Target)
            {
                TM += Now.M;
                Maze.UP(Now.VP, Now.HP);
                for (int i = 0; i < Now.D.size(); i++)
                {
                    TP.push_back(Now.D[i]);
                }
                return;
            }
            for (int i = 0; i < 4; i++)
            {
                int newVertical = Now.VP + MV[i];
                int newHorizontal = Now.HP + MH[i];

                if (newVertical >= 0 && newHorizontal >= 0 && newVertical < V && newHorizontal < H && L[newVertical][newHorizontal] != '#' && L[newVertical][newHorizontal] != 'X' && visited[newVertical][newHorizontal] == false)
                {
                    visited[newVertical][newHorizontal] = true;
                    vector<string> NewPath = Now.D;
                    NewPath.push_back(MD[i]);
                    R.push({newVertical, newHorizontal, Now.M + 1, NewPath});
                }
            }
        }
    }

public:
    void find(Maze Maze)
    {
        int TM = 0;
        vector<string> TPF;
        vector<string> TPG;

        cout << "Map Loaded :" << endl;
        cout << "Start Possition : (1,1)" << endl;

        findExit(Maze, 'F', TM, TPF);
        cout << "Path To Flag :";
        for (int i = 0; i < TPF.size(); i++)
        {
            cout << TPF[i];
            if (i == TPF.size() - 1)
            {
                //do nothing
            }
            else
            {
                cout << " --> ";
            }
        }
        cout << endl;
        cout << "Flag Capture : (" << Maze.getV() << "," << Maze.getH() << ")" << endl;

        findExit(Maze, 'G', TM, TPG);
        cout << "Path To Base :";
        for (int i = 0; i < TPG.size(); i++)
        {
            cout << TPG[i];
             if (i == TPG.size() - 1)
            {
                //do nothing
            }
            else
            {
                cout << " --> ";
            }
        }
        cout << endl;
        cout << "Base Reached : (" << Maze.getV() << "," << Maze.getH() << ")" << endl;
        cout << TM;
    }
};

int main()
{
    int a;
    vector<vector<char>> layout1 = {
        {
            '#',
            '#',
            '#',
            '#',
            '#',
            '#',
            '#',
        },
        {
            '#',
            'S',
            '#',
            '.',
            '.',
            '.',
            '#',
        },
        {
            '#',
            '.',
            '#',
            '.',
            '#',
            'G',
            '#',
        },
        {
            '#',
            '.',
            '.',
            '.',
            '#',
            '.',
            '#',
        },
        {
            '#',
            '#',
            '#',
            '.',
            '.',
            '.',
            '#',
        },
        {
            '#',
            'X',
            '.',
            '.',
            'F',
            '.',
            '#',
        },
        {
            '#',
            '#',
            '#',
            '#',
            '#',
            '#',
            '#',
        }};

    vector<vector<char>> layout2 = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#', 'G', '#'},
        {'#', '.', '#', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '#', '#'},
        {'#', 'X', '.', '.', '#', '.', '.', 'F', '#'},
        {'#', '.', '#', '#', '#', 'X', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    vector<vector<char>> layout3 = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '#', '.', '.', '.', '#', 'G', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '#', '#', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '.', 'X', '.', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '#', '#', '#', '.', '#', 'F', '#'},
        {'#', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    BFS b;
    cout << "Which Maze (1-3)";

    scanf("%d", &a);
    switch (a)
    {
    case 1:
    {
        Maze maze1(layout1);
        b.find(maze1);
        break;
    }
    case 2:
    {
        Maze maze1(layout2);
        b.find(maze1);
        break;
    }
    case 3:
    {
        Maze maze1(layout3);
        b.find(maze1);
        break;
    }
    default:
        cout << "Salah Input";
        break;
    }
}
