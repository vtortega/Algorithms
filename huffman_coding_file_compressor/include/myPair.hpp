#include <iostream>

template <typename T, typename U>
class Pair {
public:
    T first;
    U second;

    Pair() : first(), second() {}

    Pair(const T& f, const U& s) : first(f), second(s) {}

    template <typename X, typename Y>
    Pair(const std::pair<X, Y>& other) : first(other.first), second(other.second) {}

    template <typename X, typename Y>
    Pair& operator=(const std::pair<X, Y>& other) {
        first = other.first;
        second = other.second;
        return *this;
    }
};