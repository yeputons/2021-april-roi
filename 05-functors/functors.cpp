#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using std::cout;
using std::set;
using std::sort;
using std::vector;

struct Checker {
    int center;
    bool operator()(int a, int b) const {
        return abs(a - center) < abs(b - center);
    }
};

void print_set(const set<int, Checker> &s) {
    for (int x : s) {
        cout << " " << x;
    }
    cout << "\n";
}

int main() {
    {
        Checker check3;
        check3.center = 2;

        vector v{1, 2, 3};
        sort(begin(v), end(v), check3);
        for (int x : v) {
            cout << " " << x;
        }
        cout << "\n";
    }
    {
        Checker check4{5};                        // check4.center == 5
        set<int, Checker> s1({1, 2, 3}, check4);  // копирование
        cout << "s1:";
        print_set(s1);

        check4.center = 2;
        set<int, Checker> s2({1, 2, 3}, check4);  // копирование
        cout << "s2:";
        print_set(s2);

        s1.insert(4);  // s1 == {4, 3, 2, 1}
        cout << "s1:";
        print_set(s1);

        s2.insert(4);  // s2 == {2, 1, 4}
        cout << "s2:";
        print_set(s2);
    }
}
