#include <iostream>
#include <vector>
#include <algorithm> // For std::find_if, std::sort
#include <utility>

// Custom comparison function for sorting in descending order
bool comparePairs(const std::pair<char, int> &a, const std::pair<char, int> &b)
{
    if (a.second != b.second)
    {
        // Sort by frequency in descending order
        return a.second > b.second;
    }
    else
    {
        // If frequencies are equal, sort by character (uppercase larger than lowercase)
        return static_cast<int>(a.first) > static_cast<int>(b.first);
    }
}

// Function to accumulate frequencies for the same characters in a vector
std::vector<std::pair<char, int>> accumulateFrequencies(const std::vector<std::pair<char, int>> &freq_prev)
{
    std::vector<std::pair<char, int>> freq;

    for (const auto &pair : freq_prev)
    {
        char currentChar = pair.first;
        int currentFreq = pair.second;

        std::vector<std::pair<char, int>>::iterator it = std::find_if(freq.begin(), freq.end(),
                                                                      [currentChar](const std::pair<char, int> &element)
                                                                      {
                                                                          return element.first == currentChar;
                                                                      });

        if (it != freq.end())
        {
            // If the character is found, update its frequency
            it->second += currentFreq;
        }
        else
        {
            // If the character is not found, add a new pair to the vector
            freq.push_back(std::make_pair(currentChar, currentFreq));
        }
    }

    // Sort the vector in descending order using the custom comparison function
    std::sort(freq.begin(), freq.end(), comparePairs);

    return freq;
}

int main()
{
    // Example usage
    std::vector<std::pair<char, int>> frequencyVector = {{'b', 1}, {'C', 2}, {'b', 2}, {'C', 1}};

    // Display the original vector
    std::cout << "Original Vector: ";
    for (const auto &pair : frequencyVector)
    {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }

    // Accumulate frequencies for the same characters
    std::vector<std::pair<char, int>> accumulatedVector = accumulateFrequencies(frequencyVector);

    // Display the accumulated and sorted vector
    std::cout << "\nAccumulated and Sorted Vector: ";
    for (const auto &pair : accumulatedVector)
    {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }

    return 0;
}
