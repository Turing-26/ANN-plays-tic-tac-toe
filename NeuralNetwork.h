/**
 * @file NeuralNetwork.h
 * @brief Neural network class
 * @date 2022-05-26
 *
 */
#pragma once
#include "Matrix.h"
#include "read.h"
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief activation function .
 *
 * @param z input value coming into the node.
 */

float sigmoid(float z)
{
    float s = (float)1 / (1 + exp(-1 * z));
    return s;
}

/**
 * @brief deravative used for error calculation for back propogation.
 *
 * @param z argument z is the output of the node.
 */

float derSigmoid(float z)
{
    return z * (1 - z);
}

// float tanH(float x)
// {
//     return tanh(x);
// }

// float dertanH(float x)
// {
//     return 1 - (tanh(x) * tanh(x));
// }

/**
 * @brief class that helps learing of ai
 */

class NeuralNetwork
{
    std::vector<int> topology; // number of neurons at each layer
    std::vector<Matrix> valueMat;
    std::vector<Matrix> weightMat;
    std::vector<Matrix> bias;
    std::vector<vector<float>> input;
    std::vector<vector<float>> target;
    float learningRate;

public:
    NeuralNetwork(std::vector<int> top, float lr = 0.1) : topology(top), weightMat({}), valueMat({}), bias({}), learningRate(lr)
    {

        for (int i = 0; i < topology.size() - 1; i++)
        {
            Matrix weightMat(topology[i], topology[i + 1]);
            weightMat = weightMat.apply([](const float)
                                        { return (float)rand() / (float)RAND_MAX * 2 - 1; });

            this->weightMat.push_back(weightMat);

            Matrix biasMat(1, topology[i + 1]);
            biasMat = biasMat.apply([](const float)
                                    { return (float)rand() / (float)RAND_MAX * 2 - 1; });

            this->bias.push_back(biasMat);
        }

        valueMat.resize(topology.size());
        // for (int i = 0; i < topology.size(); i++)
        // {
        //     valueMat.push_back(Matrix(topology[i], 1));
        // }

        input = readers::read();
        target.resize(input.size());

        for (int i = 0; i < input.size(); i++)
        {
            target[i].push_back(input[i].back());
            input[i].pop_back();
        }
    }

    /**
     * @brief gets the output value for thee sets of
     *        input indicating the current status of the board.
     *
     * @param in a vecctor showing all nine positions in a board.
     * @return Matrix
     */

    Matrix feedForward(std::vector<float> in)
    {
        Matrix vals(1, in.size());
        for (int i = 0; i < in.size(); i++)
            vals.setVal(in[i], i);

        // Feed forward to next layers
        for (int i = 0; i < weightMat.size(); i++)
        {
            valueMat[i] = vals;
            vals = vals.mult(weightMat[i]);
            vals = vals.add(bias[i]);

            // if (i == weightMat.size() - 1)
            vals = vals.apply(sigmoid);
            // else
            //     vals = vals.apply(tanH);
        }

        valueMat[weightMat.size()] = vals;

        return valueMat.back();
    }

    /*
    error = realVal - output; // error is minimized on every iteration to get it as close as possible to zero
    (d/dx)(error) = (+/-) value; // change weight by a small amount determined by the learning rate
    */

    /**
     * @brief corrects our weights acooriding to desired output value.
     *
     * @param target a desired output value
     */

    bool backPropogate(std::vector<float> target)
    {
        if (target.size() != topology.back())
            return 0;

        Matrix errors(1, target.size());
        for (int i = 0; i < target.size(); i++)
        {
            errors.setVal(target[i], i);
        }
        Matrix sub = valueMat.back().neg(); // ch
        errors = errors.add(sub);

        for (int i = weightMat.size() - 1; i >= 0; i--)
        {
            Matrix transpose = weightMat[i].trans();
            Matrix error = errors.mult(transpose);
            // Matrix DOut = valueMat[i + 1];

            // if (i == weightMat.size())
            Matrix DOut = valueMat[i + 1].apply(derSigmoid);
            // else
            //     Matrix DOut = valueMat[i + 1].apply(dertanH);

            Matrix derror = errors.multEl(DOut);
            derror = derror.mult(learningRate);

            Matrix weightChange = valueMat[i].trans().mult(derror);

            weightMat[i] = weightMat[i].add(weightChange);
            bias[i] = bias[i].add(derror);

            errors = error;
        }

        return 1;
    }
    /**
     * @brief training our neural network to correctly identify patterns.
     */

    void train()
    {
        std::cout << "Training started\n";

        for (int i = 0; i < 100000; i++)
        {
            int in = rand() % 958;
            feedForward(input[in]);
            backPropogate(target[in]);
        }

        // std::cout << feedForward(input[126]).at(0, 0) << endl;
        // std::cout << feedForward(input[896]).at(0, 0) << endl;
        // std::cout << feedForward(input[233]).at(0, 0) << endl;
        std::cout << "Done!\n";
    }

    void displayIn()
    {
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < input[i].size(); j++)
            {
                cout << input[i][j] << ",";
            }
            cout << endl;
        }
    }

    void displayOut()
    {
        for (int i = 0; i < target.size(); i++)
        {
            for (int j = 0; j < target[i].size(); j++)
            {
                cout << target[i][j] << ",";
            }
            cout << endl;
        }
    }
};