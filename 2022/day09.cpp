// day09.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Anti
// Discord
// Preview
// Spoiler

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <iterator>
#include <set>

const int NUM_TAILS = 9;
using namespace std;

enum Dir {U, D, L, R};

struct coord
{
    int x = 0;
    int y = 0;

    bool operator<(const coord& crd) const noexcept
    {
        return this->x + this->y * 10000 < crd.x + crd.y * 10000;
    }
};

void moveHead(coord& h, const Dir d);
void moveTail(coord& t, const coord& h);

int main()
{
    ifstream input;
    input.open("day09.txt");
    string line;

    coord tails[NUM_TAILS + 1] = {};
    set<coord> grid;
    
    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }

        for (int i = 0; i <= NUM_TAILS; i++)
        {
            tails[i].x = 0;
            tails[i].y = 0;
        }
        grid.insert(tails[0]);     // Visit origin initially

        while (getline(input, line))
        {
            Dir direction = U;
            int distance = 0;
            switch (line[0])
            {
            case 'U':
                direction = U;
                break;
            case 'D':
                direction = D;
                break;
            case 'L':
                direction = L;
                break;
            case 'R':
                direction = R;
                break;
            default:
                cout << "Invalid direction\n";
            }
            
            distance = stoi(line.substr(2, line.length() - 2));

            for (int i = 0; i < distance; i++)
            {
                moveHead(tails[0], direction);

                // Move all tails
                for (int j = 1; j <= NUM_TAILS; j++)
                {
                    moveTail(tails[j], tails[j - 1]);
                    if (j == NUM_TAILS)
                    {
                        grid.insert(tails[NUM_TAILS]);
                    }
                }
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    cout << "Locations visited: " << grid.size() << "\n";
    input.close();
}

/// <summary>
/// Moves the head coordinate 1 unit in a direction
/// </summary>
/// <param name="h">Coordinate of head</param>
/// <param name="d">Direction to move</param>
void moveHead(coord& h, const Dir d)
{
    switch (d)
    {
    case U:
        h.y += 1;
        break;
    case D:
        h.y -= 1;
        break;
    case L:
        h.x -= 1;
        break;
    case R:
        h.x += 1;
    }
}

/// <summary>
/// Moves a tail knot according to its head
/// </summary>
/// <param name="t">Tail coordinate</param>
/// <param name="h">Head coordinate</param>
void moveTail(coord& t, const coord& h)
{
    // Move diagonally first if needed
    if (abs(h.y - t.y) > 0 && abs(h.x - t.x) > 0 && (abs(h.y - t.y) > 1 || abs(h.x - t.x) > 1))
    {
        signbit(double(h.y - t.y)) ? t.y -= 1 : t.y += 1;
        signbit(double(h.x - t.x)) ? t.x -= 1 : t.x += 1;
    }

    // Recover y coordinate if needed
    while (abs(h.y - t.y) > 1)
    {
        signbit(double(h.y - t.y)) ? t.y -= 1 : t.y += 1;
    }
    //Recover x coordinate if needed
    while (abs(h.x - t.x) > 1)
    {
        signbit(double(h.x - t.x)) ? t.x -= 1 : t.x += 1;
    }
}