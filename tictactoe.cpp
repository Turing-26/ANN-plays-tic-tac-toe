#include <iostream>
#include "NeuralNetwork.h"

using namespace std;

class TicTacToe
{
    int player;
    vector<int> board;

public:
    TicTacToe()
    {
        player = 1;

        for (int i = 0; i < 9; i++)
        {
            board.push_back(0);
        }
    }

    void displayGrid()
    {
        for (int i = 0; i < 9; i++)
        {
            if ((i + 1) % 3 == 0)
            {
                cout << board[i] << endl;
            }
            else
            {
                cout << board[i] << "|";
            }
        }
    }

    bool endGame()
    {
        int filled = 0;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] > 0)
                filled++;
        }

        if (filled == 9)
        {
            cout << "Game ended in a draw...\n";
            return 1;
        }

        for (int i = 0; i < 7; i += 3)
        {
            if ((board[i] > 0) && (board[i] == board[i + 1] == board[i + 2]))
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (board[i] > 0 && board[i] == board[i + 3] && board[i] == board[i + 6])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }

            if (i == 0 && board[i] > 0 && board[i] == board[i + 4] && board[i] == board[i + 8])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }

            if (i == 2 && board[i] > 0 && board[i] == board[i + 2] && board[i] == board[i + 4])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }
        }

        return 0;
    }

    void playGame()
    {
        while (1)
        {
            displayGrid();
            int pos;

            cout << "Player " << player << "'s"
                 << " turn\n";
            cout << "What position do you want to play in (number from 0 to 8)?\n";
            cin >> pos;

            while (pos < 0 || pos > 8 || board[pos] != 0)
            {
                cout << "Invalid position, enter again\n";
                cin >> pos;
            }

            board[pos] = player;

            if (endGame())
            {
                displayGrid();
                break;
            }

            player == 1 ? player = 2 : player = 1;
        }
    }
};

int main()
{
}