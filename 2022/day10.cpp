// day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Anti
// Discord
// Preview
// Spoiler

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <vector>

using namespace std;

vector<string> tokenizeString(const string s);
int addx(const int value, int& x, int& cycle);
void updateCycle(int& cycle, const int x);

bool thisproblemisstupidthatsnothowcycleswork = false;
const int SCREEN_WIDTH = 40;
const int SIGNAL_STRENGTH_CYCLE = 20;

int main()
{
    ifstream input;
    input.open("day10.txt");
    string line, cmd, param1;
    int cycle = 0, x = 1, sum = 0, row = -1;

    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }

        while (getline(input, line))
        {
            vector<string> v = tokenizeString(line);
            cmd = v[0];
            if (v.size() > 1)
            {
                param1 = v[1];
            }

            if (cmd == "noop")
            {
                updateCycle(cycle, x);
            }
            else if (cmd == "addx")
            {
                sum += addx(stoi(param1), x, cycle);
            }

            if (cycle % SCREEN_WIDTH == SIGNAL_STRENGTH_CYCLE)       // New signal strength update
            {
                if (thisproblemisstupidthatsnothowcycleswork)
                {
                    thisproblemisstupidthatsnothowcycleswork = false;
                }
                else
                {
                    sum += x * cycle;
                }
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    input.close();
    cout << "Sum: " << sum << "\n";
}

/// <summary>
/// Tokenizes a string separated by spaces
/// </summary>
/// <param name="s">String to tokenize</param>
/// <returns>Vector containing individual words</returns>
vector<string> tokenizeString(const string s)
{
    vector<string> v;
    stringstream ss;

    ss << s;
    string temp;

    while (!ss.eof())
    {
        ss >> temp;
        v.push_back(temp);
    }

    return v;
}

/// <summary>
/// Simulates an addx function call
/// </summary>
/// <param name="value">Value to add to x</param>
/// <param name="x">Location of 'x register'</param>
/// <param name="cycle">Cycle number</param>
/// <returns></returns>
int addx(const int value, int& x, int& cycle)
{
    bool midcycle = false;

    updateCycle(cycle, x);

    if (cycle % SCREEN_WIDTH == SIGNAL_STRENGTH_CYCLE)
    {
        midcycle = true;
    }

    updateCycle(cycle, x);
    x += value;

    if (cycle % SCREEN_WIDTH == SIGNAL_STRENGTH_CYCLE)
    {
        thisproblemisstupidthatsnothowcycleswork = true;
        return (x - value) * cycle;
    }

    return midcycle ? (x - value) * (cycle - 1) : 0;
}

/// <summary>
/// Increments the cycle and handles rendering the appropriate pixel
/// </summary>
/// <param name="cycle">Current cycle</param>
/// <param name="x">Value of 'x register'</param>
void updateCycle(int& cycle, const int x)
{
    // Check if sprite is visible
    cout << (abs((cycle % SCREEN_WIDTH) - x) <= 1 ? '#' : '.');
    cycle++;

    if (cycle % SCREEN_WIDTH == 0 && cycle != 0)   // New row for screen
    {
        cout << "\n";
    }
}