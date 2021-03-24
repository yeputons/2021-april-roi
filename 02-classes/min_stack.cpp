#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::min;
using std::pair;
using std::vector;

struct min_stack {
private:
    // .first - data, .second - min_prefix
    vector<pair<int, int>> data;

public:
    void push(int val) & {
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

    [[nodiscard]] int top() const {
        assert(!data.empty());
        return data.back().first;
    }

    [[nodiscard]] int min_element() const {
        assert(!data.empty());
        return data.back().second;
    }
};

void print(const min_stack &s) {
    cout << s.top() << " " << s.min_element() << "\n";
}

int main() {
    min_stack s;
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
