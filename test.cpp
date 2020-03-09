#include "gtest/gtest.h"

#include "unit_tests/And_Test.hpp"
#include "unit_tests/Command_Test.hpp"
#include "unit_tests/Or_Test.hpp"
#include "unit_tests/Parser_Test.hpp"
#include "unit_tests/Semicolon_Test.hpp"
#include "unit_tests/InRedirect_Test.hpp"
#include "unit_tests/OutRedirect_Test.hpp"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
