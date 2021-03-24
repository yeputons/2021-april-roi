#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::set;
using std::vector;

template <typename Container>
auto sum_all(const Container &c) {
    auto res = 0;
    for (const auto &val : c) {
        res += val;
    }
    return res;
}

int main() {
    cout << sum_all(vector{1, 2, 3, 4}) << "\n";  // 0 + 1 + 2 + 3 + 4 == 10
    cout << sum_all(vector{1.75, 2.75}) << "\n";  // 0 + (int) 1.75 + (int) 2.75 == 3
    cout << sum_all(set{1, 1, 4}) << "\n";        // 0 + 1 + 4 == 5
}
