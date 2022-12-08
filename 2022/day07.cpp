// day07.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <algorithm>

using namespace std;

struct file
{
    string name = "";
    int size = 0;
    bool listed = false;
    file* parentfile;
    vector<file> files;
};

vector<string> tokenizeString(string s);
bool parseInputString(string s);
void changeDirectory(string dir);
void list();
file createFile(string name, file* parentFile, int size = 0);
int calculateSizes(file topdir);
int findFileToDelete(int minsize);

file root;
file* current;
ifstream input;
vector<int> dsizes;
int sum = 0;

int main()
{
    const int DISKSPACE = 70000000;
    const int UPDATESIZE = 30000000;

    input.open("day07.txt");
    string line;

    try
    {
        if (!input)
        {
            throw runtime_error("Could not open file");
        }
        while (getline(input, line))
        {
            if (!parseInputString(line))
            {
                cout << "Bad input\n";
                return 0;
            }
        }
    }
    catch (exception e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
        return 1;
    }

    root.size = calculateSizes(root);

    cout << "Sum: " << sum << endl;

    int available = DISKSPACE - root.size;

    if (available < UPDATESIZE)
    {
        // We don't need to know *which* file, just how big it is....
        cout << "Smallest directory to free space: " << findFileToDelete(UPDATESIZE - available) << endl;
    }

    input.close();
    return 0;
}

/// <summary>
/// Finds the size of the smallest directory that will free up enough space for an update
/// </summary>
/// <param name="minsize">Size of the update</param>
/// <returns>Size of the smallest directory</returns>
int findFileToDelete(int minsize)
{
    sort(dsizes.begin(), dsizes.end());

    for (int i = 0; i < dsizes.size(); i++)
    {
        if (dsizes[i] > minsize)
        {
            return dsizes[i];
        }
    }
    return -1;
}

/// <summary>
/// Calculates the size of a file
/// </summary>
/// <param name="f">File to calculate</param>
/// <param name="sum">Reference variable to track the running size sum of 100000+ size files</param>
/// <returns>Size of current file</returns>
int calculateSizes(file f)
{
    if (!f.files.size() == 0)
    {
        for (int i = 0; i < f.files.size(); i++)
        {
            f.size += calculateSizes(f.files[i]);
        }
        if (f.size <= 100000)
        {
            sum += f.size;
        }
    }
    dsizes.push_back(f.size);
    return f.size;
}

/// <summary>
/// Parses an input string
/// </summary>
/// <param name="s">String to parse</param>
/// <returns>Whether the string was successfully parsed</returns>
bool parseInputString(string s)
{
    vector<string> parsedline;

    parsedline = tokenizeString(s);

    if (parsedline.size() < 1)
    {
        return false;
    }
    if (parsedline[0] == "$")   // Command detected
    {
        string cmd = parsedline[1];

        if (cmd == "cd")
        {
            changeDirectory(parsedline[2]);
            return true;
        }
        if (cmd == "ls")
        {
            list();
            return true;
        }
    }
    cout << "Invalid command\n";
    return false;
}

/// <summary>
/// Changes the current directory
/// </summary>
/// <param name="dir">New directory</param>
void changeDirectory(string dir)
{
    if (dir == "..")                              // Return to parent directory
    {
        current = current->parentfile;
    }
    else if (dir == "/")                          // Initial setup or return home
    {
        current = &root;
    }
    else
    {
        for (int i = 0; i < current->files.size(); i++)
        {
            if (dir == current->files[i].name)    // Directory already exists
            {
                current = &current->files[i];
                return;                                // Command success
            }
        }

        // Create new directory
        current->files.push_back(createFile(dir, current));
        return;
    }
}

/// <summary>
/// Populates the file vector if this is the first time a file has been listed
/// </summary>
void list()
{
    // List command functionally initializes the file vector, only needs to happen once
    if (current->listed)
    {
        return;
    }

    vector<string> v;
    string line;

    while (input.peek() != '$' && input.peek() != EOF) // Read until next command
    {
        getline(input, line);
        v = tokenizeString(line);

        if (v.size() < 1)
        {
            cout << "Empty list\n";
            return;
        }

        // Check for file or directory listing
        if (v[0] == "dir")
        {
            current->files.push_back(createFile(v[1], current));
        }
        else
        {
            current->files.push_back(createFile(v[1], current, stoi(v[0])));
        }
    }
}

/// <summary>
/// Initialize a new file struct
/// </summary>
/// <param name="name">Name of the file</param>
/// <param name="parentFile">File's parent</param>
/// <param name="size">Size of the file</param>
/// <returns>Newly created file</returns>
file createFile(string name, file* parentFile, int size)
{
    file newfile;
    newfile.name = name;
    newfile.size = size;
    newfile.parentfile = parentFile;
    return newfile;
}

/// <summary>
/// Tokenizes a string separated by spaces
/// </summary>
/// <param name="s">String to tokenize</param>
/// <returns>Vector containing individual words</returns>
vector<string> tokenizeString(string s)
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