## Структура данных "стек с минимумом"
Теперь давайте приступим к обобщённому программированию структур данных.

```
  #   Значения   Минимум вниз

       |    |      |    |
  4    |  6 |      |  4 |  <--- верхушка стека
  3    |  4 |      |  4 |
  2    |  9 |      |  5 |
  1    |  5 |      |  5 |
  0    | 10 |      | 10 |
       +----+      +----+
```

После двух операций `pop()`:
```
  #   Значения   Минимум вниз

       |    |      |    |
  2    |  9 |      |  5 |  <--- верхушка стека
  1    |  5 |      |  5 |
  0    | 10 |      | 10 |
       +----+      +----+
```

---
## Желаемая реализация
```c++
// можно хранить так
vector<int> data      {10, 5, 9, 4, 6};
vector<int> min_prefix{10, 5, 5, 4, 4};

// или так
vector<pair<int, int>> data{
    {10, 10}, {5, 5}, {9, 5},
    {4, 4}, {6, 4};
};

// но хочется так повысить уровень абстракции и упростить код
min_stack<int> s;
s.push(10);
s.push(5);
s.push(9);
s.push(4);
s.push(6);
cout << s.top() << " " << s.min_element() << "\n";  // 6 4
s.pop();
s.pop();
cout << s.top() << " " << s.min_element() << "\n";  // 9 5
```

---
## Создаём структуру (класс)
```c++
struct min_stack {
    // .first - data, .second - min_prefix
    vector<pair<int, int>> data;
};
// ....
void print(const min_stack &s) {
    cout << s.data.back().first << " " << s.data.back().second << "\n";
}
int main() {
    min_stack s;
    s.data.emplace_back(10, 10);  // push_back(pair(/* .... */))
    s.data.emplace_back(5, 5);
    s.data.emplace_back(9, 5);
    s.data.emplace_back(4, 4);
    s.data.emplace_back(6, 4);
    print(s);  // 6 4
    s.data.pop_back();
    s.data.pop_back();
    print(s);  // 9 5
}
```

---
## Добавляем методы
```c++
struct min_stack {
    // .first - data, .second - min_prefix
    vector<pair<int, int>> data;

    // похоже на обычную функцию, может обращаться к data напрямую
    void push(int val) & {  // & — lvalue-ref-qualifier (C++11)
        if (data.empty()) {  // не нужен self, как в Python
            data.emplace_back(val, val);
        } else {
            data.emplace_back(val, min(val, data.back().second));
        }
    }

    void pop() & {  // & — lvalue-ref-qualifier (C++11)
        data.pop_back();
    }
};
// ....
    min_stack s;
    s.push(10);  // s.data.emplace_back(10, 10);
    // ....
    print(s);
    s.pop();     // s.data.pop_back();
    // ....
```


---
## Добавляем методы для чтения
```c++
struct min_stack {
    // ....
    void push(int val) & {
        if (data.empty()) {
            data.emplace_back(val, val);
        } else {
            data.emplace_back(val, min(val, min_element()));  // !
        }
    }

    [[nodiscard]] int top() const {  // const-qualifier
        return data.back().first;
    }

    [[nodiscard]] int min_element() const {  // const-qualifier
        return data.back().second;
    }
    // ....
};
void print(const min_stack &s) {
    cout << s.top() << " " << s.min_element() << "\n";
}
...
```

---
## Контроль доступа
Теперь нигде за пределами `min_stack` не используется `data`, `first`, `second`.
Значит, что ошибиться мы можем теперь либо при использовании,
либо внутри `min_stack`, но тогда он сломается сразу везде и это легко поймать.

```c++
struct min_stack {
private:
    vector<pair<int, int>> data;

public:
    void push(int val) & { /* .... */ }

    void pop() & { /* .... */ }

    [[nodiscard]] int top() const {  /* .... */ }

    [[nodiscard]] int min_element() const {  /* .... */ }
};
// ....
s.data.back().first;  // ошибка доступа к s.data
s.top();              // ок
```

---
## assert для отладки
Можем добавить проверки во все использования `min_stack`
одновременно:

```c++
    [[nodiscard]] int top() const {
        assert(!data.empty());  // (!)
        return data.back().first;
    }

    [[nodiscard]] int min_element() const {
        assert(!data.empty());  // (!)
        return data.back().second;
    }

    void pop() & {
        assert(!data.empty());  // (!)
        data.pop_back();
    }
```

Если какой-то `assert` вызвать с ложным утверждением,
программа с грохотом упадёт.
