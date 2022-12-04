// day04.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Anti
// Discord
// Preview
// Spoiler

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>

using namespace std;

int main()
{
    ifstream file;
    file.open("day04.txt");
    string line, elf1, elf2;
    int elf1low, elf1high, elf2low, elf2high, sum = 0;

    try
    {
        if (!file)
        {
            throw runtime_error("Could not open file");
        }

        while (getline(file, line))
        {
            elf1 = line.substr(0, line.find(","));
            elf2 = line.substr(line.find(",") + 1, line.length() - line.find(","));
            
            elf1low = stoi(elf1.substr(0, elf1.find("-")));
            elf1high = stoi(elf1.substr(elf1.find("-") + 1, elf1.length() - elf1.find("-")));
            elf2low = stoi(elf2.substr(0, elf2.find("-")));
            elf2high = stoi(elf2.substr(elf2.find("-") + 1, elf2.length() - elf2.find("-")));

            if ((elf1low <= elf2low && elf1high >= elf2high) || (elf2low <= elf1low && elf2high >= elf1high))
            {
                sum++;
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    cout << "Sum: " << sum << "\n";
    file.close();
    return 0;
}