#include "rotate.h"
#include "utils.h"

#include <vector>
#include <algorithm>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;

TEST_CASE("Simple") {
    {
        std::vector test = {1, 4, 3, 2, 6, 7, 0};
        std::vector expected = {3, 2, 6, 7, 0, 1, 4};
        Rotate(&test, 2);
        CHECK_THAT(test, Equals(expected));
    }
    {
        std::vector test = {2, 1, 3, 5};
        std::vector expected = {5, 2, 1, 3};
        Rotate(&test, 3);
        CHECK_THAT(test, Equals(expected));
    }
    {
        std::vector test = {1, 2};
        std::vector expected = {1, 2};
        Rotate(&test, 0);
        CHECK_THAT(test, Equals(expected));
    }
    {
        std::vector test = {1, 2, 3};
        std::vector expected = {1, 2, 3};
        Rotate(&test, 3);
        CHECK_THAT(test, Equals(expected));
    }
}

TEST_CASE("Empty") {
    {
        std::vector<int> test;
        Rotate(&test, 0);
        CHECK(test.empty());
    }
    {
        std::vector test = {0};
        std::vector expected = {0};
        Rotate(&test, 1);
        CHECK_THAT(test, Equals(expected));
    }
}

TEST_CASE("Big") {
    constexpr auto kSize = 1'000'000;
    constexpr auto kBegin = -1'000'000'000;
    constexpr auto kEnd = 1'000'000'000;
    constexpr auto kShift = 100'000;

    auto test = RandomGenerator{7'345'422u}.GenIntegralVector(kSize, kBegin, kEnd);
    auto expected = test;

    Rotate(&test, kShift);
    std::ranges::rotate(expected, expected.begin() + kShift);

    CHECK_THAT(test, Equals(expected));
}
