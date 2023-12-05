#include <iostream>
#include <vector>
#include <algorithm> // For find_if
#include <utility>
using namespace std;

// Function to accumulate frequencies for the same characters in a vector
vector<pair<char, int>> accumulateFrequencies(const vector<pair<char, int>> &freq_prev)
{
    vector<pair<char, int>> accumulatedFreq;

    for (const auto &pair : freq_prev)
    {
        char currentChar = pair.first;
        int currentFreq = pair.second;

        // Explicitly specify the iterator type
        vector<std::pair<char, int>>::iterator it = find_if(accumulatedFreq.begin(), accumulatedFreq.end(),
                                                                      [currentChar](const std::pair<char, int> &element)
                                                                      {
                                                                          return element.first == currentChar;
                                                                      });

        if (it != accumulatedFreq.end())
        {
            // If the character is found, update its frequency
            it->second += currentFreq;
        }
        else
        {
            // If the character is not found, add a new pair to the vector
            accumulatedFreq.push_back(make_pair(currentChar, currentFreq));
        }
    }

    return accumulatedFreq;
}

int main()
{
    // Example usage
    vector<pair<char, int>> frequencyVector = {{'A', 5}, {'B', 3}, {'C', 2}, {'A', 2}};

    // Display the original vector
    cout << "Original Vector: ";
    for (const auto &pair : frequencyVector)
    {
        cout << "(" << pair.first << "," << pair.second << ") ";
    }

    // Accumulate frequencies for the same characters
    vector<pair<char, int>> accumulatedVector = accumulateFrequencies(frequencyVector);

    // Display the accumulated vector
    cout << "\nAccumulated Vector: ";
    for (const auto &pair : accumulatedVector)
    {
        cout << "(" << pair.first << "," << pair.second << ") ";
    }

    return 0;
}
