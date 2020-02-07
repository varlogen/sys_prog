#include<gtest/gtest.h>
#include "../src/z3/Functions.h"

TEST(Message, Compare) {
    std::stringstream stream;
    message(stream, "% + % = %", 2, 'a', 3.2);
    EXPECT_EQ(stream.str(), "2 + a = 3.2");
}

TEST(Cat, Compare) {
    std::array<int, 3> arr1{1, 2, 3};
    std::array<int, 3> arr2{4, 5, 6};
    std::array<int, 3> arr3{7, 8, 9};
    std::array<int, 3> arr4{10, 11, 12};
    std::array<int, 12> newArr = cat(arr1 ,arr2, arr3, arr4);
    std::array<int, 12> targetArr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(newArr, targetArr);
}

TEST(Tie, Compare) {
    std::array<int, 2> array1{1, 2};
    std::array<int, 2> array2{3, 4};
    std::array<int, 4> newArr{10, 20, 30, 40};
    tie(array1, array2) = newArr;
    std::array<int, 2> targetArr1{10, 20};
    std::array<int, 2> targetArr2{30, 40};
    EXPECT_EQ(array1, targetArr1);
    EXPECT_EQ(array2, targetArr2);
}
