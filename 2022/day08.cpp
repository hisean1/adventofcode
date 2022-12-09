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

enum Dir { n, s, e, w };

bool isVisible(const int height, const vector<int>& treeline);
int distanceToBlocker(const int height, const vector<int>& treeline);
vector<int> getTreesInDirection(const int row, const int column, const vector<vector<int>>& grid, Dir d);

int main()
{
    ifstream input;
    input.open("day08.txt");
    string line;
    vector<vector<int>> treemap;
    int sum = 0, bestview = 0, bestrow = 0, bestcolumn = 0;
    
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
                // All edges are visible
                if (row == 0 || row == treemap.size() - 1 || column == 0 || column == treemap[row].size() - 1)
                {
                    sum++;
                }
                else
                {
                    bool visible = false;
                    int viewscore = 1;

                    for (int dir = n; dir <= w; dir++)
                    {
                        vector<int> v = getTreesInDirection(row, column, treemap, Dir(dir));

                        if (isVisible(treemap[row][column], v))
                        {
                            visible = true;
                        }
                        viewscore *= distanceToBlocker(treemap[row][column], v);
                    }
                    if (viewscore > bestview)
                    {
                        bestview = viewscore;
                        bestrow = row;
                        bestcolumn = column;
                    }
                    if (visible)
                    {
                        sum++;
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

    cout << "Sum: " << sum << endl;
    cout << "Best View: (" << bestrow << "," << bestcolumn << "): " << bestview << endl;
    
    input.close();
    return 0;
}

/// <summary>
/// Checks if a tree is visible from outside the forest
/// </summary>
/// <param name="height">Height of tree to check</param>
/// <param name="treeline">Trees between target and viewer</param>
/// <returns>Whether tree is visible</returns>
bool isVisible(const int height, const vector<int>& treeline)
{
    for (int i = 0; i < treeline.size(); i++)
    {
        if (height <= treeline[i])
        {
            return false;   // Not visible
        }
    }

    // Not blocked, must be visible
    return true;
}

/// <summary>
/// Calculates the distance to a view-blocking tree (if one exists)
/// </summary>
/// <param name="height">Height of tree to calculate</param>
/// <param name="treeline">Trees in direction to calculate</param>
/// <returns>Distance to view-blocking tree, or edge of forest otherwise</returns>
int distanceToBlocker(const int height, const vector<int>& treeline)
{
    for (int i = 0; i < treeline.size(); i++)
    {
        if (height <= treeline[i])
        {
            return i + 1;   // Blocked at i
        }
    }
    // Unblocked to edge of forest
    return treeline.size();
}

/// <summary>
/// Gets the trees (in order) in a direction, from a grid coordinate
/// </summary>
/// <param name="row">Row of target tree</param>
/// <param name="column">Column of target tree</param>
/// <param name="grid">Grid of the forest heights</param>
/// <param name="d">Direction to search</param>
/// <returns>Vector containing tree heights</returns>
vector<int> getTreesInDirection(const int row, const int column, const vector<vector<int>>& grid, Dir d)
{
    vector<int> v;

    switch (d)
    {
    case n:
        for (int i = row - 1; i >= 0; i--)
        {
            v.push_back(grid[i][column]);
        }
        break;
    case s:
        for (int i = row + 1; i < grid.size(); i++)
        {
            v.push_back(grid[i][column]);
        }
        break;
    case e:
        for (int i = column + 1; i < grid.size(); i++)
        {
            v.push_back(grid[row][i]);
        }
        break;
    case w:
        for (int i = column - 1; i >= 0; i--)
        {
            v.push_back(grid[row][i]);
        }
        break;
    }

    return v;
}