// day05.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Anti
// Discord
// Spoiler
// Preview

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <stack>
#include <vector>

using namespace std;

vector<int> ExtractNumbersFromString(string s, char delim);
void PrintCrateTops(vector<stack<char>> v);

int main()
{
    ifstream file;
    file.open("day05.txt");
    string line;
    bool firstline = true, input = true;

    vector<stack<char>> crates;      // :)
    vector<stack<char>> loadcrates;  // (:

    try
    {
        if (!file)
        {
            throw runtime_error("Could not open file");
        }
        while (getline(file, line))
        {
            if (input)  // Still loading crate starting positions
            {
                for (int i = 0; i < (line.length() / 4) + 1; i++)
                {
                    if (firstline)  // Initialize the stack vector the first time through
                    {
                        stack<char> cratestack;
                        if (line[i * 4] == '[')
                        {
                            cratestack.push(line[i * 4 + 1]);
                        }
                        loadcrates.push_back(cratestack);
                    }
                    else
                    {
                        if (line[i * 4] == '[')
                        {
                            loadcrates[i].push(line[i * 4 + 1]);
                        }
                    }
                }

                firstline = false;
            }
            else
            {
                if (!firstline)     // flip the stacks
                {
                    for (int i = 0; i < loadcrates.size(); i++)
                    {
                        crates.push_back(loadcrates[i]);
                        while (loadcrates[i].size() > 0)
                        {
                            crates[i].push(loadcrates[i].top());
                            loadcrates[i].pop();
                        }
                    }

                    firstline = true;       // only do this once
                    loadcrates = crates;    // use loadcrates for part 2
                }

                int from, to, num;
                vector<int> v = ExtractNumbersFromString(line, ' ');
                num = v[0];
                from = v[1] - 1;
                to = v[2] - 1;

                // use temp stack to un-invert the crane movement for 9001
                stack<char> temp;

                // move crates
                for (int i = 0; i < num; i++)
                {
                    if (crates[from].size() > 0)
                    {
                        crates[to].push(crates[from].top());
                        crates[from].pop();
                    }
                    if (loadcrates[from].size() > 0)
                    {
                        temp.push(loadcrates[from].top());
                        loadcrates[from].pop();
                    }
                }
                for (int i = 0; i < num; i++)   // Reassemble crate order
                {
                    if (temp.size() > 0)
                    {
                        loadcrates[to].push(temp.top());
                        temp.pop();
                    }
                }
            }
            if (line[1] == '1')
            {
                input = false;
                getline(file, line);    // Skip empty line
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    PrintCrateTops(crates);
    PrintCrateTops(loadcrates);

    file.close();
}

/// <summary>
/// Returns a vector with all numbers separated by a delimiter
/// </summary>
/// <param name="s">string to search</param>
/// <param name="delim">delimiter to check</param>
/// <returns>vector of numbers</returns>
vector<int> ExtractNumbersFromString(string s, char delim)
{
    vector<int> v;
    stringstream ss;

    ss << s;

    string temp;
    int found;

    while (!ss.eof())
    {
        ss >> temp;
        if (stringstream(temp) >> found)
        {
            v.push_back(found);
        }
    }
    return v;
}

/// <summary>
/// Prints the content of the top crate in each stack
/// </summary>
/// <param name="v">Vector of crate stacks to print</param>
void PrintCrateTops(vector<stack<char>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].size() > 0)
        {
            cout << v[i].top();
        }
        else
        {
            cout << "empty";
        }
    }
    cout << endl;
}