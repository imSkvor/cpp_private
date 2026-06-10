#include "sms_decoder.h"

#include <string>

#include <catch2/catch_test_macros.hpp>

namespace {

void Check(const std::string& a, const std::string& expected) {
    static int test = 0;
    auto result = (Decode(a) == expected);
    INFO("test " << ++test << ": " << Decode(a));
    CHECK(result);
}

}  // namespace

TEST_CASE("Basic") {
    Check("", "");
    Check("1", "1");
    Check("11", "11");
    Check("2", "a");
    Check("22", "b");
    Check("333", "f");
    Check("4444", "4");
    Check("55555", "j");
    Check("6666666666", "n");
    Check("7", "p");
    Check("88", "u");
    Check("999", "y");
    Check("0", " ");
    Check("00", "0");
    Check("*", ".");
    Check("**", ",");
    Check("***", "?");
    Check("****", "!");
    Check("*****", ".");
}

TEST_CASE("Pauses") {
    Check("....", "");
    Check("1.1", "11");
    Check("22.2", "ba");
    Check("333.33.3", "fed");
    Check("9...999.", "wy");
    Check("9898", "wtwt");
    Check("98898", "wuwt");
    Check("98.898", "wttwt");
    Check("98...99..98", "wtxwt");
    Check("*...**..***", ".,?");
}

TEST_CASE("my") {
    Check("#22#22#22", "BBB");
}

TEST_CASE("Capital") {
    Check("#1", "1");
    Check("#22", "B");
    Check("#222222", "B");
    Check("#22#22#22", "BBB");
    Check("#22#22.22", "BBb");
    Check("##22#22.22", "bBb");
    Check("##22###22.22", "bBb");
    Check("#22333", "Bf");
    Check("#****", "!");
    Check("#**.**", ",,");
    Check("22#", "b");
    Check("22#****", "b!");
    Check("#0", " ");
    Check("#00", "0");
    Check("#6666.6", "6m");
    Check("#.22", "B");
    Check("#....22", "B");
    Check("#....##22", "B");
    Check("#.#22", "b");
    Check("##.22", "b");
    Check("#.#.22", "b");
}

TEST_CASE("SMS") {
    Check("#4433555.555666096667775553****", "Hello world!");
    Check("#444094447777440#8#4033994447777833.30444660844330.00.007777*",
          "I wish TG existed in the 00s.");
    Check("#4433999****0#7777666777.777999**0222.266.66.6668082555.55036664446640#44#9",
          "Hey! Sorry, cannot talk doing HW");
    Check("222.2555.55506330888899999199999*.*.*.", "call me 8919...");
}
