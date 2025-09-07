#include <gtest/gtest.h>

#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);  // Qt application for all render tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}