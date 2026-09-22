#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Location // This struct is to save a multiple variable that have different types into 1 array
{
    int VP, HP, M;    // VP = Vertical Point, HP = Horizontal Point, M = Moves Number what
    vector<string> D; // D = Direction
};

class Maze // This class is to hold the logic of the maze eg(What maze is it and the starting point of it and for the updated starting point UP)
{
private:
    vector<vector<char>> L; // L = Layout
    int CV = 1, CH = 1;     // CV = Current Vertical, CH = Current Horizontal, TM = Total Moves

public:
    Maze(vector<vector<char>> Layout) // This is for getting the maze layout
    {
        L = Layout;
    }

    vector<vector<char>> getL() { return L; } // this is to return the value of L or getting it
    int getV() { return CV; }                 // this is to return the value of CV or getting it
    int getH() { return CH; }                 // this is to return the value of CH or getting it

    vector<string> TF, TG; // TF = To Flag, TG = To Goal
    void UP(int v, int h)  // Update Possiton after its done with F
    {
        CV = v; // V = Vertical
        CH = h; // H = Horizontal
    }
};

class BFS // This is for the logic of how the Robot will solve the maze which is using BFS (Breath First Search)
{
private:                                            // private only this class can access these variable fuciton or etc
    int MV[4] = {0, 0, 1, -1};                      // MV = Move Vertical the array for direction
    int MH[4] = {-1, 1, 0, 0};                      // MH = Move Horizontal the array for direction
    string MD[4] = {"Left", "Right", "Down", "Up"}; // MD = Move Direction
    void findExit(Maze &Maze, char Target, int &TM, vector<string> &TP)
    {
        vector<vector<char>> L = Maze.getL(); // getting the maze from Maze class
        int V = L.size();                     // getting the how long the vertical of maze from L
        int H = L[0].size();                  // getting the how long the Horizontal of maze from L[0]
        int SV = Maze.getV();                 // SV = Starting Vertical this is getting the CV from maze basicly
        int SH = Maze.getH();                 // SV = Starting Vertical this is getting the CH from maze basicly

        vector<vector<bool>> visited(V, vector<bool>(H, false)); // this is to make every singel tile maze false (so its not visited)
        queue<Location> R;                                       // using queue because so we get FIFO (First in First out) so its the fastest way
        R.push({SV, SH, 0, {}});                                 // add the first variable or the starting point of the Robot
        visited[SV][SH] = true;                                  // make the starting point true so the Robot dont go back
        while (R.size() != 0)                                    // if there still a path to explore then keep running it
        {
            Location Now = R.front();        // get the array in the front of the queue
            R.pop();                         // Remove the top of the queue so it can process the next one
            if (L[Now.VP][Now.HP] == Target) // Chekc if the coordinate has reached the target char (F or G)
            {
                TM += Now.M;                           // We add the total Moves because if there 2 target it need to be added
                Maze.UP(Now.VP, Now.HP);               // Update the last possition of V and H and chaged it to SV and SH (this is for if there more than 1 goals)
                for (int i = 0; i < Now.D.size(); i++) // Get all of the total path form (F or even G)
                {
                    TP.push_back(Now.D[i]); // Get all the Direction form the first Move to the last (use push back so its in order)
                }
                return;
            }
            for (int i = 0; i < 4; i++) // Check all 4 direction
            {
                int newVertical = Now.VP + MV[i];   // Take what is the VP then add it with the MV (array index)
                int newHorizontal = Now.HP + MH[i]; // Take what is the HP then add it with the MH (array index)

                if (newVertical >= 0 && newHorizontal >= 0 && newVertical < V && newHorizontal < H && L[newVertical][newHorizontal] != '#' && L[newVertical][newHorizontal] != 'X' && visited[newVertical][newHorizontal] == false)
                {                                                             // The if statment is for checking whether its out of bounds (like -1,0 etc), The new Vertical and Horizontal is not a Wall, Bomb or have been visited
                    visited[newVertical][newHorizontal] = true;               // mark the coodinate as visited so it dont go there again
                    vector<string> NewPath = Now.D;                           // Add another path that the robot can possibly take
                    NewPath.push_back(MD[i]);                                 // Add the new direction but from the back so use push back
                    R.push({newVertical, newHorizontal, Now.M + 1, NewPath}); // we add the new struct or new array to the struct so it can
                    // be checked again for next moves
                }
            }
        }
    }

public: // public every class can access this variable or fuction
    vector<string> find(Maze Maze)
    {
        int TM = 0;         // TM = Total Move
        vector<string> TPF; // TPF = Total Path to Find F
        vector<string> TPG; // TPG = Total Path to Find G
        vector<string> TP;  // TP == Total Path Form F to G

        cout << "Start Possition : (1,1)" << endl; // cause the first one always start at 1,1 so just use string

        findExit(Maze, 'F', TM, TPF); // call the fuction of findExit in the BFS private to find the F and get the TM and TPF
        cout << "Path To Flag : ";
        for (int i = 0; i < TPF.size(); i++) // after getting the F print the TPF form like 1 --> 2 --> 3(the parameter size is to check how long
        // the data is)
        {
            cout << TPF[i];          // print the Direction
            if (i == TPF.size() - 1) // if it the i is the same as the total size - 1 then it dont print 3 (-->) (-1 becuase the size is start at 1 not 0)
            {
                // do nothing
            }
            else
            {
                cout << " --> "; // add -->
            }
        }
        cout << endl;
        cout << "Flag Capture : (" << Maze.getV() << "," << Maze.getH() << ")" << endl;
        // Get the last point of V and H after reaching F or starting point of the next one

        findExit(Maze, 'G', TM, TPG); // call the fuction of findExit in the BFS private to find the G and get the TM and TPG
        cout << "Path To Base : ";
        for (int i = 0; i < TPG.size(); i++) // after getting the G print the TPG form like 1 --> 2 --> 3(the parameter size is to check how long
                                             // the data is)
        {
            cout << TPG[i];
            if (i == TPG.size() - 1) // if it the i is the same as the total size - 1 then it dont print 3 (-->) (-1 becuase the size is start at 1 not 0)
            {
                // do nothing
            }
            else
            {
                cout << " --> "; // add -->
            }
        }
        cout << endl;
        cout << "Base Reached : (" << Maze.getV() << "," << Maze.getH() << ")" << endl;
        // Get the last point of V and H after reaching F or starting point of the next one
        cout << "Total Moves : " << TM << endl; // get the total Moves

        TP.insert(TP.end(), TPF.begin(), TPF.end()); // Get all TPF direction begin to end in TP from the back
        TP.insert(TP.end(), TPG.begin(), TPG.end()); // Get all TPF direction begin to end in TP from the back

        return TP; //return the full step so the Visialisation can get the variable (or the finalpath so it have varibale)
    }
};

class Visualisation // Visualisation how the Robot will move from S to F to G
{
private:
    void Map(vector<vector<char>> L, int V, int H)// getting the map Vertivcal and Horizontal Point
    {
        L[V][H] = 'R';// Change the tile maze if the robot is at that location 
        for (auto &row : L)// looping for getting the map of the maze with the 'R'
        {
            for (char cell : row)
            {
                cout << cell << ' ';
            }
            cout << '\n';
        }
        cout << "---------------------------------\n";
    }

public:
    void Visual(Maze Maze, vector<string> fullPath)
    {

        vector<vector<char>> L = Maze.getL(); // Get the maze size or what maze this is
        int CV = 1; //start point always 1
        int CH = 1; //start point always 1
        Map(L, CV, CH); // for the start of the maze
        for (int i = 0; i < fullPath.size(); i++)// loop until the the fullpath is do
        {
            cout << "Press Enter\n";
            cout << "---------------------------------\n";

            cin.get();// User Input need to pressed enter so it continue to the next step
            //Check what is the string in the fullpath index then covert the string like left to CH--; because CH-- is left in the logic
            if (fullPath[i] == "Left")
                CH--;
            else if (fullPath[i] == "Right")
                CH++;
            else if (fullPath[i] == "Up")
                CV--;
            else if (fullPath[i] == "Down")
                CV++;

            Map(L, CV, CH);// check the maze, where is the updated Vertical and Horizontal point and get 3 of that to the fuction map
        }
    }
};

int main()
{
    int a;
    vector<vector<char>> layout1 = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '#', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', 'G', '#'},
        {'#', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '.', '.', '.', '#'},
        {'#', 'X', '.', '.', 'F', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}}; // Maze layout1

    vector<vector<char>> layout2 = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#', 'G', '#'},
        {'#', '.', '#', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '#', '#'},
        {'#', 'X', '.', '.', '#', '.', '.', 'F', '#'},
        {'#', '.', '#', '#', '#', 'X', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#'}}; // Maze layout2

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
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}}; // maze layout3

    Maze selectedMaze = layout1; //new variable to hold the user input what maze is it
    BFS b;//to call the BFS fuction or class
    Visualisation vis; //to call the Visualisation fuction or class
    vector<string> finalPath; //New variable to get the total path from TP

    cout << "Which Maze (1-3) : ";
    cin >> a;
    cout << "---------------------------------\n";
    switch (a)
    {
    case 1:
    {
        break;// dont change cause the default maze is 1
    }
    case 2:
    {
        selectedMaze = layout2;//change the maze to 2 if user input 2
        break;
    }
    case 3:
    {
        selectedMaze = layout3;//change the maze to 3 if user input 3
        break;
    }
    default:
        cout << "Salah Input";// if it not 1-3
        break;
    }
    finalPath = b.find(selectedMaze);//call the find fuction in BFS to solve the maze and get the TP to finalPath
    cout << "---------------------------------\n";
    cout << "Type 1 for robot visualisation : ";
    cin >> a;
    if (a == 1)//if the user want Visualisation press if not then ok
    {
        vis.Visual(selectedMaze, finalPath);// call the Visual fuction with the selected maze (user input the maze at the start) and
        //final path that we got from (BFS find)
    }
    else
    {
        cout << "ok";
    }
    return 0;
}
