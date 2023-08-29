#include <iostream>
#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "Polynomial.cpp"

TEST(functionTest, resultTest) {
    int arr[3] = {5, 4, 3};
    Polynomial<3> pol(arr);
    EXPECT_EQ(pol(1), 12);
}

TEST(functionTest1, resultTest) {
    int arr[3] = {5, 4, 3};
    Polynomial<3> pol(arr);
    EXPECT_EQ(pol(2), 25);
}

TEST(functionTest2, resultTest) {
    int arr[3] = {5, 4, 3};
    Polynomial<3> pol(arr);
    EXPECT_EQ(pol(2), 20); // правильный ответ 25
}

int main() {
    testing::InitGoogleTest();
    std::cout << "Hello, World!" << std::endl;
    constexpr int arr[3] = {5, 4, 3};
    constexpr Polynomial<3> pol(arr);
    static_assert(pol(1) == 12);
    return RUN_ALL_TESTS();
}
