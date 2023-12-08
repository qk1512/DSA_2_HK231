#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

char caesarEncode(char originalChar, int originalFreq)
{
    if (isupper(originalChar))
    {
        originalChar = char(int(originalChar + originalFreq - 65) % 26 + 65);
    }
    else
    {
        originalChar = char(int(originalChar + originalFreq - 97) % 26 + 97);
    }
    return originalChar;
}

bool comparePairs(pair<char, int> a, pair<char, int> b)
{
    if (a.second != b.second)
    {
        return a.second > b.second;
    }
    else
    {
        if (isupper(a.first) && !isupper(b.first))
            return true;
        else if(!isupper(a.first) && isupper(b.first))
            return false;
        else
            return a.first > b.first;
    }
}

vector<pair<char, int>> string_Processing(string &name)
{
    // TODO: implement string_Processing
    vector<pair<char, int>> freq_prev;
    for (char c : name)
    {
        bool found = false;
        for (pair<char, int> &prev : freq_prev)
        {
            if (prev.first == c)
            {
                prev.second++;
                found = true;
                break;
            }
        }
        if (!found)
        {
            freq_prev.push_back(make_pair(c, 1));
        }
    }

    for (char &c : name)
    {
        int key;
        for (pair<char, int> pair : freq_prev)
        {
            if (pair.first == c)
            {
                key = pair.second;
                break;
            }
        }
        c = caesarEncode(c, key);
    }

    for (pair<char, int> &pair : freq_prev)
    {
        char originalChar = pair.first;
        int originalFreq = pair.second;

        if (isupper(originalChar))
        {
            pair.first = char(int(originalChar + originalFreq - 65) % 26 + 65);
        }
        else
        {
            pair.first = char(int(originalChar + originalFreq - 97) % 26 + 97);
        }
    }

    vector<pair<char, int>> freq;
    for (pair<char, int> pair : freq_prev)
    {
        char currentChar = pair.first;
        int currentFreq = pair.second;

        bool found = false;
        for (std::pair<char, int> &element : freq)
        {
            if (element.first == currentChar)
            {
                element.second += currentFreq;
                found = true;
                break;
            }
        }

        if (!found)
        {
            freq.push_back(make_pair(currentChar, currentFreq));
        }
    }

    sort(freq.begin(),freq.end(),comparePairs);
    return freq;
}

int main(){
    string name = "tlfImdVKjobnHLpuwSLKHJOoF";
    vector<pair<char,int>> freq = string_Processing(name);

    for (const auto &pair : freq)
    {
        std::cout << "{" << pair.first << ", " << pair.second << "}" << " -> ";
    }
    return 0;
}