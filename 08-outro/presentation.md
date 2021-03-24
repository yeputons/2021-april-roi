## Осталось за кадром (техника)
Передача лямбда-функций в `min_stack`.
Проблема с ними в том, что нам нужно, с одной стороны указать типа стэка, а с другой — мы не знаем тип компаратора.

К сожалению, вывод шаблонных параметров для классов (C++17) не работает частично:

```c++
min_stack<int> s([](int a, int b) { /* .... */ });
```

Это можно решить при помощи:

* Вывод шаблонных параметров для функций работает частично
* Конструктор `min_stack` со списком инициализации (member initialization list)

Получится так:

```c++
template<typename T, typename Compare>
auto make_min_stack(const Compare &compare) {
    return min_stack<T, Compare>(compare);
}
// ....
auto s = make_min_stack<int>([](int a, int b) { /* .... */ });
```

---

## Осталось за кадром (языковые возможности)
```c++
// хитрые параметры шаблонов:
template <int N>
template <typename T, T x = T{}>
template <template <typename> typename Container, typename T>
template <auto X>
```

```c++
// вариативные шаблоны:
template<typename... Ts>
void print_all_twice(Ts... ts) {
    (cout << ... << ts);
    auto f = [](auto t) {
        cout << t << "\n";
    };
    (f(t), ...)
}
// ....
print_all_twice(1, 23.4);
```

* Шаблоны переменных (C++17), создание своих концептов (C++20)
* Детали structured binding
    * `auto [a, b] = minmax(f(), g());` на самом деле не работает
* SFINAE как предшественник ограничений из C++20

---
## Заключение
* На этом лекция подходит к концу. Я надеюсь, что вам было интересно и полезно.
  * Разве что не надо пытаться применить все эти техники сразу на туре олимпиады, не потренировавшись в спокойной обстановке и не привыкнув.
    Тем более, что не везде есть последние версии компиляторов.
* Наверняка у вас остались вопросы — смело задавайте мне их в личку.
  * Я считаю, что не бывает глупых вопросов, бывают разве что глупые ответы.
* Спасибо за внимание и до новых встреч!