/*
Philipp Schmid: 5703070
Max Staneker: 7018590
*/
#pragma once
#include <vector>
#include <functional>

// TODO 7.1.a: Implement the square function
template<typename T>
T square(T x) {
    return x * x;
}

// TODO 7.1.b: Implement the halve function
template<typename T>
double halve(T x) {
    return static_cast<double>(x) / 2.0;
}

// TODO 7.1.c: Implement the add function
template<typename T>
T add(T a, T b) {
    return a + b;
}

// TODO 7.1.d: Implement the multiply function
template<typename T>
T multiply(T a, T b) {
    return a * b;
}

// TODO 7.1.e: Implement the reduce function
template<typename T>
T reduce(std::function<T(T,T)> operation, const std::vector<T>& values, T neutral) {
    T result = neutral;
    for (std::size_t i = 0; i < values.size(); ++i) {
        result = operation(result, values[i]);
    }
    return result;
}

// TODO 7.1.f: Implement the map function
template<typename T> 
std::vector<T> map(std::function<T(T)> func, const std::vector<T>& values) {
    std::vector<T> result;
    for (std::size_t i = 0; i < values.size(); ++i) {
        result.push_back(func(values[i]));
    }
    return result;
}
