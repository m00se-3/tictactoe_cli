#include "fuzztest/fuzztest.h"
#include <gtest/gtest.h>

#include <tictactoe_cli.hpp>
#include <strstream>

static void testGameLogic(const std::string& input) {
    Board board;
    std::istrstream stream{input.c_str()};

    board.run(&stream);
}

FUZZ_TEST(MyGameTest, testGameLogic)
.WithDomains(fuzztest::Arbitrary<std::string>())
.WithSeeds({"2-92kdhfiuei&*%$@(nfiosbr)"});