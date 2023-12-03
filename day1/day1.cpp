// Online C++ compiler to run C++ program online
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>

std::map<std::string, std::string> digit_lookup = { {"one","o1e"}, {"two","t2o"} , {"three","t3e"}, {"four","f4r"},
    {"five","f5e"}, {"six","s6x"}, {"seven","s7n"}, {"eight","e8t"}, {"nine","n9e"}};

void replace_all(std::string& line,
    std::string const& toReplace,
    std::string const& replaceWith) 
{
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(line.size());

    while (true) {
        prevPos = pos;
        pos = line.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(line, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(line, prevPos, line.size() - prevPos);
    line.swap(buf);
}

std::string getFirstLastDigits(std::string line)
{
    std::string first_last = "";
    line.erase(std::remove_if(line.begin(), line.end(),
        [](auto const c) -> bool { return !std::isdigit(c); }), line.end());
    first_last += line.front();
    first_last += line.back();
    
    std::cout << first_last << std::endl;
    return first_last;
}

int main()
{
    std::ifstream infile("input.txt");
    std::string line;
    int total = 0;
    int i = 0;
    while (std::getline(infile, line))
    {
        //std::cout << line << std::endl;
        for (auto const & digit : digit_lookup)
        {
            replace_all(line, digit.first, digit.second);
        }
        std::cout << line << std::endl;
        
        total += std::stoi(getFirstLastDigits(line));
        line.clear();

    }
    std::cout << total << std::endl;
    return 0;
}
