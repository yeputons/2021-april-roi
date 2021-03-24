#include <concepts>
#include <iostream>

using std::cout;
using std::invocable;

template <typename Fn>
requires invocable<Fn, int>
void call_10_20_30(Fn fn) {
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
