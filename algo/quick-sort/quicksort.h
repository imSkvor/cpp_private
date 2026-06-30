#pragma once

#include <span>
#include <functional>
#include <stdexcept>


// основная реализация, допишем, как обсудим про шаблоны в плюсах
// пока можно оставить как есть
// comp: (T, T) -> bool -- операция сравнения элементов
template <typename T, typename Compare = std::less<T>>
void QuickSort(std::span<T> data, Compare comp = Compare{}) {
    throw std::runtime_error{"Not implemented"};
}

// наивная реализация для интов
template<>
void QuickSort<int, std::less<int>>(std::span<int> data, std::less<int> comp) {
    throw std::runtime_error{"Not implemented"};
}