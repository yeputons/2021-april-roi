#include <iostream>
#include <iterator>
#include <utility>

using std::cout;
using std::pair;
using std::size;

int main() {
    int arr[] = {2, 3, 4, 5};
    constexpr int n = size(arr);
    // до
    {
        int a = -1, b = -1;
        for (int i = 0; i < n && a == -1; i++)
            for (int j = 0; j < n && a == -1; j++)
                if (i != j && arr[i] % arr[j] == 0)
                    a = i, b = j;
        cout << a << " " << b << "\n";
    }
    {
        const auto [a, b] =  // можно сделать переменные константными
            [&]() {  // создали функтор при помощи лямбда-выражения
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (i != j && arr[i] % arr[j] == 0)
                            return pair{i, j};  // не нужны флаги
                return pair{-1, -1};  // не нужны промежуточные переменные
            }();
        cout << a << " " << b << "\n";
    }
}
