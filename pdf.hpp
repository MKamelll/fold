#pragma once

#include <string>
#include <vector>

class Pdf
{
public:
    Pdf();
    void merge(std::vector<std::string> &files, std::string &outputName);
};

