// day06.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Anti
// Discord
// Spoiler
// Preview

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream file;
    file.open("day06.txt");
    char c;
    const int SIGSIZE = 14;
    int index = 0;
    char signal[SIGSIZE];
    for (int i = 0; i < SIGSIZE; i++)
    {
        signal[i] = ' ';
    }

    try
    {
        if (!file)
        {
            throw runtime_error("Could not open file");
        }
        while (EOF != (c = file.get()))
        {
            index++;

            for (int i = 0; i < SIGSIZE - 1; i++)
            {
                signal[i] = signal[i + 1];
            }
            signal[SIGSIZE - 1] = c;

            char temp[SIGSIZE];
            copy(signal, signal + sizeof(signal), temp);
            sort(temp, temp + sizeof(temp));
            for (int i = 0; i < SIGSIZE - 1; i++)
            {
                if (temp[i] == temp[i + 1])
                {
                    break;
                }
                if (i == SIGSIZE - 2 && index >= SIGSIZE)
                {
                    cout << "Message begins after character " << index << endl;
                    return 0;
                }
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    cout << "No signal detected\n";
    return 0;
}
