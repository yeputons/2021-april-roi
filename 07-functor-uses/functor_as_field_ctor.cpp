#include <cmath>
#include <iostream>

using std::abs;
using std::cout;

template <typename Fn>
struct Caller {
    Fn fn;  // храним функтор как поле, тип берем из шаблона
    int x;
    void call() {
        fn(x);
    }
    Caller(const Fn &fn_)  // специальный метод для инициализации
        : fn(fn_) {        // инициализирует поле fn копированием
    }
};

int main() {
    struct PrintDistanceTo {  // функтор
        int center;
        void operator()(int x) const {
            cout << abs(x - center) << "\n";
        }
    };
    Caller c{[](int x) { cout << x << "\n"; }};
    c.x = 50;
    c.call();  // 50
}
