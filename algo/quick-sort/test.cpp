#include "quicksort.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <vector>
#include <algorithm>
#include <random>
#include <span>
#include <string>
#include <chrono>
#include <iostream>

using Catch::Matchers::Equals;

namespace {

std::vector<int> GenerateRandomVector(size_t size, int min_val, int max_val) {
    std::vector<int> vec(size);
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(min_val, max_val);
    for (auto& x : vec) {
        x = dist(gen);
    }
    return vec;
}

struct MoveOnlyInt {
    int val;
    MoveOnlyInt(int v) : val(v) {}
    
    MoveOnlyInt(const MoveOnlyInt&) = delete;
    MoveOnlyInt& operator=(const MoveOnlyInt&) = delete;
    
    MoveOnlyInt(MoveOnlyInt&& other) noexcept : val(other.val) { other.val = 0; }
    MoveOnlyInt& operator=(MoveOnlyInt&& other) noexcept {
        val = other.val;
        other.val = 0;
        return *this;
    }
    
    bool operator<(const MoveOnlyInt& other) const { return val < other.val; }
    bool operator==(const MoveOnlyInt& other) const { return val == other.val; }
};

struct CustomType {
    int val;
    CustomType(int v) : val(v) {}
    bool operator==(const CustomType& other) const { return val == other.val; }
};

struct CustomGreater {
    bool operator()(const CustomType& a, const CustomType& b) const {
        return a.val > b.val;
    }
};

}

TEST_CASE("Basic Manual Tests") {
    SECTION("Empty and single element") {
        std::vector<int> empty;
        QuickSort(std::span{empty});
        CHECK(empty.empty());

        std::vector<int> single = {42};
        QuickSort(std::span{single});
        CHECK(single == std::vector<int>{42});
    }

    SECTION("Simple ints") {
        std::vector<int> data = {5, 2, 9, 1, 5, 6};
        QuickSort(std::span{data});
        CHECK(data == std::vector<int>{1, 2, 5, 5, 6, 9});
    }
}

TEST_CASE("Edge Cases") {
    const size_t n = 100000;

    SECTION("All elements equal") {
        std::vector<int> data(n, 42);
        QuickSort(std::span{data});
        CHECK(data == std::vector<int>(n, 42));
    }

    SECTION("Already sorted") {
        std::vector<int> data(n);
        std::iota(data.begin(), data.end(), 0);
        QuickSort(std::span{data});
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        CHECK(data == expected);
    }

    SECTION("Reverse sorted") {
        std::vector<int> data(n);
        std::iota(data.rbegin(), data.rend(), 0);
        QuickSort(std::span{data});
        std::vector<int> expected(n);
        std::iota(expected.begin(), expected.end(), 0);
        CHECK(data == expected);
    }
}

TEST_CASE("Comparison with std::sort") {
    std::vector<int> data = GenerateRandomVector(5000, -1000, 1000);
    std::vector<int> expected = data;

    std::sort(expected.begin(), expected.end());
    QuickSort(std::span{data});

    CHECK_THAT(data, Equals(expected));
}

TEST_CASE("Comparator Calls Count") {
    struct CountingLess {
        size_t& count;
        bool operator()(int a, int b) const { 
            ++count; 
            return a < b; 
        }
    };

    const size_t n = 1000;
    std::vector<int> data(n, 42); // Все элементы равны
    size_t comparisons = 0;
    
    QuickSort(std::span{data}, CountingLess{comparisons});

    INFO("Comparisons made: " << comparisons);
    CHECK(comparisons < n * 10); 
}

TEST_CASE("Benchmark") {
    const size_t n = 1000000;
    std::vector<int> data = GenerateRandomVector(n, -1000000, 1000000);
    std::vector<int> data_copy = data;

    auto start_std = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_std = end_std - start_std;

    auto start_qs = std::chrono::high_resolution_clock::now();
    QuickSort(std::span{data_copy});
    auto end_qs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_qs = end_qs - start_qs;

    std::cout << "\n[Benchmark] N = " << n << "\n";
    std::cout << "  std::sort time: " << time_std.count() << " ms\n";
    std::cout << "  QuickSort time: " << time_qs.count() << " ms\n";
    
    CHECK(data == data_copy);
    INFO("std::sort is " << time_qs / time_std << " times faster");
    CHECK(time_qs.count() < time_std.count() * 3.0);
}


// Types and comparator tests

TEST_CASE("Other Types and Comparators", "[advanced]") {
    SECTION("Doubles with std::greater") {
        std::vector<double> data = {3.14, 1.41, 2.71, 0.57};
        QuickSort(std::span{data}, std::greater<double>{});
        CHECK(data == std::vector<double>{3.14, 2.71, 1.41, 0.57});
    }

    SECTION("Strings") {
        std::vector<std::string> data = {"banana", "apple", "cherry", "date"};
        QuickSort(std::span{data});
        CHECK(data == std::vector<std::string>{"apple", "banana", "cherry", "date"});
    }
}

TEST_CASE("Move-only type", "[advanced]") {
    std::vector<MoveOnlyInt> data;
    data.push_back(MoveOnlyInt(5));
    data.push_back(MoveOnlyInt(2));
    data.push_back(MoveOnlyInt(9));
    data.push_back(MoveOnlyInt(1));

    QuickSort(std::span{data});

    std::vector<MoveOnlyInt> expected;
    expected.push_back(MoveOnlyInt(1));
    expected.push_back(MoveOnlyInt(2));
    expected.push_back(MoveOnlyInt(5));
    expected.push_back(MoveOnlyInt(9));

    CHECK(data == expected);
}

TEST_CASE("Type without default std::less", "[advanced]") {
    std::vector<CustomType> data = {CustomType(3), CustomType(1), CustomType(4), CustomType(2)};
    
    QuickSort(std::span{data}, CustomGreater{});

    std::vector<CustomType> expected = {CustomType(4), CustomType(3), CustomType(2), CustomType(1)};
    CHECK(data == expected);
}
