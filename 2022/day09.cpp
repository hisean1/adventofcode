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

void moveHead(coord& h, const int dist, const Dir d);
void moveTail(coord& t, const coord& h, set<coord>& s);
void visitCoord(const coord& t, set<coord>& s);

int main()
{
    ifstream input;
    input.open("day09.txt");
    string line;

    coord head;
    coord tail;
    set<coord> grid;
    
    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }

        visitCoord(tail, grid);     // Visit origin initially

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
            moveHead(head, distance, direction);
            moveTail(tail, head, grid);
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

void moveHead(coord& h, const int dist, const Dir d)
{
    switch (d)
    {
    case U:
        h.y += dist;
        break;
    case D:
        h.y -= dist;
        break;
    case L:
        h.x -= dist;
        break;
    case R:
        h.x += dist;
    }
}

void moveTail(coord& t, const coord& h, set<coord>& s)
{
    // Move diagonally first if needed
    if (abs(h.y - t.y) > 0 && abs(h.x - t.x) > 0 && (abs(h.y - t.y) > 1 || abs(h.x - t.x) > 1))
    {
        signbit(double(h.y - t.y)) ? t.y -= 1 : t.y += 1;
        signbit(double(h.x - t.x)) ? t.x -= 1 : t.x += 1;
        visitCoord(t, s);
    }

    // Recover y coordinate if needed
    while (abs(h.y - t.y) > 1)
    {
        signbit(double(h.y - t.y)) ? t.y -= 1 : t.y += 1;
        visitCoord(t, s);
    }
    //Recover x coordinate if needed
    while (abs(h.x - t.x) > 1)
    {
        signbit(double(h.x - t.x)) ? t.x -= 1 : t.x += 1;
        visitCoord(t, s);
    }
}

void visitCoord(const coord& t, set<coord>& s)
{
    s.insert(t);
}