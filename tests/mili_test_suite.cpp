#include <string>
#include "google/gtest/gtest.h"

int main(int argc, char **argv) {
  printf("Running mili tests1\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
