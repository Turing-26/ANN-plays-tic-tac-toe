/**
 * @file tictactoe.cpp
 * @author Sarim Ahmad(2021572), Ahmed Ali Abid(2021065), Mohommad Omar Khan(2021305)
 * @brief This project consistes of of a neural network that is trained to play tic-tac-toe with a human
 * @version 0.1(beta)
 * @date 2022-05-26
 *
 */

#include "NeuralNetwork.h"
#include <iostream>

using namespace std;

class TicTacToe
{
    friend class NeuralNetwork;
    int player;
    vector<float> board;

public:
    /**
     * @brief Construct a new Tic Tac Toe object
     */
    TicTacToe()
    {
        player = 1;

        for (int i = 0; i < 9; i++)
        {
            board.push_back((float)0.01);
        }
    }

    /**
     * @brief it helps deciding the index on which the Ai will play the game .
     */
    int aiMove(NeuralNetwork n)
    {
        vector<float> temp = board;
        vector<float> prob(9, 1);
        Matrix res;

        for (int i = 0; i < 9; i++)
        {
            if (board[i] == (float)0.01)
            {
                temp[i] = -1;
                Matrix res = n.feedForward(temp);
                prob[i] = res.at(0, 0);
                cout << res.at(0, 0) << endl;
                temp[i] = 0.01;
            }
            // cout << prob[i] << endl;
        }

        float min = 1;
        for (int i = 0; i < 9; i++)
        {
            if (prob[i] < min)
                min = prob[i];
        }

        int index;
        for (int i = 0; i < 9; i++)
        {
            if (min == prob[i])
                index = i;
        }
        cout << index << endl;

        return index;
    }

    /**
     * @brief it displays a board on the console for the player to play the game.
     */
    void displayBoard()
    {
        for (int i = 0; i < 9; i++)
        {
            if ((i + 1) % 3 == 0)
            {
                if (board[i] == 0.01f)
                    cout << " " << endl;
                if (board[i] == (float)1)
                    cout << "X" << endl;
                if (board[i] == float(-1))
                    cout << "O" << endl;
            }
            else
            {
                if (board[i] == 0.01f)
                    cout << " |";
                if (board[i] == (float)1)
                    cout << "X|";
                if (board[i] == float(-1))
                    cout << "O|";
            }
        }
    }

    /**
     * @brief it checks the conditions of winnig and draw of the
     *        game and tells us which plaer has won the game
     */
    bool endGame()
    {
        int filled = 0;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] != (float)0.01)
                filled++;
        }

        for (int i = 0; i < 7; i += 3)
        {
            if ((board[i] != (float)0.01) && (board[i] == board[i + 1] && board[i] == board[i + 2]))
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (board[i] != (float)0.01 && board[i] == board[i + 3] && board[i] == board[i + 6])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }

            if (i == 0 && board[i] != (float)0.01 && board[i] == board[i + 4] && board[i] == board[i + 8])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }

            if (i == 2 && board[i] != (float)0.01 && board[i] == board[i + 2] && board[i] == board[i + 4])
            {
                cout << "Player " << player << " wins\n";
                return 1;
            }
        }

        if (filled == 9)
        {
            cout << "Game ended in a draw...\n";
            return 1;
        }

        return 0;
    }

    /**
     * @brief it starts the game between two real players without the use of ai.
     */
    void playGame()
    {
        while (1)
        {
            displayBoard();
            int pos;

            cout << "Player " << player << "'s"
                 << " turn\n";
            cout << "What position do you want to play in (number from 0 to 8)?\n";
            cin >> pos;

            while (pos < 0 || pos > 8 || board[pos] != 0.01)
            {
                cout << "Invalid position, enter again\n";
                cin >> pos;
            }

            player == 1 ? board[pos] = player : board[pos] = -1;

            if (endGame())
            {
                displayBoard();
                break;
            }

            player == 1 ? player = 2 : player = 1;
        }
    }

    /**
     * @brief it launches a game in which our real player plays with the AI.
     */
    void playWithAi(NeuralNetwork n)
    {
        while (1)
        {
            displayBoard();
            int pos;

            if (player == 1)
            {
                cout << "Players turn\n";
                cout << "What position do you want to play in (number from 0 to 8)?\n";
                cin >> pos;

                while ((pos < 0 || pos > 8) || board[pos] != (float)0.01)
                {
                    cout << "Invalid position, enter again\n";
                    cin >> pos;
                }
            }
            else
            {
                pos = aiMove(n);
                cout << "\n";
            }

            player == 1 ? board[pos] = player : board[pos] = -1;

            if (endGame())
            {
                displayBoard();
                break;
            }

            player == 1 ? player = 2 : player = 1;
        }
    }
};

int main()
{
    srand(time(NULL)); // to generate random numbers
    vector<int> topology = {9, 5, 1};

    NeuralNetwork network(topology, 0.01);
    TicTacToe tictactoe;

    network.train();
    // tictactoe.playGame();
    tictactoe.playWithAi(network);

    return 0;
}