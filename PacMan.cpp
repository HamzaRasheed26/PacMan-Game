#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <time.h>

using namespace std;

// array for maze
const int rows = 24, cols = 71;
char maze[rows][cols];

// functions prototypes
char menu();
void printMaze();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void playGame();
void gotoxy(int x, int y);
void scoreboard();
void winner();
bool gameover();
void readMaze();
void moveGhost1();
void moveGhost2();
void moveGhost3();
int ghostDirection();
int moveGhost4();
void gameOverMessage();

// data structure and variable sfor storing position of objects

// for pacman
int PacmanX = 9;
int PacmanY = 31;

// for ghost 1
int g1x = 16;
int g1y = 31;
int flag1 = 0;

// for ghost 2
int g2x = 1;
int g2y = 29;
int flag2 = 0;

// for ghost 3
int g3x = 1;
int g3y = 60;

// for ghost 4
int g4x = 5;
int g4y = 5;

int scoreCount = 0; // for score
int lives = 3;      // for lives

bool win = false;

// main function
main()
{
    char option, again;

    readMaze(); // reading maze from file

    while (true)
    {
        option = menu(); // taking option from  menu

        if (option == '1') // optoin for playing game
        {

            while (true)
            {
                lives = 3;
                scoreCount = 0;

                playGame(); // function of playing game

                gotoxy(2, 18);
                cout << "Press Y to Play Again and N to continue : ";
                cin >> again;

                if (again == 'N' || again == 'n')
                {
                    break;
                }
            }
        }
        else if (option == '2') // option for exit
        {
            break;
        }
    }
}

// function of menu
char menu()
{
    system("cls");
    cout << "*******************************************" << endl;
    cout << "   ___   ___    __            ___         " << endl;
    cout << "  |   | |   |  /      |\\  /| |   | |\\   | " << endl;
    cout << "  |___| |___| |       | \\/ | |___| | \\  | " << endl;
    cout << "  |     |   | |       |    | |   | |  \\ | " << endl;
    cout << "  |     |   |  \\__    |    | |   | |   \\| " << endl;
    cout << endl;
    cout << "*******************************************" << endl;
    cout << "\n";
    cout << " 1. Play Game :) " << endl;
    cout << " 2. Exit " << endl;
    char option;
    while (true)
    {
        cout << " Your Option : ";
        cin >> option;

        if (option == '1' || option == '2')
        {
            return option; // returning option
        }
        cout << "Invalid input" << endl;
    }
}

// function for playing game
void playGame()
{
    bool playingGame = true;
    system("cls");
    printMaze(); // printing maze on screen
    gotoxy(PacmanY, PacmanX);
    cout << 'P';

    while (playingGame) // game loop
    {
        Sleep(100); // delaying game 

        moveGhost1(); // moving ghost 1
        moveGhost2(); // moving ghost 2
        moveGhost3(); // moving ghost 3
        moveGhost4(); // moving ghost 4

        scoreboard(); // displaying score board

        if (gameover()) // checking lives
        {
            playingGame = false;
        }

        if (GetAsyncKeyState(VK_LEFT)) // for moving pacman left
        {
            movePacmanLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT)) // for moving pacman right
        {
            movePacmanRight();
        }
        if (GetAsyncKeyState(VK_UP)) // for moving pacman up
        {
            movePacmanUp();
        }
        if (GetAsyncKeyState(VK_DOWN)) // for moving pacman down
        {
            movePacmanDown();
        }
        if (GetAsyncKeyState(VK_ESCAPE)) // for exit from runing game
        {
            playingGame = false;
        }
        if (scoreCount == 400) // wining condition
        {
            winner();
            playingGame = false;
        }
    }
}

// function for printing maze on screen
void printMaze()
{
    for (int row = 0; row < rows; row++)
    {

        for (int col = 0; col < cols; col++)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}

// function for moving pacman left
void movePacmanLeft()
{
    if (maze[PacmanX][PacmanY - 1] == ' ' || maze[PacmanX][PacmanY - 1] == '.')
    {
        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanY--;

        gotoxy(PacmanY, PacmanX);
        cout << 'P';

        if (maze[PacmanX][PacmanY - 1] == '.')
        {
            scoreCount++;
        }
    }
}

// function for moving pacman right
void movePacmanRight()
{
    if (maze[PacmanX][PacmanY + 1] == ' ' || maze[PacmanX][PacmanY + 1] == '.')
    {
        if (maze[PacmanX][PacmanY + 1] == '.')
        {
            scoreCount++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanY++;
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
    }
}

// function for moving pacman up
void movePacmanUp()
{
    if (maze[PacmanX - 1][PacmanY] == ' ' || maze[PacmanX - 1][PacmanY] == '.')
    {
        if (maze[PacmanX - 1][PacmanY] == '.')
        {
            scoreCount++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanX--;
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
    }
}

// function for moving pacman down
void movePacmanDown()
{
    if (maze[PacmanX + 1][PacmanY] == ' ' || maze[PacmanX + 1][PacmanY] == '.')
    {
        if (maze[PacmanX + 1][PacmanY] == '.')
        {
            scoreCount++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanX++;
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
    }
}

// function for displaying on required location
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// function for displaying score board anf lives
void scoreboard()
{
    gotoxy(90, 10);
    cout << "Score : " << scoreCount << endl;
    gotoxy(90, 11);
    cout << "Lives : " << lives << endl;
}

// function for winning message
void winner()
{
    gotoxy(30, 50);
    {
        cout << "*****************" << endl;
        cout << "   WINNER WINNER " << endl;
        cout << "  CHICKEN  DINNER " << endl;
        cout << "*****************" << endl;
    }
}

// function for reading maze from  file
void readMaze()
{
    fstream fileMaze;
    string line;

    fileMaze.open("mazeData.txt", ios::in);
    for (int x = 0; x < 24; x++)
    {
        getline(fileMaze, line);
        for (int y = 0; y < 71; y++)
        {
            maze[x][y] = line[y];
        }
    }
    fileMaze.close();
}

// function for checking game over condition
bool gameover()
{
    if (PacmanX == g1x && PacmanY == g1y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g2x && PacmanY == g2y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g3x && PacmanY == g3y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g4x && PacmanY == g4y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    gotoxy(PacmanY, PacmanX);
    cout << 'P';
    if (lives == 0)
    {
        gameOverMessage();
        return true;
    }
    return false;
}

// function for moving ghost 1 horizontal
void moveGhost1()
{
    char pre;
    
    // moving left
    if ((maze[g1x][g1y - 1] == ' ' || maze[g1x][g1y - 1] == '.') && flag1 == 1)
    {
        pre = maze[g1x][g1y];
        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y--;
        gotoxy(g1y, g1x);
        cout << 'G';
    }
    else
    {
        flag1 = 0;
    }
    
    // moving right
    if ((maze[g1x][g1y + 1] == ' ' || maze[g1x][g1y + 1] == '.') && flag1 == 0)
    {
        pre = maze[g1x][g1y];

        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y++;
        gotoxy(g1y, g1x);
        cout << 'G';
    }
    else
    {
        flag1 = 1;
    }
}

// function for moving ghost 2 verticl
void moveGhost2()
{
    char pre;
    
    // moving up
    if ((maze[g2x - 1][g2y] == ' ' || maze[g2x - 1][g2y] == '.') && flag2 == 1)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x--;
        gotoxy(g2y, g2x);
        cout << 'G';
    }
    else
    {
        flag2 = 0;
    }

    // moving down
    if ((maze[g2x + 1][g2y] == ' ' || maze[g2x + 1][g2y] == '.') && flag2 == 0)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x++;
        gotoxy(g2y, g2x);
        cout << 'G';
    }
    else
    {
        flag2 = 1;
    }
}

int ghostDirection()
{
    srand(time(0));
    int num = 1 + (rand() % 4);
    return num;
}

// function for moving ghost 3 random
void moveGhost3()
{

    int num = ghostDirection();

    char pre;

    if (num == 1) // moving right
    {
        if (maze[g3x][g3y + 1] == ' ' || maze[g3x][g3y + 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y++;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 2) // moving left
    {
        if (maze[g3x][g3y - 1] == ' ' || maze[g3x][g3y - 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y--;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 3) // moving up
    {
        if (maze[g3x - 1][g3y] == ' ' || maze[g3x - 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x--;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 4) // moving down
    {
        if (maze[g3x + 1][g3y] == ' ' || maze[g3x + 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x++;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
}

// function for moving ghost 4 behind the pacman
int moveGhost4()
{
    
    char pre;

    Sleep(50);

    // if pacman x greater than  ghost x than move right
    if (PacmanX > g4x) 
    {
        if (maze[g4x + 1][g4y] == ' ' || maze[g4x + 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x++;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    // if pacman x less than  ghost x than move left
    if (PacmanX < g4x)
    {
        if (maze[g4x - 1][g4y] == ' ' || maze[g4x - 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x--;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    // if pacman y greater than  ghost y than move down
    if (PacmanY > g4y)
    {
        if (maze[g4x][g4y + 1] == ' ' || maze[g4x][g4y + 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y++;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    // if pacman y less than  ghost y than move up
    if (PacmanY < g4y)
    {
        if (maze[g4x][g4y - 1] == ' ' || maze[g4x][g4y - 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y--;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
}

// function for game over message
void gameOverMessage()
{
    system("cls");
    cout << "\n\n\n";
    cout << "         ____    ___            ___    ___              ___    ___" << endl;
    cout << "        /    |  |   |  |\\  /|  |      |   |  \\      /  |      |   |" << endl;
    cout << "       |        |___|  | \\/ |  |___   |   |   \\    /   |___   |___|  " << endl;
    cout << "       |   __   |   |  |    |  |      |   |    \\  /    |      |  \\     " << endl;
    cout << "        \\_|  |  |   |  |    |  |___   |___|     \\/     |___   |   \\  " << endl;
    cout << "" << endl;

    cout << "\n Press any key to continue...";
    getch();
    getch();
}