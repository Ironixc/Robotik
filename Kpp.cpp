#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;
string Move_direction[] = {"Left", "Right", "Down", "Up"};
vector<string> Path = {};

int Move_Vertical[] = {0, 0, 1, -1};
int Move_Horizontal[] = {-1, 1, 0, 0};
int Moves = 0;

struct Location
{
    int VerticalPoint;
    int HorizontalPoint;
    int Count;
    vector<string> direction;
};

void FindF(vector<vector<string>> &layout, int &StartPointVertical, int &StartPointHorizontal)
{
    int Vertical = layout.size();
    int Horizontal = layout[0].size();

    vector<vector<bool>> Visited(Vertical, vector<bool>(Horizontal, false));
    queue<Location> R; // R = Robot/Possition
    R.push({StartPointVertical,StartPointHorizontal , 0, {}});
    Visited[StartPointVertical][StartPointHorizontal] = true;
    while (R.size() != 0)
    {
        Location Now = R.front();
        R.pop();
        if (layout[Now.VerticalPoint][Now.HorizontalPoint] == "F")
        {
            Moves = Now.Count;
            StartPointHorizontal = Now.HorizontalPoint;
            StartPointVertical = Now.VerticalPoint;
            Path = Now.direction;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int newVertical = Now.VerticalPoint + Move_Vertical[i];
            int newHorizontal = Now.HorizontalPoint + Move_Horizontal[i];
            if (newVertical >= 0 && newHorizontal >= 0 && newVertical < Vertical && newHorizontal < Horizontal && layout[newVertical][newHorizontal] != "#" && layout[newVertical][newHorizontal] != "B" && Visited[newVertical][newHorizontal] == false)
            {
                Visited[newVertical][newHorizontal] = true;
                vector<string> NewPath = Now.direction;
                NewPath.push_back(Move_direction[i]);
                R.push({newVertical, newHorizontal, Now.Count + 1, NewPath});
            }
        }
    }
}

void FindE(vector<vector<string>> &layout, int &StartPointVertical, int &StartPointHorizontal)
{
    int Vertical = layout.size();
    int Horizontal = layout[0].size();

    vector<vector<bool>> Visited(Vertical, vector<bool>(Horizontal, false));
    queue<Location> R; // R = Robot/Possition
    R.push({StartPointVertical, StartPointHorizontal, 0, Path});

    while (R.size() != 0)
    {
        Location Now = R.front();
        R.pop();
        if (layout[Now.VerticalPoint][Now.HorizontalPoint] == "E")
        {
            Moves += Now.Count;
            StartPointHorizontal = Now.HorizontalPoint;
            StartPointVertical = Now.VerticalPoint;
            Path = Now.direction;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int newVertical = Now.VerticalPoint + Move_Vertical[i];
            int newHorizontal = Now.HorizontalPoint + Move_Horizontal[i];
            if (newVertical >= 0 && newHorizontal >= 0 && newVertical < Vertical && newHorizontal < Horizontal && layout[newVertical][newHorizontal] != "#" && layout[newVertical][newHorizontal] != "B" && Visited[newVertical][newHorizontal] == false)
            {
                Visited[newVertical][newHorizontal] = true;
                vector<string> NewPath = Now.direction;
                NewPath.push_back(Move_direction[i]);
                R.push({newVertical, newHorizontal, Now.Count + 1, NewPath});
            }
        }
    }
} 

int main()
{
    vector<vector<string>> layout = {
        {"#", "#", "#", "#", "#", "#", "#"},
        {"#", "S", "#", "B", ".", "#", "#"},
        {"#", ".", ".", ".", "F", ".", "#"},
        {"#", ".", ".", ".", ".", ".", "#"},
        {"#", ".", "#", "#", ".", "E", "#"},
        {"#", "#", "#", "#", "#", "#", "#"}
    };
    int StartPointVertical = 1;
    int StartPointHorizontal = 1;

    FindF(layout, StartPointVertical, StartPointHorizontal);
    cout << Moves << StartPointHorizontal << StartPointVertical << endl;
    for (int i = 0; i < Path.size(); i++)
    {
        cout << Path[i] << "-->";
    }
    FindE(layout, StartPointVertical, StartPointHorizontal);
    cout << Moves << StartPointHorizontal << StartPointVertical;
    for (int i = 0; i < Path.size(); i++)
    {
        cout << Path[i] << "-->";
    }
}
