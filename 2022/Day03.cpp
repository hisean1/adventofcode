// Day03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
//

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <istream>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

char FindIntersection(string s1, string s2);
char FindIntersectionPeek3(ifstream &file, string line, int iter);
int GetElfValue(char c);

int main()
{
    ifstream file;
    file.open("day03.txt");
    string line;
    int sum = 0;
    int sum2 = 0;

    try
    {
        if (!file)
        {
            throw runtime_error("Could not open file");
        }

        string front;
        string back;
        char intersection;
        char badge;
        int iter = 0;

        while (getline(file, line))
        {
            front = line.substr(0, line.length() / 2);
            back = line.substr(line.length() / 2, line.length());
            intersection = FindIntersection(front, back);

            sum += GetElfValue(intersection);
            
            //cout << "Read line: " << line << endl;
            
            if (iter % 3 == 0 && file)
            {
                //cout << "Peek3: ";
                badge = FindIntersectionPeek3(file, line, iter);
                sum2 += GetElfValue(badge);
                //cout << file.tellg() << endl;
            }
            iter++;
            //cout << file.tellg() << " || iter: " << iter << endl;
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
    }

    cout << "Sum: " << sum << "\n" << "Sum2: " << sum2 << endl;
}

/// <summary>
/// Finds intersecting character between two strings (assuming only 1)
/// </summary>
/// <param name="s1">String 1</param>
/// <param name="s2">String 2</param>
/// <returns>Intersecting character</returns>
char FindIntersection(string s1, string s2)
{
    for (int i = 0; i < s1.length(); i++)
    {
        for (int j = 0; j < s2.length(); j++)
        {
            if (s1[i] == s2[j])
            {
                return s1[i];
            }
        }
    }
    return 0;
}

/// <summary>
/// Finds intersecting character between 3 consecutive lines (assuming only 1)
/// </summary>
/// <param name="&file">File to read</param>
/// <param name="line">Last line read</param>
/// <returns>Intersecting character</returns>
char FindIntersectionPeek3(ifstream &file, string line, int iter)
{
    //cout << "Peek3 start\n";
    int pos = file.tellg();         // save current position
    //if (pos > 9400) cout << file.tellg() << endl;
    string line2, line3;
    if (!file)
    {
        cout << "PEEk 3 FAILURE THIS IS NOT A DRILL" << endl;
        return 0;
    }
    getline(file, line2);
    //if (pos > 9400) cout << file.tellg() << endl;
    if (!file)
    {
        cout << "PEEk 3 FAILURE THIS IS NOT A DRILL" << endl;
        return 0;
    }
    getline(file, line3);
    //if (pos > 9400) cout << file.tellg() << endl;

    // Stop it.  Get some help.
    int hackpos = pos;
    switch (iter)
    {
    case 0:
        hackpos -= 1;
        break;
    case 288:
        hackpos += 2;
    case 291:
        hackpos += 2;
    case 294:
        hackpos += 2;
    case 297:
        hackpos += 2;
    case 300:
        hackpos += 3;
        break;
    default:
        hackpos -= 3;
    }

    file.seekg(hackpos, ios_base::beg); // return to starting position
    //if (pos > 9400) cout << file.tellg() << endl;

    //cout << "Line1: " << line << "\nLine2: " << line2 << "\nLine3: " << line3 << endl;

    for (int i = 0; i < line.length(); i++)
    {
        for (int j = 0; j < line2.length(); j++)
        {
            for (int k = 0; k < line3.length(); k++)
            {
                if (line[i] == line2[j] && line[i] == line3[k])
                {
                    //cout << "Peek3 end\n\n";
                    return line[i];
                }
            }
        }
    }
    cout << "PEEk 3 FAILURE THIS IS NOT A DRILL" << endl;
    return 0;
}

/// <summary>
/// Finds the elf value of a character
/// </summary>
/// <param name="c">Character to evaluate</param>
/// <returns>Integer elf value of character</returns>
int GetElfValue(char c)
{
    if (c == 0)
    {
        return 0;   // Bad data
    }
    if (isupper(c))
    {
        return c - 38;  // Capital letter char offset
    }
    return c - 96;  // Lowercase letter char offset
}