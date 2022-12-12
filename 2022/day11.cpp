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
    queue<unsigned long long> items;
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
void tossMonkeyItems(vector<monkey>& monkeys, monkey& m, int lcf);
unsigned long long countInspections(const vector<monkey>& monkeys);

const int NUM_ROUNDS = 10000;
const int UNDAMAGED_MODIFIER = 1;

int main()
{
    ifstream input;
    input.open("day11.txt");
    string line;
    unsigned long long monkeybusiness = 0;
    int lcf = 1;
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
                lcf *= monkeys[monkeys.size() - 1].divisibility;
            }
        }

        // Toss items
        for (int i = 0; i < NUM_ROUNDS; i++)
        {
            for (int j = 0; j < monkeys.size(); j++)
            {
                tossMonkeyItems(monkeys, monkeys[j], lcf);
            }
            
            int round = i + 1;

            if (round == 1 || round == 20 || round % 1000 == 0)
            {
                cout << "== After round " << round << " ==\n";
                monkeybusiness = countInspections(monkeys);
                cout << endl;
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    input.close();
    cout << "Monkey business: " << monkeybusiness << "\n";
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
            // Starting items begin at index 2)
            for (int j = 2; j <= v.size() - 1; j++)
            {
                // Trim comma if necessary
                if (j != v.size() - 1)
                {
                    v[j] = v[j].substr(0, v[j].length() - 1);
                }
                m.items.push(stoi(v[j]));
            }
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

/// <summary>
/// 
/// </summary>
/// <param name="monkeys"></param>
/// <param name="i"></param>
void tossMonkeyItems(vector<monkey>& monkeys, monkey& m, int lcf)
{
    while (m.items.size() > 0)
    {
        int modifier = m.oldmodifier ? m.items.front() : m.modifier;                            // Set modifier
        m.items.front() = m.addition ? m.items.front() + modifier : m.items.front() * modifier; // Adjust worry value
        m.inspections++;                                                                        // Increment inspection
        m.items.front() /= UNDAMAGED_MODIFIER;                                                  // Monkey gets bored
        m.items.front() %= lcf;                                                                 // 'find another way to keep worry manageable'
        int index = (m.items.front() % m.divisibility == 0) ? m.indexT : m.indexF;              // Choose new monkey
        monkeys[index].items.push(m.items.front());                                             // Toss item to target
        m.items.pop();                                                                          // Remove item from current monkey
    }
}

/// <summary>
/// Counts each monkey's inspections and prints to cout
/// </summary>
/// <param name="monkeys">Monkeys to check</param>
unsigned long long countInspections(const vector<monkey>& monkeys)
{
    unsigned long long inspectmax = 0;
    unsigned long long inspectmax2 = 0;

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
    return inspectmax * inspectmax2;
}
