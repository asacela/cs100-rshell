#include "gtest/gtest.h"

#include "unit_tests/Parser_Test.hpp"

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}