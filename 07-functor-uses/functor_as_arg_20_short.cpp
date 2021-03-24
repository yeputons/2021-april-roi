#include <concepts>
#include <iostream>

using std::cout;
using std::invocable;

// template<invocable<int> Fn>
// void call_10_20_30(Fn fn) {
void call_10_20_30(invocable<int> auto fn) {
    fn(10);
    fn(20);
    fn(30);
}

int main() {
    call_10_20_30([](int x) {  // 10, 20, 30
        cout << x << "\n";
    });
    // call_10_20_30([](){});  // одна ошибка компиляции
}
