#include <iostream>
#include "NeuralNetwork.h"

using namespace std;

class TicTacToe
{
    friend class NeuralNetwork;
    int player;
    vector<float> board;

public:
    TicTacToe()
    {
        player = 1;

        for (int i = 0; i < 9; i++)
        {
            board.push_back((float)0.01);
        }
    }

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
                temp[i] = 0.01;
            }
            cout << prob[i] << endl;
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

    void displayBoard()
    {
        for (int i = 0; i < 9; i++)
        {
            if ((i + 1) % 3 == 0)
            {
                board[i] == 0.01 ? cout << " " << endl : cout << board[i] << endl;
            }
            else
            {
                board[i] == 0.01 ? cout << " |" : cout << board[i] << "|";
            }
        }
    }

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
    srand(time(NULL));
    vector<int> topology = {9, 5, 1};
    // vector<int> topology = {2, 3, 1};

    NeuralNetwork network(topology, 0.01);
    TicTacToe tictactoe;

    network.train();
    // tictactoe.playGame();
    tictactoe.playWithAi(network);
    // network.out();
    // network.displayOut();

    // vector<vector<float>> in{
    //     {0.0f, 0.0f},
    //     {1.0f, 1.0f},
    //     {0.0f, 1.0f},
    //     {1.0f, 0.0f},
    // };

    // vector<vector<float>> out{
    //     {0.0f},
    //     {0.0f},
    //     {1.0f},
    //     {1.0f},
    // };

    // int epoch = 100000;
    // for (int i = 0; i < epoch; i++)
    // {
    //     int index = rand() % 4;
    //     Matrix res = network.feedForward(in[index]);
    //     cout << res.at(0, 0) << endl;
    //     network.backPropogate(out[index]);
    // }

    // cout << endl;

    // for (auto i : in)
    // {
    //     network.feedForward(i);
    //     auto pred = network.prediction();
    //     cout << i[0] << "," << i[1] << " -> " << pred[0] << endl;
    // }

    // return 0;
}