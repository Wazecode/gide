#pragma once
#include <string>


class Search
{
public:
    Search();
    std::string findAll(std::string searchTerm, std::string content);
private:
    bool isPrefix(std::string word, int len, int pos);
    int suffixLen(std::string word, int len, int pos);
    bool isAsciiStr(std::string s);
};

