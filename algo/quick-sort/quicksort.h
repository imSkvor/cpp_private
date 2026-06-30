#pragma once

#include <concepts>
#include <random>
#include <span>
#include <functional>
#include <stdexcept>


template <typename Iter>
    requires std::movable<std::iter_value_t<Iter>>
void IterSwap(Iter first, Iter last) {
    std::swap(*first, *last);
}

template <typename Iter, typename Compare>
concept SortableIterator =
    std::random_access_iterator<Iter> &&
    std::movable<std::iter_value_t<Iter>> &&
    std::predicate<Compare, std::iter_value_t<Iter>, std::iter_value_t<Iter>>;

template <typename Iter>
struct PartitionResult {
    Iter lesser_end;
    Iter equal_end;
};

template <typename Iter, typename Compare>
    requires SortableIterator<Iter, Compare>
PartitionResult<Iter> ThreeWayPartition(Iter first, Iter last, Compare comp) {
    if (first == last) {
        return {first, last};
    }

    Iter pivot_pos = first;
    Iter less = std::next(pivot_pos);
    Iter equal = less;
    Iter greater = last;

    while (equal != greater) {
        if (comp(*equal, *pivot_pos)) {
            IterSwap(equal, less);
            ++less;
            ++equal;
        } else if (comp(*pivot_pos, *equal)) {
            --greater;
            IterSwap(equal, greater);
        } else {
            ++equal;
        }
    }

    IterSwap(pivot_pos, std::prev(less));
    return {std::prev(less), equal};
}

template <typename Iter, typename Compare>
    requires SortableIterator<Iter, Compare>
void QuickSortImpl(Iter first, Iter last, Compare comp, std::mt19937& gen) {
    while (first < last) {
        using DiffType = typename std::iterator_traits<Iter>::difference_type;

        std::uniform_int_distribution<DiffType> dis(0, last - first - 1);
        Iter pivot_pos = first + dis(gen);
        IterSwap(first, pivot_pos);

        auto [less, greater] = ThreeWayPartition(first, last, comp);

        int left_size = less - first;
        int right_size = last - greater;

        if (left_size < right_size) {
            QuickSortImpl(first, less, comp, gen);
            first = greater;
        } else {
            QuickSortImpl(greater, last, comp, gen);
            last = less;
        }
    }
}


// основная реализация, допишем, как обсудим про шаблоны в плюсах
// пока можно оставить как есть
// comp: (T, T) -> bool -- операция сравнения элементов
template <typename T, typename Compare = std::less<T>>
void QuickSort(std::span<T> data, Compare comp = Compare{}) {
    std::mt19937 gen{std::random_device{}()};
    return QuickSortImpl(data.begin(), data.end(), comp, gen);
}

// наивная реализация для интов
// template<>
// void QuickSort<int, std::less<int>>([[maybe_unused]] std::span<int> data, [[maybe_unused]] std::less<int> comp) {
//     throw std::runtime_error{"Not implemented"};
// }
