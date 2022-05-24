#pragma once
#include <fstream>
#include <vector>

// using namespace std;

namespace readers
{
    std::string erase(char *s, char r)
    {
        int l = 0;
        while (*s != '\0')
        {
            l++;
            s++;
        }
        s -= l;

        std::string newS;

        for (int i = 0; i < l; i++)
        {
            if (s[i] == r)
                continue;
            else if (s[i] == 'p' || s[i] == 'n')
            {
                newS += s[i];
                break;
            }
            else
                newS += s[i];
        }

        return newS;
    }

    std::vector<std::vector<float>> read()
    {
        std::ifstream dataIn("tic-tac-toe.data");
        std::vector<std::string> dataStr;
        std::string d;

        while (!dataIn.eof())
        {
            getline(dataIn, d, '\n');
            dataStr.push_back(d);
        }
        dataIn.close();

        int l = dataStr.size();

        std::vector<std::vector<float>> data(l, std::vector<float>(10, 0));

        for (int i = 0; i < l; i++)
        {
            dataStr[i] = erase(&dataStr[i][0], ',');

            for (int j = 0; j < dataStr[i].size(); j++)
            {
                if (dataStr[i][j] == 'x')
                    data[i][j] = 1;
                else if (dataStr[i][j] == 'o')
                    data[i][j] = -1;
                else if (dataStr[i][j] == 'b')
                    data[i][j] = (float)0.01;
                else if (dataStr[i][j] == 'p')
                    data[i][j] = 1;
                else if (dataStr[i][j] == 'n')
                    data[i][j] = -1;
            }
        }

        std::ofstream dataOut("output.data");

        int ll = data[0].size();

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < ll; j++)
            {
                dataOut << data[i][j] << ',';
            }
            dataOut << '\n';
        }
        dataOut.close();

        return data;
    }

}
