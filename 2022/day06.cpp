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
    const int SIGSIZE = 4;
    int index = 0;
    char signal[SIGSIZE] = { 'c', 'c', 'c', 'c' };

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
            if (!(temp[0] == temp[1] || temp[1] == temp[2] || temp[2] == temp[3]) && index > 3)
            {
                break;
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    cout << "Signal begins after character " << index << endl;
    for (int i = 0; i < SIGSIZE; i++)
    {
        cout << signal[i] << ",";
    }
}
