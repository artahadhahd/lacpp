#include "mat.hpp"
#include <iostream>

int main() {


    // Vec3<int> vec{ {1, 2, 3} };

    Mat2x2<int> a({1, 2, 3, 4});
    Mat2x2<int> b({5, 6, 7, 8});
    // std::cout << a[0] + std::array<int, 2>{1, 2};
    // a.at(0) *= 2;
    std::cout << a[0];
    // a += b;
}