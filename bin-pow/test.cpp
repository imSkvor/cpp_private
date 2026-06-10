#include "binpow.h"

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Signature") {
    INFO("Do not change BinPow signature");
    STATIC_CHECK(std::is_same_v<decltype(&BinPow), int (*)(int, int64_t, int)>);
}

TEST_CASE("Small") {
    CHECK(BinPow(2, 3, 19) == 8);
    CHECK(BinPow(3, 0, 19) == 1);
    CHECK(BinPow(3, 3, 100) == 27);
    CHECK(BinPow(3, 4, 20) == 1);
    CHECK(BinPow(4, 8, 1'000) == 536);
}

TEST_CASE("Big") {
    CHECK(BinPow(1, 374'834'758'345, 129'237) == 1);
    CHECK(BinPow(2, 1'000'000'000'000'000'000, 1'000'000'007) == 719'476'260);
    CHECK(BinPow(17'239, 1'000'000'000'000'000 - 1, 100'000'000) == 43'181'159);
    CHECK(BinPow(203'042'322, 82'392'839'238'824'787, 92'374) == 78'360);
}

TEST_CASE("Edge") {
    CHECK(BinPow(42, 2025, 1) == 0);
    CHECK(BinPow(2, 1'000'000'000'000'000'000, 1) == 0);
    CHECK(BinPow(42, 1, 10) == 2);
    CHECK(BinPow(2, 1, 10) == 2);
    CHECK(BinPow(1, 0, 10) == 1);
}

TEST_CASE("Negative") {
    CHECK(BinPow(-42, 1, 100) == -42);
    CHECK(BinPow(-42, 2, 100) == 64);
    CHECK(BinPow(42, 1, -100) == 42);
    CHECK(BinPow(42, 2, -100) == 64);
    CHECK(BinPow(-42, 1, -100) == -42);
    CHECK(BinPow(-42, 2, -100) == 64);
}
