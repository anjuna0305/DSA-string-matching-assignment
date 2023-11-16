#include <iostream>
#include <fstream>

int main()
{
    std::ifstream inputFile{"modules.txt"};

    if (inputFile.is_open())
    {
        std::cout << "error while opening the file" << std::endl;
        return 0;
    }
}