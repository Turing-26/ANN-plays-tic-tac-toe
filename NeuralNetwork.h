#include "Matrix.h"
// #include <bits/stdc++.h>

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

class NeuralNetwork
{
    std::vector<int> topology; // number of neurons at each layer
    std::vector<Matrix> valueMat;
    std::vector<Matrix> weightMat;
    std::vector<Matrix> bias;
    float learningRate;

public:
    NeuralNetwork(std::vector<int> top, float lr = 0.1) : topology(top), weightMat({}), valueMat({}), bias({}), learningRate(lr)
    {
        for (int i = 0; i < topology.size() - 1; i++)
        {
            Matrix weightMat(topology[i], topology[i + 1]);
            weightMat = weightMat.apply([](const float)
                                        { return (float)rand() / RAND_MAX; });

            this->weightMat.push_back(weightMat);

            Matrix biasMat(topology[1], topology[i + 1]);
            biasMat = biasMat.apply([](const float)
                                    { return (float)rand() / RAND_MAX; });

            this->bias.push_back(biasMat);
        }

        valueMat.resize(topology.size());
    }

    bool feedForward(std::vector<float> in)
    {
        if (in.size() != topology[0])
            return 0;

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
            vals = vals.apply(sigmoid);
        }

        valueMat[weightMat.size()] = vals;

        return 1;
    }

    /*
    error = realVal - output; // error is minimized on every iteration to get it as close as possible to zero
    (d/dx)(error) = (+/-) value; // change weight by a small amount determined by the learning rate
    */

    bool backPropogation(std::vector<float> target)
    {
        if (target.size() != topology.back())
            return 0;

        Matrix errors(1, target.size());
        for (int i = 0; i < target.size(); i++)
        {
            errors.setVal(target[i], i);
        }

        Matrix sub = valueMat[-1].neg(); // ch
        errors = errors.add(sub);

        for (int i = weightMat.size() - 1; i >= 0; i--)
        {
            Matrix trans = weightMat[i].trans();
            Matrix error = errors.mult(trans);
            Matrix DOut = valueMat[i + 1].apply(derSigmoid);
            Matrix derror = errors.multEl(DOut);
            derror = derror.mult(learningRate);

            Matrix weightChange = valueMat[i].trans().mult(derror);

            weightMat[i] = weightMat[i].add(weightChange);
            bias[i] = bias[i].add(derror);

            errors = error;
        }

        return 1;
    }

    std::vector<float> prediction()
    {
        return valueMat[-1].getVals();
    }
};