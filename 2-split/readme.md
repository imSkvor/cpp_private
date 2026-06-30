# Split

Реализуйте функцию `Split(string, delimiter)`, которая разбивает строку `string` на подстроки по заданному разделителю `delimiter` (по умолчанию пробел). Например,
```
Split("just a test", " ") = {"just", "a", "test"}
```
Обратите внимание, что функция должна корректно обрабатывать случаи, когда два разделителя следуют подряд --- в этом случае
в ответ в этом месте пойдет пустая строка.

### Примечания
* Постарайтесь не использовать строку-накопитель в решении. Вместо этого используйте методы
[find](https://en.cppreference.com/w/cpp/string/basic_string/find) и [substr](https://en.cppreference.com/w/cpp/string/basic_string/substr).
* Обратите внимание, на специальную константу `std::string::npos`. Как она используется?
* Запрещено использование [std::views::split](https://en.cppreference.com/w/cpp/ranges/split_view) и [std::views::lazy_split](https://en.cppreference.com/w/cpp/ranges/lazy_split_view)
