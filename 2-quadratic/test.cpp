#include "quadratic.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;

TEST_CASE("No Roots") {
    CHECK(SolveQuadratic(0, 0, 5).count == RootCount::kZero);
    CHECK(SolveQuadratic(1, 0, 3).count == RootCount::kZero);
    CHECK(SolveQuadratic(4, -4, 7).count == RootCount::kZero);
}

TEST_CASE("One Root") {
    {
        auto result = SolveQuadratic(0, 3, 4);
        CHECK(result.count == RootCount::kOne);
        CHECK_THAT(result.first, WithinRel(-4. / 3));
    }
    {
        auto result = SolveQuadratic(9, -12, 4);
        CHECK(result.count == RootCount::kOne);
        CHECK_THAT(result.first, WithinRel(2. / 3));
    }
    {
        auto result = SolveQuadratic(5, 0, 0);
        CHECK(result.count == RootCount::kOne);
        CHECK_THAT(result.first, WithinRel(0.));
    }
}

TEST_CASE("Two Roots") {
    {
        auto result = SolveQuadratic(-5, 19, 12);
        CHECK(result.count == RootCount::kTwo);
        CHECK_THAT(result.first, WithinRel(1.9 - std::sqrt(601.) / 10));
        CHECK_THAT(result.second, WithinRel(1.9 + std::sqrt(601.) / 10));
    }
    {
        auto result = SolveQuadratic(1, -1, -1);
        CHECK(result.count == RootCount::kTwo);
        CHECK_THAT(result.first, WithinRel(.5 - std::sqrt(5.) / 2));
        CHECK_THAT(result.second, WithinRel(.5 + std::sqrt(5.) / 2));
    }
}

TEST_CASE("Inf Roots") {
    CHECK(SolveQuadratic(0, 0, 0).count == RootCount::kInf);
}
