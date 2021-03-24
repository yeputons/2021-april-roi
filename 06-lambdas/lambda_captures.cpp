#include <iostream>
#include <utility>
#include <vector>

using std::as_const;
using std::cout;
using std::vector;

int main() {
    {
        int a = 10, b = 20, c = 30;
        auto print_all = [&]() {
            cout << "a=" << a << ", b=" << b << ", c=" << c << "\n";
        };
        print_all();  // a=10, b=20, c=30
        a = 50;
        print_all();  // a=50, b=20, c=30
    }
    cout << "---\n";
    {
        int a = 10, b = 20;
        vector v{1, 2, 3};
        auto print_ab_inc_a = [&a, &b]() {
            cout << a << " " << b << "\n";  // ок, a и b захвачена
            a++;                            // можно менять
            // cout << v.size() << "\n";    // ошибка компиляции
        };
        auto print_10 = [a]() {
            cout << a << "\n";  // всегда 10
            // a++;             // менять нельзя, operator() const
        };
        auto print_10_20 = [=]() {          // то же самое, что [a, b]
            cout << a << " " << b << "\n";  // всегда 10 20
            // cout << v.size() << "\n";    // сделает захват [a, b, v], v скопируется
        };
        print_ab_inc_a();   // 10 20
        cout << a << "\n";  // 11
        a += 100;           // a = 111
        print_ab_inc_a();   // 111 20
        print_10();         // 10
        print_10_20();      // 10 20
    }
    cout << "---\n";
    {
        int a = 10, b = 20;
        vector v{1, 2, 3};
        auto print_a_23_inc_a = [&x = a, y = b + v.size()]() {
            cout << x << " " << y << "\n";  // значение a и 23
            x++;                            // можно менять, изменится a
            // y++;                         // менять нельзя
        };
        auto print_v = [&v = as_const(v)] {       // v не копируется
            cout << v[0] << " " << v[1] << "\n";  // значения из v
            // v = {};                            // нельзя случайно поменять
        };
        print_a_23_inc_a();  // 10 23
        cout << a << "\n";   // 11
        print_v();           // 1 2

        a += 100;              // a = 110
        v = {-1, -2, -3, -4};  // v = {-1, -2, ....}
        print_a_23_inc_a();    // 111 23
        cout << a << "\n";     // 112
        print_v();             // -1 -2
    }
    {
        int a = 10, b = 20;
        vector v{1, 2, 3};
        auto f1 = [=, &v]() {              // [a, &v]
            cout << a << " " << v.size();  // ок
            v = {};                        // ок
            // a++;                        // ошибка компиляции
        };
        auto f2 = [=, &v = as_const(v)]() {  // [a, &cv = as_const(v)]
            cout << a << " " << v.size();    // ок
            // a++;                          // ошибка компиляции
            // v = {};                       // ошибка компиляции
        };
        auto f3 = [&, b, &v = as_const(v)]() {  // [&a, b, &v = as_const(v)]
            cout << a << " " << v.size();       // ок
            a++;                                // ок
            // b++;                             // ошибка компиляции
            // v = {};                          // ошибка компиляции
        };
    }
}
