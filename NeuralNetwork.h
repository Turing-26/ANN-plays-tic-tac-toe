#pragma once
#include "Matrix.h"
#include "read.h"
#include <bits/stdc++.h>

using namespace std;

float sigmoid(float z)
{
    float s = (float)1 / (1 + exp(-1 * z));
    return s;
}

float derSigmoid(float z) // argument z is the output of the sigmoid function
{
    return z * (1 - z);
}

float tanH(float x)
{
    return tanh(x);
}

float dertanH(float x)
{
    return 1 - (tanh(x) * tanh(x));
}

class NeuralNetwork
{
    std::vector<int> topology; // number of neurons at each layer
    std::vector<Matrix> valueMat;
    std::vector<Matrix> weightMat;
    std::vector<Matrix> bias;
    std::vector<vector<float>> input;
    std::vector<int> target;
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

            Matrix biasMat(topology[1], topology[i + 1]);
            biasMat = biasMat.apply([](const float)
                                    { return (float)rand() / (float)RAND_MAX * 2 - 1; });

            this->bias.push_back(biasMat);
        }

        // valueMat.resize(topology.size());
        for (int i = 0; i < topology.size(); i++)
        {
            valueMat.push_back(Matrix(topology[i], 1));
        }

        input = readers::read();

        for (int i = 0; i < input.size(); i++)
        {
            target.push_back(input[i].back());
        }
    }

    Matrix feedForward(std::vector<float> in)
    {
        Matrix vals(1, in.size());
        for (int i = 0; i < in.size(); i++)
        {
            vals.setVal(in[i], i);
        }

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

    bool backPropogate(std::vector<int> target)
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
            Matrix trans = weightMat[i].trans();
            Matrix error = errors.mult(trans);
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

    // void read()
    // {
    //     ifstream data("tic-tac-toe.data");
    //     string in;

    //     for (int i = 0; i < 958; i++)
    //     {
    //         data >> in;
    //         int l = 0;
    //         for (int j = 0; j < 19; j++)
    //         {
    //             if (in[j] == 'x')
    //             {
    //                 input[i][l] = 1;
    //                 l++;
    //             }
    //             else if (in[j] == 'o')
    //             {
    //                 input[i][l] = -1;
    //                 l++;
    //             }
    //             else if (in[j] == 'b')
    //             {
    //                 input[i][l] = 0.01;
    //                 l++;
    //             }
    //             else if (in[j] == 'p')
    //             {
    //                 target.push_back(1);
    //                 break;
    //             }
    //             else if (in[j] == 'n')
    //             {
    //                 target.push_back(0);
    //                 break;
    //             }
    //         }
    //     }
    // }

    void train()
    {
        for (int i = 0; i < 958; i++)
        {
            while (1)
            {
                Matrix res = feedForward(input[i]);

                if (res.at(0, 0) > 0.5)
                    break;
                else if (target[i] == 1)
                {
                    std::vector<int> tar;
                    tar.push_back(target[i]);
                    backPropogate(tar);
                }
                else
                    break;
            }
        }
        std::cout << "Done!";
    }

    std::vector<float> prediction()
    {
        return valueMat.back().getVals();
    }
};