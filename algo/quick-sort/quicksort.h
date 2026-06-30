#pragma once

#include <span>
#include <functional>
#include <stdexcept>


// основная реализация, допишем, как обсудим про шаблоны в плюсах
// пока можно оставить как есть
// comp: (T, T) -> bool -- операция сравнения элементов
template <typename T, typename Compare = std::less<T>>
void QuickSort([[maybe_unused]] std::span<T> data, [[maybe_unused]] Compare comp = Compare{}) {
    throw std::runtime_error{"Not implemented"};
}

// наивная реализация для интов
template<>
void QuickSort<int, std::less<int>>([[maybe_unused]] std::span<int> data, [[maybe_unused]] std::less<int> comp) {
    throw std::runtime_error{"Not implemented"};
}