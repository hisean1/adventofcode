// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <istream>

using namespace std;

int main()
{
    ifstream file;
    file.open("day02.txt");
    string line;
    int sum = 0;

    try
    {
        if (!file)
        {
            throw runtime_error("Could not open file");
        }

        while (getline(file, line))
        {
            switch (line[2])
            {
            case 'X':               // MUST LOSE
                switch (line[0])
                {
                case 'A':
                    sum += 3;       // 3 pt for choosing scissors
                    break;
                case 'B':
                    sum += 1;       // 1 pt for choosing rock'
                    break;
                case 'C':
                    sum += 2;       // 2 pt for choosing paper
                default:
                    break;
                }
                break;
            case 'Y':               // MUST TIE
                sum += 3;           // 3 pt for tying
                switch (line[0])
                {
                case 'A':
                    sum += 1;       // 1 pt for choosing rock
                    break;
                case 'B':
                    sum += 2;       // 2 pt for choosing paper
                    break;
                case 'C':
                    sum += 3;       // 3 pt for choosing scissors
                default:
                    break;
                }
                break;
            case 'Z':               // MUST WIN
                sum += 6;           // 3 pt for winning
                switch (line[0])
                {
                case 'A':
                    sum += 2;       // 2 pt for choosing paper
                    break;
                case 'B':
                    sum += 3;       // 3 pt for choosing scissors
                    break;
                case 'C':
                    sum += 1;       // 1 pt for choosing rock
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
    catch (exception &e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
    }

    cout << "Sum: " << sum << "\n";

    file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
