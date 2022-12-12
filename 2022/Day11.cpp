// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct monkey
{
    queue<int> items;
    int indexT;
    int indexF;
    int divisibility;
    int modifier;
    int inspections;
    bool addition;
    bool oldmodifier;

    monkey() : indexT(0), indexF(0), divisibility(1), modifier(0), inspections(0), addition(true), oldmodifier(false)
    {
    }
};

monkey readMonkeyFromFile(ifstream& f);
vector<string> tokenizeString(const string s);
void tossMonkeyItems(vector<monkey>& monkeys, int i);

const int NUM_ROUNDS = 20;
const int UNDAMAGED_MODIFIER = 3;

int main()
{
    ifstream input;
    input.open("day11.txt");
    string line;
    int inspectmax = 0;
    int inspectmax2 = 0;
    vector<monkey> monkeys;

    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }

        // Import monkeys
        while (getline(input, line))
        {
            if (line.substr(0, 6) == "Monkey")
            {
                monkeys.push_back(readMonkeyFromFile(input));
            }
        }
        //cout << "monkey[0].items.size(): " << monkeys[0].items.size() << endl;

        // Toss items
        for (int i = 0; i < NUM_ROUNDS; i++)
        {
            for (/*monkey m : monkeys*/int j = 0; j < monkeys.size(); j++)
            {
                //cout << "New monkey\n";
                tossMonkeyItems(monkeys, j);
            }
            //cout << "Round " << i + 1 << "\tmonkeys[0].items.front(): " << monkeys[0].items.front() << endl;
        }

        // Count inspections
        for (int i = 0; i < monkeys.size(); i++)
        {
            cout << "Monkey " << i << " inspected " << monkeys[i].inspections << " items.\n";
            if (monkeys[i].inspections > inspectmax)
            {
                inspectmax2 = inspectmax;
                inspectmax = monkeys[i].inspections;
            }
            else if (monkeys[i].inspections > inspectmax2)
            {
                inspectmax2 = monkeys[i].inspections;
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    input.close();
    cout << "Monkey business: " << inspectmax * inspectmax2 << "\n";
}

/// <summary>
/// Creates a monkey from a file
/// </summary>
/// <param name="f">File to read from</param>
/// <returns>An initialized monkey</returns>
monkey readMonkeyFromFile(ifstream& f)
{
    string s;
    monkey m;

    for (int i = 0; i < 5; i++)
    {
        getline(f, s);
        vector<string> v = tokenizeString(s);
        switch (i)
        {
        case 0: // Starting Items
            // Read starting items (beginning index 2)
            for (int j = 2; j <= v.size() - 1; j++)
            {
                // Trim comma if necessary
                if (j != v.size() - 1)
                {
                    v[j] = v[j].substr(0, v[j].length() - 1);
                }
                m.items.push(stoi(v[j]));
                //cout << stoi(v[j]) << " ";
            }
            //cout << endl;
            break;
        case 1: // Operation
            if (v[4] == "*")
            {
                m.addition = false;         // Initialized true, only change if false
            }
            if (v[5] == "old")
            {
                m.oldmodifier = true;       // Initialized false, only change if true
            }
            else
            {
                m.modifier = stoi(v[5]);    // Set modifier normally
            }
            break;
        case 2: // Divisibility Test
            m.divisibility = stoi(v[3]);
            break;
        case 3: // True Case
            m.indexT = stoi(v[5]);
            break;
        case 4: // False Case
            m.indexF = stoi(v[5]);
            break;
        }
    }
    return m;
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

void tossMonkeyItems(vector<monkey>& monkeys, int i)
{
    while (/*int i = 0; i < m.items.size(); i++*/monkeys[i].items.size() > 0)
    {
        //cout << "\tItem: " << monkeys[i].items.front() << " | oldmodifier: " << monkeys[i].oldmodifier;
        int modifier = monkeys[i].oldmodifier ? monkeys[i].items.front() : monkeys[i].modifier;                            // Set modifier
        //cout << " | Modifier: " << modifier;
        monkeys[i].items.front() = monkeys[i].addition ? monkeys[i].items.front() + modifier : monkeys[i].items.front() * modifier; // Adjust worry value
        monkeys[i].inspections++;
        //cout << " | New worry: " << monkeys[i].items.front();
        monkeys[i].items.front() /= UNDAMAGED_MODIFIER;                                                  // Monkey gets bored
        //cout << " | Bored worry: " << monkeys[i].items.front() << endl;
        int index = (monkeys[i].items.front() % monkeys[i].divisibility == 0) ? monkeys[i].indexT : monkeys[i].indexF;              // Choose new monkey
        //cout << "Throwing " << monkeys[i].items.front() << " to monkey " << index << endl;
        //cout << "monkey " << index << " size: " << monkeys[index].items.size() << " -> ";
        monkeys[index].items.push(monkeys[i].items.front());                                             // Toss item to target
        //cout << monkeys[index].items.size() << endl;
        //cout << "m.items size: " << monkeys[i].items.size() << " -> ";
        monkeys[i].items.pop();                                                                          // Remove item from current monkey
        //cout << monkeys[i].items.size() << endl;
    }
}