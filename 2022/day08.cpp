// day08.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

bool isVisible(const int row, const int column, const vector<vector<int>>& grid);

int main()
{
    ifstream input;
    input.open("day08.txt");
    string line;
    vector<vector<int>> treemap;
    int sum = 0;
    
    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }
        while (getline(input, line))
        {
            vector<int> v;
            for (int i = 0; i < line.length(); i++)
            {
                v.push_back(int(line[i]) - '0');
            }
            treemap.push_back(v);
        }

        for (int row = 0; row < treemap.size(); row++)
        {
            for (int column = 0; column < treemap[row].size(); column++)
            {
                if (isVisible(row, column, treemap))
                {
                    sum++;
                    cout << "1";
                }
                else
                {
                    cout << "0";
                }
            }
            cout << endl;
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    cout << "Sum: " << sum << endl;
    
    input.close();
    return 0;
}

/// <summary>
/// Checks if a tree is visible from the outside
/// </summary>
/// <param name="row">Row of tree</param>
/// <param name="column">Column of tree</param>
/// <param name="grid">Grid of trees</param>
/// <returns>True if tree is visible</returns>
bool isVisible(const int row, const int column, const vector<vector<int>>& grid)
{
    // All edges are visible
    if (row == 0 || row == grid.size() - 1 || column == 0 || column == grid[row].size() - 1)
    {
        return true;
    }

    // Check West visibility
    bool visible = true;
    for (int i = 0; i < row; i++)
    {
        if (grid[i][column] >= grid[row][column])
        {
            visible = false;
            break;  // Not visible from west
        }
    }
    if (visible)
    {
        return true;
    }
    
    // Check East visibility
    visible = true;
    for (int i = row + 1; i < grid.size(); i++)
    {
        if (grid[i][column] >= grid[row][column])
        {
            visible = false;
            break;  // Not visible from east
        }
    }
    if (visible)
    {
        return true;
    }

    // Check North visibility
    visible = true;
    for (int i = 0; i < column; i++)
    {
        if (grid[row][i] >= grid[row][column])
        {
            visible = false;
            break;  // Not visible from north
        }
    }
    if (visible)
    {
        return true;
    }

    // Check South visibility
    visible = true;
    for (int i = column + 1; i < grid[row].size(); i++)
    {
        if (grid[row][i] >= grid[row][column])
        {
            visible = false;
            break;  // Not visible from south
        }
    }
    if (visible)
    {
        return true;
    }

    // Not visible
    return false;
}