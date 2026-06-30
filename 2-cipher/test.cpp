#include "decipher.h"

#include <algorithm>
#include <string>
#include <ranges>

#include <catch2/catch_test_macros.hpp>

namespace {

void Check(const std::string& a, const std::string& expected) {
    static int test = 0;
    auto results = Decipher(a);

    auto view = std::views::join_with(results, '\n');
    auto s = std::ranges::to<std::string>(view);

    INFO("test " << ++test);
    INFO("result:\n" << s);

    CHECK(std::find(results.begin(), results.end(), expected) != results.end());
}

}  // namespace

TEST_CASE("Basic") {
    Check("a", "a");
    Check("hloolelwrd", "helloworld");
    Check("hweolrllod", "helloworld");
    Check("tset", "test");
}

TEST_CASE("Punctuation") {
    Check("HloWrdel ol!", "Hello World!");
    Check("HlWleoodl r!", "Hello World!");
    Check("Hore llWdlo!", "Hello World!");
    Check("HWeolrllod !", "Hello World!");
}

TEST_CASE("Longer") {
    Check("Ilv rporpy oecytgah!", "I love cryptography!");
    Check("Ivrop eyghl pryocta!", "I love cryptography!");
    Check(
        "C1el eaa r efeywa  C8h+ e r,mrnsloectahIeoi+ liawngIic fn  ndi+.e+c st p,duyrfi na d "
        "t+fsk  ge todetnt in+  1oihesl  a efet tu we1e enlu.wedirlohId 9TC1dsorieaulm inhw str.",
        "C++11 feels like a new language. I write code differently now than I did in C++98. The "
        "C++11 code is shorter, simpler, and usually more efficient than what I used to write.");
    Check(
        "Ao m c lyhv e,p r o sntlbipsebv eeic ttoo l dillnuc eearlnte hbfmaoio e tic dn  dixfel "
        "ayfrnpmceeas oloioco etne e.rsornnobtefrnerpmoyric.",
        "All problems in computer science can be solved by another level of indirection, except "
        "for the problem of too many layers of indirection..");
}
