#include "long_sum.h"

#include <string>

#include <catch2/catch_test_macros.hpp>

namespace {

void Check(const std::string& a, const std::string& b, const std::string& expected) {
    static int test = 0;
    auto result = (LongSum(a, b) == expected);
    INFO("test " << ++test << ": " << LongSum(a, b));
    CHECK(result);
}

}  // namespace, that is a wierd way of checking commits...

TEST_CASE("Small") {
    Check("2", "2", "4");
    Check("6", "4", "10");
    Check("999", "9002", "10001");
    Check("999999999", "1", "1000000000");
    Check("1", "999999999", "1000000000");
}

TEST_CASE("Zero") {
    Check("0", "0", "0");
    Check("1", "0", "1");
    Check("0", "1", "1");
    Check("3748324784728473284723432333", "0", "3748324784728473284723432333");
    Check("0", "3748324784728473284723432333", "3748324784728473284723432333");
}

TEST_CASE("Leading Zero") {
    Check("01", "0", "1");
    Check("01", "9", "10");
    Check("001", "9", "10");
    Check("001", "009", "10");
}

TEST_CASE("Big") {
    Check("8328447534758347534857", "2222222222221921834372462374321",
          "2222222230550369369130809909178");
    Check("11234288473832", "227733800002323994999999230231233443",
          "227733800002323995000010464519707275");
    Check("123456789098765432187463567523", "999999999999999999999999999999999999999999999",
          "1000000000000000123456789098765432187463567522");
    Check("12345678901234567890123456789", "1111111111111111111111111111",
          "13456790012345679001234567900");
}

TEST_CASE("Very big") {
    std::string ones(4 * 1024 * 1024, '1');
    std::string twos(4 * 1024 * 1024, '2');
    std::string nines(4 * 1024 * 1024, '9');

    Check(ones, ones, twos);
    Check(ones, nines, ones + "0");
}
