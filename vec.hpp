#ifndef LACPP_VEC_HPP
#define LACPP_VEC_HPP
#include <array>
#include <cstdint>
#include <iostream>
#include <functional>
#include <cmath>
#include <string>
#include <sstream>

template<typename T, size_t N>
struct Vec {
    using Container = std::array<T, N>;
    Container values = {0};
    Vec(Container values) : values(values) {}
    Vec(){}

    static constexpr Container Zeros{{0}};

    template <typename U = float>
    U average() const {
        return U(sum()) / U(N);
    }

    template <typename U = T>
    U sum() const {
        U result;
        for (size_t i = 0; i < N; ++i) {
            result += get(i);
        }
        return result;
    }

    static T dot(Vec lhs, const Vec& rhs)
    {
        for (size_t i = 0; i < N; ++i) {
            lhs[i] = lhs[i] * rhs[i];
        }
        return lhs.sum();
    }

    // https://en.wikipedia.org/wiki/Norm_(mathematics)#p-norm
    long double norm(uint32_t p = N) const
    {
        T sum {0};
        for (auto const num : values) {
            sum += std::pow(num, 3.0);
        }
        return std::pow(sum, 1.0 / p);
    }

    Vec& operator+=(const Vec& rhs) {
        for (size_t i = 0; i < N; ++i) {
            values[i] += rhs[i];
        }
        return *this;
    }

    friend Vec operator+(Vec lhs, Vec const& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    Vec& operator-=(const Vec& rhs) {
        for (size_t i = 0; i < N; ++i) {
            values[i] -= rhs[i];
        }
        return *this;
    }

    friend Vec operator-(Vec lhs, const Vec& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend T operator*(Vec lhs, Vec const& rhs) {
        return dot(lhs, rhs);
    }

    Vec& operator*=(T const scalar)
    {
        for (size_t i = 0; i < N; ++i) {
            values[i] *= scalar;
        }
        return *this;
    }

    friend Vec operator*(Vec lhs, T const& scalar)
    {
        lhs *= scalar;
        return lhs;
    }

    Vec& operator/=(T const scalar)
    {
        for (size_t i = 0; i < N; ++i) {
            values[i] /= scalar;
        }
        return *this;
    }

    friend Vec operator/(Vec lhs, T const& scalar)
    {
        lhs /= scalar;
        return lhs;
    }

    T& operator[](size_t const index) {
        return values[index];
    }

    T const& operator[](size_t const index) const {
        return values[index];
    }

    T get(size_t const index) const {
        return values[index];
    }

    Vec for_each(std::function<void(T&)> func) {
        for (size_t i = 0; i < N; ++i) {
            func(values[i]);
        }
        return std::move(*this);
    }

    friend std::ostream& operator<<(std::ostream& os, Vec const& vec) {
        os << "[ ";
        for (size_t i = 0; i < N; ++i) {
            os << vec[i] << ' ';
        }
        os << ']';
        return os;
    }

    const T* begin() const { return values.begin(); }
    const T* end() const { return values.end(); };
};

template<typename T>
using Scalar = Vec<T, 1>;
template <typename T>
using Vec2 = Vec<T, 2>;
template <typename T>
using Vec3 = Vec<T, 3>;
template <typename T>
using Vec4 = Vec<T, 4>;

#endif