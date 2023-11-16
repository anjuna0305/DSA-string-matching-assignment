#include <iostream>
#include <typeinfo>
#include <limits>
#include <fstream>
#include <string>

// convert string to lovercase
void convertToLowerCase(std::string &inputString)
{
    for (int i = 0; i < inputString.length(); i++)
    {
        inputString[i] = std::tolower(inputString[i]);
    }
}

// take pattern from user as standard input
std::string inputPattern()
{
    std::string inputPattern;
    while (true)
    {
        std::cout << "enter string pattern : ";
        if (std::cin >> inputPattern)
            break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "invalid input!" << std::endl;
    }

    convertToLowerCase(inputPattern);
    return inputPattern;
}

// preprocessing: calculate shift table
void calculateShiftTableTable(int shiftTable[256], std::string pattern)
{
    for (int i = 0; i < 256; ++i)
        shiftTable[i] = pattern.length();

    for (int i = 0; i < pattern.length() - 1; ++i)
        shiftTable[static_cast<int>(pattern[i])] = pattern.length() - i - 1;
}

// implementation of horspool algo
int stringMatcher(std::string text, std::string pattern, int shiftTable[256])
{
    int position = 0;
    int numberOfMatches = 0;

    while (position + pattern.length() <= text.length())
    {
        for (int i = pattern.length() - 1; i >= 0; i--)
        {
            if (pattern[i] != text[position + i])
            {
                position += shiftTable[static_cast<int>(text[position + pattern.length() - 1])];
                break;
            }
            if (i == 0)
            {
                // match found
                numberOfMatches++;
                position += 1;
            }
        }
    }
    return numberOfMatches;
}

int main()
{
    int shiftTable[256];
    std::string pattern, text;
    int totalmatches = 0;

    std::ifstream inputFile{"modules.txt"};

    if (!inputFile.is_open())
    {
        std::cout << "error while opening the file" << std::endl;
        return 0;
    }

    pattern = inputPattern();
    calculateShiftTableTable(shiftTable, pattern);

    while (std::getline(inputFile, text))
    {
        convertToLowerCase(text);
        totalmatches += stringMatcher(text, pattern, shiftTable);
    }
    inputFile.close();

    std::cout << "total matches : " << totalmatches << std::endl;
    return 0;
}