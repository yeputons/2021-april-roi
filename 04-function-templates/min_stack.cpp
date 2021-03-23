#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::min;
using std::pair;
using std::string;
using std::vector;

template<typename T>
struct min_stack {
    // .first - data, .second - min_prefix
    vector<pair<T, T>> data;

    void push(const T &val) & {
        if (data.empty()) {
            data.emplace_back(val, val);
        } else {
            data.emplace_back(val, min(val, min_element()));
        }
    }

    void pop() & {
        assert(!data.empty());
        data.pop_back();
    }

    [[nodiscard]] const T &top() const {
        assert(!data.empty());
        return data.back().first;
    }

    [[nodiscard]] const T &min_element() const {
        assert(!data.empty());
        return data.back().second;
    }
};

template<typename T>
void print(const min_stack<T> &s) {
    cout << s.top() << " " << s.min_element() << "\n";
}

int main() {
    {
        min_stack<int> s;
        s.push(10);
        s.push(5);
        s.push(9);
        s.push(4);
        s.push(6);
        print(s);
        s.pop();
        s.pop();
        print(s);
    }

    {
        min_stack<string> s;
        s.push("hello");
        s.push("egor");
        s.push("world");
        print(s);
    }
}
