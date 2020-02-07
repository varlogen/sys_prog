#include "Functions.h"

void msgTest(){
    message(std::cout, "% + % = %", 2, 'a', 3.2);
    std::cout << "\n";
}

void catTest(){
    std::array<int, 3> arr1{1, 2, 3};
    std::array<int, 3> arr2{4, 5, 6};
    std::array<int, 3> arr3{7, 8, 9};
    std::array<int, 3> arr4{10, 11, 12};
    std::array<int, 12> arr5 = cat(arr1 ,arr2, arr3, arr4);
    for (auto x : arr5){
        std::cout << x << " ";
    }
    std::cout << "\n";
}

void tieTest(){
    std::array<int, 4> array1{1, 2, 3, 4};
    std::array<int, 4> array2{10, 20, 30, 40};
    std::array<int, 8> array3{100, 200, 300, 400, 4, 5, 6, 19};
    tie(array1, array2) = array3;
}

int main() {
    msgTest();
    catTest();
    tieTest();
    return 0;
}
