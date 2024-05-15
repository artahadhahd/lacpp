#ifndef LACPP_MAT_HPP
#define LACPP_MAT_HPP
#include "vec.hpp"
#include <cstdint>
#include <array>

template <typename T, size_t X, size_t Y>
struct Mat {    
    using Container = std::array<T, X * Y>;
    static constexpr size_t size = X * Y;
    Container values {0};

    template<typename U = float>
    U average() const {
        return sum<U>() / U(size);
    }

    template<typename U = T>
    U sum() const {
        U result;
        for (size_t i = 0; i < size; ++i) {
            result += values[i];
        }
        return result;
    }

    Vec<T, X> const operator[](size_t const index) const {
        auto vec = Vec<T, X>::Zeros;
        std::copy(values.begin() + X * index, values.begin() + X * (index + 1), vec.begin());
        return vec;
    }

    Vec<T, X>& at(size_t const index) const {
        auto vec = Vec<T, X>::Zeros;
        std::copy(values.begin() + X * index, values.begin() + X * (index + 1), vec.begin());
        return vec;
    }

    Vec<T, Y> operator()(size_t const index) const {
        auto vec = Vec<T, Y>::Zeros;
        std::copy(values.begin() + Y * index, values.begin() + Y * (index + 1), vec.begin());
        return vec;
    }

    Mat& operator+=(Mat const& mat) {
        for (size_t i = 0; i < size; ++i) {
            values[i] += mat.values[i];
        }
        return *this;
    }

    friend Mat operator+(Mat lhs, Mat const& rhs) {
        lhs += rhs;
        return lhs;
    }

    Mat& operator*=(T const scalar) {
        for (size_t i = 0; i < size; ++i) {
            values[i] *= scalar;
        }
    }

    friend Mat operator/(Mat lhs, T const& rhs) {
        lhs *= rhs;
        return lhs;
    }

    const T* begin() { return values.begin(); };
    const T* end() { return values.end(); }
};

template<typename T>
using Mat2x2 = Mat<T, 2, 2>;

#endif