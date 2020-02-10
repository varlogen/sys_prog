#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <bits/unordered_map.h>
#include "Iterator.h"
#include "Person.h"

void iterTest()
{
    std::vector<int> int_vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::ostream out(std::cout.rdbuf());
    out_iterator<int> iter(2, out, "*");

    std::copy(int_vec.begin(), int_vec.end(), iter);
    std::cout << "\nIterator test passed\n";
}

void perTest()
{
    Person person1{1, "Person_1"};
    Person person2{2, "Person_2"};
    Person person3{3, "Person_3"};
    Person person4{4, "Person_4"};

    std::map<Person, int> map;
    map[person1] = 1;
    map[person2] = 2;
    map[person3] = 3;

    std::unordered_map<Person, int> u_map{};
    u_map.insert({person1, 1});
    u_map.insert({person2, 2});
    u_map[person3] = 3;
    u_map[person3] = 4;

    std::cout << "Person test passed\n";
}

void sortTest()
{
    std::vector<int> vector{1, 5, 3, 2, 10, 3, 11, 4, 12};
    sort(vector.begin(), vector.end());
    for (int elem : vector)
    {
        std::cout << elem << " ";
    }
    std::cout << "\nSort test passed\n";
}

int main()
{
    iterTest();
    perTest();
    sortTest();

    return 0;
}