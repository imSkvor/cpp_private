#include "rle.h"

#include <string>

#include <catch2/catch_test_macros.hpp>

namespace {

void Check(const std::string& a, const std::string& expected) {
    static int test = 0;
    auto result = (Rle(a) == expected);
    INFO("test " << ++test << ": " << Rle(a));
    CHECK(result);
}

}  // namespace

TEST_CASE("No Compression") {
    Check("", "");
    Check("A", "A");
    Check("AB", "AB");
}

TEST_CASE("Simple") {
    Check("ABB", "AB2");
    Check("AAB", "A2B");
    Check("AABBB", "A2B3");
    Check("AABBBCDDDD", "A2B3CD4");
    Check("AAAABBBCCXYZDDDDEEEFFFAAAAAAB", "A4B3C2XYZD4E3F3A6B");
}

TEST_CASE("Big") {
    Check(std::string(1024, 'A'), "A1024");
    Check(std::string(1024, 'A') + std::string(1024, 'B'), "A1024B1024");
    Check(std::string(1024, 'A') + "B", "A1024B");
    Check("B" + std::string(1024, 'A'), "BA1024");
}

TEST_CASE("Arbitrary Symbols") {
    Check("a***b", "a*3b");
    Check("a   b", "a 3b");
    Check(std::string(1024, '.'), ".1024");
    Check("...................OO....................", ".19O2.20");
    Check("g++ -Wall test.cpp", "g+2 -Wal2 test.cp2");
}
