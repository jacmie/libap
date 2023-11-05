#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace ap
{

bool iequals(const std::string &a, const std::string &b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) { return tolower(a) == tolower(b); });
}

std::vector <std::string> split(std::string input, char delimiter) {  
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);

    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

} // namespace ap

#endif // UTILS_H
