#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::greater;
using std::less;
using std::min;
using std::pair;
using std::string;
using std::vector;

template <typename T, typename Compare = less<T>>
struct min_stack {
private:
    // .first - data, .second - min_prefix
    vector<pair<T, T>> data;

public:
    Compare compare;

    void push(const T &val) & {
        if (data.empty()) {
            data.emplace_back(val, val);
        } else {
            data.emplace_back(val, min(val, min_element(), compare));
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

template <typename T, typename Compare>
void print(const min_stack<T, Compare> &s) {
    cout << s.top() << " " << s.min_element() << "\n";
}

struct CloserToCenter {
    int center;
    bool operator()(int a, int b) const {
        return abs(a - center) < abs(b - center);
    }
};

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
        min_stack<int, greater<int>> s_gr;
        s_gr.push(-10);
        s_gr.push(-5);
        s_gr.push(-9);
        s_gr.push(-4);
        s_gr.push(-6);
        print(s_gr);
        s_gr.pop();
        s_gr.pop();
        print(s_gr);
    }

    {
        min_stack<int, CloserToCenter> s_gr;
        s_gr.compare.center = 4;
        s_gr.push(1);
        s_gr.push(2);
        s_gr.push(3);
        s_gr.push(4);
        s_gr.push(5);
        print(s_gr);
        s_gr.pop();
        s_gr.pop();
        print(s_gr);
    }
}
