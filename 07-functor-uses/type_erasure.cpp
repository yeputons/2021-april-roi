#include <functional>
#include <iostream>
#include <vector>

using std::cout;
using std::function;
using std::vector;

int main() {
    vector<function<void(int)>> v{[x = 10](int y) { cout << x + y << "\n"; },
                                  [x = 20](int y) { cout << x + y << "\n"; }};
    for (const auto &f : v) {
        f(5);  // 15, 25
    }
}
