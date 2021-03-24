#include <cmath>
#include <iostream>

using std::abs;
using std::cout;

template<typename Fn>
struct Caller {
    Fn fn;  // храним функтор как поле, тип берем из шаблона
    int x;
    void call() {
        fn(x);
    }
};

int main() {
    struct PrintDistanceTo {  // функтор
        int center;
        void operator()(int x) const {
            cout << abs(x - center) << "\n";
        }
    };
    Caller<PrintDistanceTo> c;
    c.fn = PrintDistanceTo{10};
    c.x = 50;
    c.call();  // 40
}
