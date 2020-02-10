#include <iostream>
#include <fstream>
#include "Vector.h"
#include <algorithm>
#include <random>

int main()
{
    Vector<std::ofstream> vec;
    vec.push_back(std::ofstream("a.txt"));
    vec.push_back(std::ofstream("b.txt"));
    vec.push_back(std::ofstream("c.txt"));

    std::random_device rd;
    std::shuffle(vec.begin(), vec.end(), rd);
    int i = 0;
    for (std::ofstream &elem : vec)
    {
        elem << i;
        i++;
        elem.close();
    }

    return 0;
}