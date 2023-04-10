#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>

int main()
{
    std::ifstream file("example.txt");
    std::map<char, int> char_count;

    char c;
    while (file.get(c))
    {
        if (char_count.find(c) != char_count.end())
            char_count[c]++;
        else
            char_count[c] = 1;
    }

    int total_count = 0;
    for (auto& p : char_count)
        total_count += p.second;

    std::cout << "Character statistics:\n";
    for (auto& p : char_count)
    {
        std::cout << "'" << p.first << "': " << p.second << " ("
            << std::fixed << std::setprecision(2)
            << static_cast<double>(p.second) / total_count * 100 << "%)\n";
    }
    return 0;
}