#include <concepts>
#include <iostream>
#include <type_traits>

using std::cout;
using std::invocable;
using std::is_same_v;

// хитрые параметры шаблонов:
template <int N>
struct S1 {};

template <typename T, T x = T{}>
struct S2 {};

template <template <typename> typename Container, typename T>
struct S3 {};

template <auto X>
struct S4 {};

// вариативные шаблоны:
template <typename... Ts>
void print_all_twice(Ts... ts) {
    (cout << ... << ts) << "\n";
    auto f = [](auto t) { cout << t << "\n"; };
    (f(ts), ...);
}

// шаблоны переменных
template <typename T>
T is_int_v = is_same_v<T, int>;

int main() {
    print_all_twice(1, 23.4);
    cout << "is_int_v<int>=" << is_int_v<int> << "\n";
    cout << "is_int_v<int>=" << is_int_v<float> << "\n";
}
