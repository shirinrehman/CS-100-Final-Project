/* CS-100 Final Project by:
Shirin Rehman */

#include <iostream>
using namespace std;
#include <string>
#include <windows.h> 
#include <limits>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int ROW = 6;
const int COL = 7;
char player_char = 'O';
int choice;

string player_1;
string player_2;
string nameplaceholder;

void Board_Setup();
void Current_Board();
void Piece_Display(int);

bool win();
bool full_board();
bool horizontal();
bool vertical();
bool diagonal();

char board[ROW][COL];

int main() // main function
{
    cout << "                                             " << endl;
    cout << "WELCOME TO CONNECT-4! PLEASE ENTER YOUR NAMES" << endl;
    cout << "                                             " << endl;
    cout << "Player 1: ";
    getline(cin, player_1);
    cout << "Player 2: ";
    getline(cin, player_2);
    nameplaceholder = player_1;

    Board_Setup();
    cout << endl;

    cout << "LETS BEGIN!" << endl;

    while (!(win()))
    {
        cout << nameplaceholder << "'s turn. Select your Column...";
        cin >> choice;

        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // checks if cin is non numeric input 
            cout << "\nOops, Invalid move!" << endl;
            cout << nameplaceholder << "'s turn. Select your Column...";
            cin >> choice;
        }

        Piece_Display(choice - 1);

        if ( win() )
        {
            break; 
        }

        if (full_board())
        {
            cout << "Looks like it's a Draw! Play Again..." << endl;
            return 0;
        }
    }

    cout << nameplaceholder << " wins the game!" << endl;

    return 0;
}

void Board_Setup() // prints the board
{
    cout << "----------------------" << endl;
    for (int j = 0; j <= ROW - 1; j++)
    {
        for (int i = 0; i <= COL - 1; i++)
        {
            board[i][j] = ' ';
            cout << "|" << board[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "----------------------" << endl;
    }
    cout << " 1  2  3  4  5  6  7" << endl;
}

void Current_Board() // prints current state of board
{
    cout << "----------------------" << endl;
    for (int j = 0; j <= ROW - 1; j++)
    {
        for (int i = 0; i <= COL - 1; i++)
        {
            cout << "|" ;
            if (board[i][j]== 'X')
            {
                SetConsoleTextAttribute(hConsole, 11);
            }
            else if (board[i][j]== 'O')
            {
                SetConsoleTextAttribute(hConsole, 12);
            }
            cout << board[i][j] << " ";
            SetConsoleTextAttribute(hConsole, 15);
        }
        cout << "|" << endl;
        cout << "----------------------" << endl;
    }
    cout << " 1  2  3  4  5  6  7" << endl;
}

void Piece_Display(int choice) /*traverses a column(from the bottom up), checks for free space and assigns the current
player char onto the first free space index of the board matrix */
{
    for (int i = ROW - 1; i >= 0; i--)
    {
        if (board[choice][i] == ' ')
        {
            board[choice][i] = player_char;
            if (player_char == 'O')
            {
                player_char = 'X';
            }
            else
            {
                player_char = 'O';
            }
            if (nameplaceholder == player_1 && !win())
            {
                nameplaceholder = player_2;
            }
            else if (nameplaceholder == player_2 && !win())
            {
                nameplaceholder = player_1;
            }
            Current_Board();
            return;
        }
    }
    cout << "Oops, Invalid move!" << endl;
}

bool horizontal() // checks if a char repeats x4 consecutively in a horizontal direction
{
    int x_check = 0;
    int o_check = 0;

    for (int i = ROW - 1; i >= 0; i--)
    {
        x_check = 0;
        o_check = 0;
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == 'X')
            {
                x_check++;
                o_check = 0;
            }
            if (board[i][j] == 'O')
            {
                o_check++;
                x_check = 0;
            }
            if (board[i][j] == ' ')
            {
                o_check = 0;
                x_check = 0;
            }
            if (o_check >= 4 || x_check >= 4)
            {
                return true;
            }
        }
    }
    return false;
}

bool vertical() // checks if a char repeats x4 consecutively in a vertical direction
{
    int x_check = 0;
    int o_check = 0;

    for (int j = 0; j < COL; j++)
    {
        x_check = 0;
        o_check = 0;
        for (int i = ROW - 1; i >= 0; i--)
        {
            if (board[i][j] == 'X')
            {
                x_check++;
                o_check = 0;
            }
            if (board[i][j] == 'O')
            {
                o_check++;
                x_check = 0;
            }
            if (board[i][j] == ' ')
            {
                o_check = 0;
                x_check = 0;
            }
            if (o_check >= 4 || x_check >= 4)
            {
                return true;
            }
        }
    }
    return false;
}

bool diagonal() // checks if a char repeats x4 consecutively diagonally 
{
    for ( int i = ROW-1; i>= 0; i-- )
    {
        for ( int j = 0; j<COL; j++ ) // checks for upper left to lower right diagonals
        {
             if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] &&
                board[i - 2][j + 2] == board[i - 3][j + 3] && (board[i][j] == 'X' || board[i][j] == 'O'))
            {
                return true;
            }

        }
    }

    for ( int i = ROW-1; i>= 0; i-- )
    {
        for ( int j = 0; j<COL; j++ ) // checks for lower left to upper right diagonals 
        {
            if (board[i][j] == board[i - 1][j - 1] && board[i - 1][j - 1] == board[i - 2][j - 2] &&
                board[i - 2][j - 2] == board[i - 3][j - 3] && (board[i][j] == 'X' || board[i][j] == 'O'))
            {
                return true;
            }

        }
    }

    return false; 
}


bool full_board() // checks if the board is full or not
{
    for (int i = 0; i < ROW - 1; i++)
    {
        for (int j = 0; j < COL - 1; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

bool win() // checks if any of the players has made a connect-4
{
    if (horizontal())
    {
        return true;
    }
    else if (vertical())
    {
        return true;
    }
    else if (diagonal())
    {
        return true;
    }
    else
    {
        return false;
    }
}