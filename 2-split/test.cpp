#include "split.h"
#include "utils.h"

#include <string>
#include <vector>
#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

using Catch::Matchers::Equals;
using Catch::Matchers::RangeEquals;

TEST_CASE("Simple") {
    CHECK_THAT(Split("aba caba 1"), RangeEquals(std::vector{"aba", "caba", "1"}));
    CHECK_THAT(Split("aba"), RangeEquals(std::vector{"aba"}));
}

TEST_CASE("Empty") {
    CHECK(Split("").empty());
}

TEST_CASE("Full match") {
    CHECK_THAT(Split("full match", "full match"), RangeEquals(std::vector{"", ""}));
}

TEST_CASE("Some tests") {
    CHECK_THAT(Split("just  a test "), RangeEquals(std::vector{"just", "", "a", "test", ""}));
    CHECK_THAT(Split("hello, world,no split here, , 1, ", ", "),
               RangeEquals(std::vector{"hello", "world,no split here", "", "1", ""}));
    CHECK_THAT(Split("  a  b c  def  g h ", "  "),
               RangeEquals(std::vector{"", "a", "b c", "def", "g h "}));
}

TEST_CASE("Random") {
    auto seed = GENERATE(take(10, random(0u, 1'000'000'000u)));
    auto string = RandomGenerator{seed}.GenString(100'000, 'a', 'f');
    std::string delimiter = "ab";

    auto view = std::views::split(string, delimiter);
    auto expected = std::ranges::to<std::vector<std::string>>(view);

    CHECK_THAT(Split(string, delimiter), Equals(expected));
}
