#include "../../model/parser/parser.h"
#include "../../model/parser/model_parser.h"

#include <fstream>
#include <gtest/gtest.h>
/*
// We are private now ¯\_(ツ)_/¯
TEST(Model_Parser, ParssingUnits_ServiseFunctions_CreatePrefixArray) {
  using s21::inbound_model::CreatePrefixArray;
  auto array = CreatePrefixArray();

  EXPECT_EQ(array.size(), 5);     //change to 26 in case adding more prefixes
  EXPECT_EQ(array[0], "v");
  // EXPECT_EQ(array[1], "vt");
  // EXPECT_EQ(array[2], "vn");
  // EXPECT_EQ(array[3], "vp");
  EXPECT_EQ(array[ 1], "f");
  EXPECT_EQ(array[2], "l");
  EXPECT_EQ(array[3], "p");
  // EXPECT_EQ(array[7], "g");
  EXPECT_EQ(array[4], "o");
  // EXPECT_EQ(array[9], "s");
  // EXPECT_EQ(array[10], "mg");
  // EXPECT_EQ(array[11], "mtlib");
  // EXPECT_EQ(array[12], "usemtl");
  // EXPECT_EQ(array[13], "curv");
  // EXPECT_EQ(array[14], "curv2");
  // EXPECT_EQ(array[15], "surf");
  // EXPECT_EQ(array[16], "parm");
  // EXPECT_EQ(array[17], "deg");
  // EXPECT_EQ(array[18], "bmat");
  // EXPECT_EQ(array[19], "step");
  // EXPECT_EQ(array[20], "cstype");
  // EXPECT_EQ(array[21], "trim");
  // EXPECT_EQ(array[22], "hole");
  // EXPECT_EQ(array[23], "scrv");
  // EXPECT_EQ(array[24], "sp");
  // EXPECT_EQ(array[25], "end");

  std::string prefix = "f";

  for (size_t i = 0; i < array.size(); i++) {
    if (array[i] == "f") {
      EXPECT_EQ(i, 1);    //change to 4 in case adding more prefixes
      EXPECT_EQ(array[i], "f");
    }
  }

  auto array_2 = CreatePrefixArray();
  auto array_3 = CreatePrefixArray();
  auto array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
  array_4 = CreatePrefixArray();
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_VerticeDecoder) {
  using s21::inbound_model::VerticeDecoder;

  double input;
  size_t output;
  size_t vert_amount;

  vert_amount = 10;

  EXPECT_EQ(VerticeDecoder(0, output, vert_amount), false);
  for (input = 1; input < 20; input++) {
    EXPECT_EQ(VerticeDecoder(input, output, vert_amount), true);
    EXPECT_EQ(output, (size_t)(input - 1));
  }

  size_t check = vert_amount - 1;
  for (input = -1; input > -20; input--, check--) {
    if (input >= -10) {
      EXPECT_EQ(VerticeDecoder(input, output, vert_amount), true);
      EXPECT_EQ(output, check);
    } else
      EXPECT_EQ(VerticeDecoder(input, output, vert_amount), false);
  }

  EXPECT_EQ(VerticeDecoder(-1, output, 3), true);
  EXPECT_EQ(output, 2);
  EXPECT_EQ(VerticeDecoder(-2, output, 3), true);
  EXPECT_EQ(output, 1);
  EXPECT_EQ(VerticeDecoder(-3, output, 3), true);
  EXPECT_EQ(output, 0);
  EXPECT_EQ(VerticeDecoder(-4, output, 3), false);
  EXPECT_EQ(VerticeDecoder(0, output, 10), false);
  EXPECT_EQ(VerticeDecoder(-1, output, 0), false);
  EXPECT_EQ(VerticeDecoder(1, output, 0), true);
  EXPECT_EQ(output, 0);
  EXPECT_EQ(VerticeDecoder(-6, output, 12), true);
  EXPECT_EQ(output, 6);
}

TEST(Model_Parser, ParssingUnits_ModelAlters_ModelNameSetter) {
  using s21::inbound_model::Model3D;
  using s21::inbound_model::ModelNameSetter;

  Model3D model;
  EXPECT_EQ(model.GetName(), "");
  EXPECT_EQ(model.GetName().empty(), true);

  ModelNameSetter(model, "Where");
  EXPECT_EQ(model.GetName(), "Where");
  ModelNameSetter(model, "are");
  EXPECT_EQ(model.GetName(), "Where_&_are");
  ModelNameSetter(model, "you");
  EXPECT_EQ(model.GetName(), "Where_&_are_&_you");
  ModelNameSetter(model, "?");
  EXPECT_EQ(model.GetName(), "Where_&_are_&_you_&_?");
  ModelNameSetter(model, " ");
  EXPECT_EQ(model.GetName(), "Where_&_are_&_you_&_?_&_ ");
  ModelNameSetter(model, "");
  EXPECT_EQ(model.GetName(), "Where_&_are_&_you_&_?_&_ ");
  ModelNameSetter(model, "I'm here", true);
  EXPECT_EQ(model.GetName(), "I'm here");
}

TEST(Model_Parser, ParssingUnits_ModelAlters_EdgesRemover) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::EdgesRemover;
  using s21::inbound_model::Model3D;

  Model3D model;
  for (int i = 0; i < 20; i++) {
    model.AddEdge(i, i + 1);
  }

  EXPECT_EQ(model.GetEdgesAmount(), 20);
  size_t counter;
  for (counter = 0; counter < model.GetEdgesAmount(); counter++) {
    EXPECT_EQ(model(counter), Edge(counter, counter + 1));
  }
  EXPECT_EQ(model(counter - 1), Edge(19, 20));

  EdgesRemover(model, 5);
  EXPECT_EQ(model.GetEdgesAmount(), 15);
  for (counter = 0; counter < model.GetEdgesAmount(); counter++) {
    EXPECT_EQ(model(counter), Edge(counter, counter + 1));
  }
  EXPECT_EQ(model(counter - 1), Edge(14, 15));

  EdgesRemover(model, 10);
  EXPECT_EQ(model.GetEdgesAmount(), 5);
  for (counter = 0; counter < model.GetEdgesAmount(); counter++) {
    EXPECT_EQ(model(counter), Edge(counter, counter + 1));
  }
  EXPECT_EQ(model(counter - 1), Edge(4, 5));

  EdgesRemover(model, 0);
  EXPECT_EQ(model.GetEdgesAmount(), 5);
  for (counter = 0; counter < model.GetEdgesAmount(); counter++) {
    EXPECT_EQ(model(counter), Edge(counter, counter + 1));
  }
  EXPECT_EQ(model(counter - 1), Edge(4, 5));

  EdgesRemover(model, 10);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EdgesRemover(model, 100);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
}

TEST(Model_Parser, ParssingUnits_ModelAlters_SingleVertEdgesAdder) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::Model3D;
  using s21::inbound_model::SingleVertEdgesAdder;

  Model3D model;
  std::vector<double> vect;

  EXPECT_EQ(SingleVertEdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  vect = {12, 3,   4,  5,   6,   7, 888, 4,  3, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 20);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 0));

  vect.clear();
  vect = {-1, -2, -4, -10, -12, -3, -4, -5, -6};
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 20);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 0));

  for (int i = 0; i < 10; i++) {
    model.AddVert(i, i * 2, i + 3);
  }
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 10);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 20);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 0));

  model.AddVert(1, 2, 3);
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 11);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 20);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 0));

  model.AddVert(1, 2, 3);
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 12);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 29);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1),
            Edge(model.GetVerticesAmount() - 6, 12 - 6));
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6, 6));

  vect.clear();
  vect = {12, 3,   4,  5,   6,   7, 888, 4,  0, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 29);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6, 6));

  vect.clear();
  vect = {12, 3,   4,  5,   6,   7, 888, 4,  5, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(SingleVertEdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 49);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 0));
}

TEST(Model_Parser, ParssingUnits_ModelAlters_EdgesAdder) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::EdgesAdder;
  using s21::inbound_model::Model3D;

  Model3D model;
  std::vector<double> vect;

  EXPECT_EQ(EdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  vect = {121};
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 1);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(120, 120));

  vect.clear();
  vect = {1, 2};
  EXPECT_EQ(vect.size(), 2);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 3);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 1));

  vect.clear();
  vect = {1, 2, 3};
  EXPECT_EQ(vect.size(), 3);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 6);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 2));

  vect.clear();
  vect = {12, 3,   4,  5,   6,   7, 888, 4,  3, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 26);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 11));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(0, 3));

  vect.clear();
  vect = {-1, -2, -4, -10, -12, -3, -4, -5, -6};
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(EdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 26);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 11));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(0, 3));

  for (int i = 0; i < 10; i++) {
    model.AddVert(i, i * 2, i + 3);
  }
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 10);
  EXPECT_EQ(EdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 26);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 11));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(0, 3));

  model.AddVert(1, 2, 3);
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 11);
  EXPECT_EQ(EdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 26);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 11));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(0, 3));

  model.AddVert(1, 2, 3);
  EXPECT_EQ(vect.size(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 12);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 35);
  EXPECT_EQ(model(model.GetEdgesAmount() - 2),
            Edge(model.GetVerticesAmount() - 6, 12 - 5));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(6, 7));
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6, 12 - 1));
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6, 11));

  vect.clear();
  vect = {12, 3,   4,  5,   6,   7, 888, 4,  0, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(EdgesAdder(model, vect), false);
  EXPECT_EQ(model.GetEdgesAmount(), 35);
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(6, 7));
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6, 11));

  vect.clear();
  vect = {12, 3,   4,  5,   6,   7, 888, 4,  5, 34,
          34, 234, 24, 324, 234, 2, 423, 42, 4, 1};
  EXPECT_EQ(vect.size(), 20);
  EXPECT_EQ(EdgesAdder(model, vect), true);
  EXPECT_EQ(model.GetEdgesAmount(), 55);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(0, 11));
  EXPECT_EQ(model(model.GetEdgesAmount() - 2), Edge(0, 3));
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_LineStartsWithPrefix) {
  using s21::inbound_model::LineStartsWithPrefix;
  using std::string;
  string line{""};
  string prefix{"f"};

  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "f";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "f ";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), true);
  line = " f ";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "f ";
  EXPECT_EQ(LineStartsWithPrefix(line, ""), false);
  line = "f 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), true);
  line = " f 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "v 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  prefix = "vp";
  line = "v 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "vp";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "vp4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
  line = "vp 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), true);
  prefix = "f";
  line = "l 1 2 4";
  EXPECT_EQ(LineStartsWithPrefix(line, prefix), false);
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_ProcessCharLP) {
  using s21::inbound_model::ProcessCharLP;
  using std::istringstream;
  using vector_d = std::vector<double>;
  using s21::inbound_model::LSpaceChTrim;
  using std::string;

  string line{
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25"};
  istringstream iss{line};
  vector_d vect;

  LSpaceChTrim(iss);
  int symbol = iss.peek();
  while (symbol != EOF) {
    EXPECT_EQ(ProcessCharLP(iss, vect, symbol), true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  EXPECT_EQ(ProcessCharLP(iss, vect, symbol), false);
  EXPECT_EQ(vect.size(), 0);

  bool func_output;
  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 0);

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 f -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 0);

  iss.clear();
  vect.clear();
  line = "    ";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 0);

  iss.clear();
  vect.clear();
  line = "";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 0);

  iss.clear();
  vect.clear();
  line = "   5";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 1);
  EXPECT_DOUBLE_EQ(vect[0], 5);

  iss.clear();
  vect.clear();
  line = "   5 6";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 2);
  EXPECT_DOUBLE_EQ(vect[0], 5);
  EXPECT_DOUBLE_EQ(vect[1], 6);

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.5 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 0);

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13. -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25#shit";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25  #Fuck";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25                        #Fuck";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  iss.clear();
  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25  #Fuck 26 27 28 29 -30";
  iss.str(line);
  LSpaceChTrim(iss);
  symbol = iss.peek();
  while (symbol != EOF) {
    func_output = ProcessCharLP(iss, vect, symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    symbol = iss.peek();
  }
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixCommonLP) {
  using s21::inbound_model::PrefixCommonLP;

  std::string line{
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25"};
  std::vector<double> vect;

  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 f -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "    ";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "   5";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_DOUBLE_EQ(vect[0], 5);

  vect.clear();
  line = "   5 6";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 2);
  EXPECT_DOUBLE_EQ(vect[0], 5);
  EXPECT_DOUBLE_EQ(vect[1], 6);

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.5 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13. -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25#Shit";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25  #Fuck";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25                        #Stupid";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25  #Fuck this: 26 27 28 29 -30";
  PrefixCommonLP(line, vect);
  EXPECT_EQ(vect.size(), 25);
  for (double i = 1; i <= 10; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
  for (double i = 11; i <= 17; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], -i);
  }
  for (double i = 18; i <= 25; i++) {
    EXPECT_DOUBLE_EQ(vect[i - 1], i);
  }
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixP) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::Model3D;
  using s21::inbound_model::PrefixP;

  std::string line{
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25"};
  Model3D model;

  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);

  for (int i = 0; i < 16; i++) {
    model.AddVert(i, -i, i * 2);
  }
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 16);

  model.AddVert(16, -16, 16 * 2);
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);
  EXPECT_EQ(model.GetVerticesAmount(), 17);

  for (double i = 0; i < 10; i++) {
    EXPECT_EQ(model(i), Edge(i, i));
  }
  for (double i = 10; i < 17; i++) {
    EXPECT_EQ(model(i),
              Edge(model.GetVerticesAmount() - (i + 1), 17 - (i + 1)));
  }
  for (double i = 17; i < 25; i++) {
    EXPECT_EQ(model(i), Edge(i, i));
  }

  model.Clear();
  for (int i = 0; i < 5; i++) {
    model.AddVert(i, -i, i * 2);
  }
  line = "    1 2 3 4 5 \t\t\t\t -1 -2 -3 -4 -5";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 10);
  EXPECT_EQ(model.GetVerticesAmount(), 5);
  EXPECT_EQ(model(0), Edge(0, 0));
  EXPECT_EQ(model(1), Edge(1, 1));
  EXPECT_EQ(model(2), Edge(2, 2));
  EXPECT_EQ(model(3), Edge(3, 3));
  EXPECT_EQ(model(4), Edge(4, 4));
  EXPECT_EQ(model(5), Edge(4, 4));
  EXPECT_EQ(model(6), Edge(3, 3));
  EXPECT_EQ(model(7), Edge(2, 2));
  EXPECT_EQ(model(8), Edge(1, 1));
  EXPECT_EQ(model(9), Edge(0, 0));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 f -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    ";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    5";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 1);
  EXPECT_EQ(model(0), Edge(4, 4));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    -5";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 1);
  EXPECT_EQ(model(0), Edge(12, 12));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    -1";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 1);
  EXPECT_EQ(model(0), Edge(16, 16));

  line = "   5 6";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 3);
  EXPECT_EQ(model(0), Edge(16, 16));
  EXPECT_EQ(model(1), Edge(4, 4));
  EXPECT_EQ(model(2), Edge(5, 5));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.5 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13. -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25#Shit";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 50);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "1 2 3 4 5 6      7   \t\t\t\t8 9 10 -11 -12 -13.0 -14 -15 -16 -17 18 19 "
      "20  21 22 23 24 25            #READ this: 26 27 28 29 -30";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 75);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "1 2 3 4 5 6      7   \t\t\t\t8 9 10 -11 -12 --13.0 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25            #READ this: 26 27 28 29 -30";
  PrefixP(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 75);
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixL) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::Model3D;
  using s21::inbound_model::PrefixL;

  std::string line{
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25"};
  Model3D model;

  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);

  for (int i = 0; i < 16; i++) {
    model.AddVert(i, -i, i * 2);
  }
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 16);

  model.AddVert(16, -16, 16 * 2);
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 24);
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  for (double i = 0; i < 9; i++) {
    EXPECT_EQ(model(i), Edge(i, i + 1));
  }
  EXPECT_EQ(model(9), Edge(17 - 11, 9));
  for (double i = 10; i < 16; i++) {
    EXPECT_EQ(model(i),
              Edge(model.GetVerticesAmount() - (i + 1), 17 - (i + 2)));
  }
  EXPECT_EQ(model(16), Edge(0, 17));
  for (double i = 17; i < 23; i++) {
    EXPECT_EQ(model(i), Edge(i, i + 1));
  }

  model.Clear();
  for (int i = 0; i < 5; i++) {
    model.AddVert(i, -i, i * 2);
  }
  line = "    1 2 3 4 5 \t\t\t\t -1 -2 -3 -4 -5";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 9);
  EXPECT_EQ(model.GetVerticesAmount(), 5);
  EXPECT_EQ(model(0), Edge(0, 1));
  EXPECT_EQ(model(1), Edge(1, 2));
  EXPECT_EQ(model(2), Edge(2, 3));
  EXPECT_EQ(model(3), Edge(3, 4));
  EXPECT_EQ(model(4), Edge(4, 4));
  EXPECT_EQ(model(5), Edge(3, 4));
  EXPECT_EQ(model(6), Edge(2, 3));
  EXPECT_EQ(model(7), Edge(1, 2));
  EXPECT_EQ(model(8), Edge(0, 1));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 f -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    ";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    5";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    -5";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line = "    -1";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  line = "   5 6";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 1);
  EXPECT_EQ(model(0), Edge(4, 5));

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.5 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13. -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 24);

  model.Clear();
  for (int i = 0; i < 17; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 24);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.0 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25#Shit";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 48);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "1 2 3 4 5 6      7   \t\t\t\t8 9 10 -11 -12 -13.0 -14 -15 -16 -17 18 19 "
      "20  21 22 23 24 25            #READ this: 26 27 28 29 -30";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 72);

  EXPECT_EQ(model.GetVerticesAmount(), 17);
  line =
      "1 2 3 4 5 6      7   \t\t\t\t8 9 10 -11 -12 --13.0 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25            #READ this: 26 27 28 29 -30";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 72);

  model.Clear();
  line = "  53 52 53 54 55 ";
  PrefixL(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 4);
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixO) {
  using s21::inbound_model::Model3D;
  using s21::inbound_model::PrefixO;

  Model3D model;
  std::string name;

  name = {"The name"};
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(), name);

  name = "other file";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(), "The name_&_other file");

  name = "";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "The name_&_other file");

  name = "       ";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "The name_&_other file");

  name = "      #HELLO THERE ";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "The name_&_other file");

  name = "   newest name   #HELLO THERE ";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(), "The name_&_other file_&_newest name");

  name = "   newest name   #HELLO THERE #fscscs ";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(),
            "The name_&_other file_&_newest name_&_newest name");

  name = "   newest name#HELLO THERE #fscscs ";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(),
            "The name_&_other file_&_newest name_&_newest name_&_newest name");

  name = "   a                                         \t\t\t\t\t\t\t\t\t\t";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(
      model.GetName(),
      "The name_&_other file_&_newest name_&_newest name_&_newest name_&_a");

  model.Clear();
  name = "";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "");

  name = "       ";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "");

  name = "      #HELLO THERE ";
  EXPECT_EQ(PrefixO(model, name), false);
  EXPECT_EQ(model.GetName(), "");

  name = "   a                                         \t\t\t\t\t\t\t\t\t\t";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(), "a");

  name = "a                                         \t\t\t\t\t\t\t\t\t\t";
  EXPECT_EQ(PrefixO(model, name), true);
  EXPECT_EQ(model.GetName(), "a_&_a");
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixV) {
  using s21::inbound_model::Model3D;
  using s21::inbound_model::PrefixV;

  Model3D model;
  std::string str;

  str = "    1  3   5.55";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 1);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);

  str = "    1  3   5.55  55";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 2);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);
  EXPECT_EQ(model[1].x, 1);
  EXPECT_EQ(model[1].y, 3);
  EXPECT_EQ(model[1].z, 5.55);

  str = "    1  3   5.55  55 444";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 2);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);
  EXPECT_EQ(model[1].x, 1);
  EXPECT_EQ(model[1].y, 3);
  EXPECT_EQ(model[1].z, 5.55);

  str = "    1  3   5.55  55 female";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 2);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);
  EXPECT_EQ(model[1].x, 1);
  EXPECT_EQ(model[1].y, 3);
  EXPECT_EQ(model[1].z, 5.55);

  str = "    2  2   5.55  55 #female";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 3);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);
  EXPECT_EQ(model[1].x, 1);
  EXPECT_EQ(model[1].y, 3);
  EXPECT_EQ(model[1].z, 5.55);
  EXPECT_EQ(model[2].x, 2);
  EXPECT_EQ(model[2].y, 2);
  EXPECT_EQ(model[2].z, 5.55);

  str = "2  2   5.55  55                      #female                  #male";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 4);
  EXPECT_EQ(model[0].x, 1);
  EXPECT_EQ(model[0].y, 3);
  EXPECT_EQ(model[0].z, 5.55);
  EXPECT_EQ(model[1].x, 1);
  EXPECT_EQ(model[1].y, 3);
  EXPECT_EQ(model[1].z, 5.55);
  EXPECT_EQ(model[2].x, 2);
  EXPECT_EQ(model[2].y, 2);
  EXPECT_EQ(model[2].z, 5.55);
  EXPECT_EQ(model[2].x, 2);
  EXPECT_EQ(model[2].y, 2);
  EXPECT_EQ(model[2].z, 5.55);

  str = "    1  3   5.55   hi";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 4);

  str = "    1  3   5.55hi";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 4);

  str = "    1  3   5.55#hi";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 5);

  str = "    1  3   -5.55";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "    1  3   -5.55.";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "    1  3   ";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "    1";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "    ";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "a";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "#f";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);

  str = "    1 f  3   4";
  PrefixV(model, str);
  EXPECT_EQ(model.GetVerticesAmount(), 6);
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_ProcessCharF) {
  using s21::inbound_model::LSpaceChTrim;
  using s21::inbound_model::ProcessCharF;

  std::string line;
  std::istringstream iss;
  std::vector<double> vect;
  int next_symbol;

  vect.clear();
  line = "";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = " ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "# ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "g ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "_ ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "/";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "\t";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5 ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], 5);

  vect.clear();
  line = "-55 ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55#";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "5f";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "-5.5";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "0";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5f";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "-55/6";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55/6/9";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55/6/9 ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55/6/9#";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55/6 ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55/6# ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55//6# ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55//6  ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "-55//6";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), true);
  EXPECT_EQ(vect.size(), 1);
  EXPECT_EQ(vect[0], -55);

  vect.clear();
  line = "5/";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/f";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/#";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/ ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/55.5";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5//";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5//#";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5///";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5//f";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5//55.55";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5// ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5//";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/#";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4//";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/f";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/55.55";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/ ";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line = "5/4/";
  iss.clear();
  iss.str(line);
  next_symbol = iss.peek();
  EXPECT_EQ(ProcessCharF(iss, vect, next_symbol), false);
  EXPECT_EQ(vect.size(), 0);

  bool func_output;

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13.5 -14 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -0 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 25);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/3 -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 25);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/3/ -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/3/s -11/2/5 "
      "-12/5 -13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/3.5 -11/2/5 "
      "-12/5 -13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10// -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/g/5 -11/2/5 "
      "-12/5 -13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 //5 -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/ -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);

  vect.clear();
  line =
      "    1 2 3 4/3 5//3 6/5/3      7//554   \t\t\t\t 8 9 10/7/ -11/2/5 -12/5 "
      "-13 -14 -15 -16 -17 18 19 20  21 22 23 24 25#HELL";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (next_symbol != EOF) {
    func_output = ProcessCharF(iss, vect, next_symbol);
    if (func_output != true) {
      EXPECT_EQ(func_output, false);
      break;
    } else
      EXPECT_EQ(func_output, true);
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }
  EXPECT_EQ(vect.size(), 0);
}

TEST(Model_Parser, ParssingUnits_PrefixHandlers_PrefixF) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::PrefixF;

  std::string line{
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25"};
  s21::inbound_model::Model3D model;

  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);

  for (int i = 0; i < 16; i++) {
    model.AddVert(i, -i, i * 2);
  }
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 16);

  model.AddVert(16, -16, 16 * 2);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);
  EXPECT_EQ(model.GetVerticesAmount(), 17);
  for (double i = 0; i < 9; i++) {
    EXPECT_EQ(model(i), Edge(i, i + 1));
  }
  EXPECT_EQ(model(9), Edge(17 - 11, 9));
  for (double i = 10; i < 16; i++) {
    EXPECT_EQ(model(i),
              Edge(model.GetVerticesAmount() - (i + 1), 17 - (i + 2)));
  }
  EXPECT_EQ(model(16), Edge(0, 17));
  for (double i = 17; i <= 23; i++) {
    EXPECT_EQ(model(i), Edge(i, i + 1));
  }
  EXPECT_EQ(model(24), Edge(0, 24));

  model.Clear();
  line =
      "1/5/5 2/4 3//6 4 5/-4/-3  \t\t        -1   -2/4/-3 -3//5 -4 -5/-9   "
      "#Something";
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  for (int i = 0; i < 4; i++) {
    model.AddVert(i, -i, i * 2);
  }
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 4);
  model.AddVert(4, -4, 4 * 2);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 10);
  EXPECT_EQ(model.GetVerticesAmount(), 5);
  EXPECT_EQ(model(0), Edge(0, 1));
  EXPECT_EQ(model(1), Edge(1, 2));
  EXPECT_EQ(model(2), Edge(2, 3));
  EXPECT_EQ(model(3), Edge(3, 4));
  EXPECT_EQ(model(4), Edge(4, 4));
  EXPECT_EQ(model(5), Edge(3, 4));
  EXPECT_EQ(model(6), Edge(2, 3));
  EXPECT_EQ(model(7), Edge(1, 2));
  EXPECT_EQ(model(8), Edge(0, 1));
  EXPECT_EQ(model(9), Edge(0, 0));

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14 -15 -16 -17 18 "
      "19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/5 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/5/7 -15 -16 "
      "-17 18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//7 -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//-7 -15 -16 "
      "-17 18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 25);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//-7# -15 -16 "
      "-17 18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 14);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/5/7 #-15 -16 "
      "-17 18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 14);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/ -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line = "    1 2 4";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 3);

  model.Clear();
  line = "    1 2 ";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line = "    1 ";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14// -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//# -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//# -15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//8-15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/-7# -15 -16 "
      "-17 18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 14);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/8-15 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14-15 -16 -17 18 "
      "19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14/-15.5 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);

  model.Clear();
  line =
      "    1 2 3 4 5 6      7   \t\t\t\t 8 9 10 -11 -12 -13 -14//-15.6 -16 -17 "
      "18 19 20  21 22 23 24 25";
  for (int i = 0; i < 20; i++) {
    model.AddVert(i, -i, i * 2);
  }
  EXPECT_EQ(model.GetVerticesAmount(), 20);
  PrefixF(model, line);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
}





*/
TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNum) {

  int ch = 'k';
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch), false);
  for (ch = 0; ch < 127; ch++) {
    if (ch <= 57 && ch >= 48)
      EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch), true);
    else
      EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch), false);
  }

  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('0'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('1'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('2'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('3'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('4'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('5'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('6'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('7'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('8'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum('9'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsInteger) {
  double num = 0.0;

  for (num = -50.0; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num), true);
  }
  for (num = -50.1; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num), false);
  }
  for (num = -50.5; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num), false);
  }
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNonzeroInteger) {
  double num = 0.0;

  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), false);
  for (num = -50.0; num < 0; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), true);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), false);
  num++;
  for (; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), true);
  }
  for (num = -50.1; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), false);
  }
  for (num = -50.5; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNonzeroInteger(num), false);
  }
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsSpaceCh) {
  int ch = 33;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(' '), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh('\t'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsHash) {
  int ch = 33;
  for (ch = 0; ch < 35; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsHash(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsHash(ch), true);
  ch++;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsHash(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsHash('#'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsHash(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsSlash) {
  int ch = 33;
  for (ch = 0; ch < 47; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch), true);
  ch++;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash('/'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsSpaceChHashEOF) {
  int ch = 33;
  for (ch = 0; ch < '\t'; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF('\t'), true);
  ch++;
  for (; ch < ' '; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(' '), true);
  ch++;
  for (; ch < '#'; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF('#'), true);
  ch++;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch), false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(EOF), true);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNotEOF) {
  int ch = 33;
  for (ch = 0; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNotEOF(ch), true);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNotEOF(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNextNumber) {
  using s21::inbound_model::parser::service_functions::IsNextNumber;
  std::string line{"Hell 2 you! "};
  std::istringstream iss{line};
  int ch = iss.peek();
  while (1) {
    if (ch == EOF)
      break;
    else if (ch == '2')
      EXPECT_EQ(IsNextNumber(iss), true);
    else
      EXPECT_EQ(IsNextNumber(iss), false);

    iss.get();
    ch = iss.peek();
  }

  line = "-555";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = "-555.6";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = "0";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = ".";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "--";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "/-";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "-f";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "-k";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "k";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "55";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = "-0.6";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = "0.66";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), true);
  line = " ";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "\t";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);
  line = "";
  iss.clear();
  iss.str(line);
  EXPECT_EQ(IsNextNumber(iss), false);

  line =
      "      -5555.55    -5555.55   -5555.55   -5555.55  f          -5555.55   "
      "  ddd    qwwq  -5555.55 -5555.55 -5555.55 -5555.55/-5555.55/-5555.55   "
      "fghj  ";
  double num;
  iss.clear();
  iss.str(line);
  ch = iss.get();
  while (s21::inbound_model::parser::service_functions::IsNotEOF(ch)) {
    if (IsNextNumber(iss)) {
      iss >> num;
      EXPECT_DOUBLE_EQ(num, -5555.55);
    }
    ch = iss.get();
  }
  line =
      "      5    5   5   5  f          5     ddd    qwwq  5 5 5 5/5/5   fghj "
      " ";
  iss.clear();
  iss.str(line);
  ch = iss.get();
  while (s21::inbound_model::parser::service_functions::IsNotEOF(ch)) {
    if (IsNextNumber(iss)) {
      iss >> num;
      EXPECT_DOUBLE_EQ(num, 5);
    }
    ch = iss.get();
  }
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_RSpaceChTrim_string) {
  using s21::inbound_model::parser::service_functions::RSpaceChTrim;

  std::string line{"Hello there!"};

  size_t length = line.length();
  size_t length_origin = length;
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length);
  EXPECT_EQ(line.length(), length_origin);

  line = "Hello there!     ";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 5);
  EXPECT_EQ(line.length(), length_origin);
  EXPECT_EQ(*(line.end() - 1), '!');

  line = "Hello there!      \t\t\t\t";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 10);
  EXPECT_EQ(line.length(), length_origin);
  EXPECT_EQ(*(line.end() - 1), '!');

  line = "Hello there!     \n\t\t\t\t";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 4);
  EXPECT_EQ(line.length(), length_origin + 6);
  EXPECT_EQ(*(line.end() - 1), '\n');

  line = "";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length);
  EXPECT_EQ(line.length(), 0);

  line = "   asdf     ";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 5);
  EXPECT_EQ(line.length(), 7);

  line = "                         ";
  length = line.length();
  RSpaceChTrim(line);
  EXPECT_EQ(line.length(), 0);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_LSpaceChTrim_string) {
  using s21::inbound_model::parser::service_functions::LSpaceChTrim;

  std::string line{"Hello there!"};

  size_t length = line.length();
  size_t length_origin = length;
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length);
  EXPECT_EQ(line.length(), length_origin);

  line = "               Hello there!";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 15);
  EXPECT_EQ(line.length(), length_origin);
  EXPECT_EQ(*(line.end() - 1), '!');

  line = "      \t\t\t\tHello there!";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 10);
  EXPECT_EQ(line.length(), length_origin);
  EXPECT_EQ(*(line.end() - 1), '!');

  line = "     \t\t\n\t\tHello there!";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 7);
  EXPECT_EQ(line.length(), length_origin + 3);
  EXPECT_EQ(*(line.end() - 1), '!');

  line = "";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length);
  EXPECT_EQ(line.length(), 0);

  line = "   asdf     ";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 3);
  EXPECT_EQ(line.length(), 9);

  line = "                         ";
  length = line.length();
  LSpaceChTrim(line);
  EXPECT_EQ(line.length(), 0);

  line = "   asdf     ";
  length = line.length();
  LSpaceChTrim(line);
  s21::inbound_model::parser::service_functions::RSpaceChTrim(line);
  EXPECT_EQ(line.length(), length - 8);
  EXPECT_EQ(line.length(), 4);
  EXPECT_EQ(line[0], 'a');
  EXPECT_EQ(*(line.end() - 1), 'f');
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_LSpaceChTrim_istringsteam) {
  using s21::inbound_model::parser::service_functions::LSpaceChTrim;

  std::string line{"Hello there!"};
  std::istringstream iss(line);

  size_t length;
  size_t length_origin = line.length();
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), 'H');
  length = 0;
  while (iss.peek() != EOF) {
    length++;
    iss.get();
  }
  EXPECT_EQ(length, length_origin);
  iss.unget();
  EXPECT_EQ(iss.get(), '!');

  line = "               Hello there!";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), 'H');
  length = 0;
  while (iss.peek() != EOF) {
    length++;
    iss.get();
  }
  EXPECT_EQ(length, length_origin);
  iss.unget();
  EXPECT_EQ(iss.get(), '!');

  line = "     \n\t\t\t\tHello there!";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), 'H');
  length = 0;
  while (iss.peek() != EOF) {
    length++;
    iss.get();
  }
  EXPECT_EQ(length, length_origin);
  iss.unget();
  EXPECT_EQ(iss.get(), '!');

  line = "";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), EOF);
  EXPECT_EQ(iss.eof(), true);

  line = "   asdf     ";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), 'a');
  length = 0;
  while (iss.peek() != EOF) {
    length++;
    iss.get();
  }
  EXPECT_EQ(length, 9);
  iss.unget();
  EXPECT_EQ(iss.get(), ' ');

  line = "                         ";
  iss.clear();
  iss.str(line);
  LSpaceChTrim(iss);
  EXPECT_EQ(iss.peek(), EOF);
  EXPECT_EQ(iss.eof(), true);
}

TEST(Model_Parser, Parser_ModelNormalizer) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::Vec3;

  s21::inbound_model::Model3D model;

  for (int i = 0; i < 21; i++) {
    model.AddVert(i + 10, i - 20, i - 10);
  }
  for (int i = 0; i < 5; i++) {
    model.AddEdge(1, 2);
    model.AddEdge(1, 1);
    model.AddEdge(30, 33);
  }
  EXPECT_EQ(model.GetEdgesAmount(), 15);
  EXPECT_EQ(model.GetVerticesAmount(), 21);

  s21::inbound_model::parser::Parser prs1(model,"nothing.txt");
  prs1.ModelNormalizer();
  EXPECT_EQ(model.GetEdgesAmount(), 2);
  EXPECT_EQ(model.GetVerticesAmount(), 21);

  EXPECT_EQ(model.GetCenteringVector(), Vec3(-20, 10, 0));
  EXPECT_DOUBLE_EQ(model.GetScaleFactor(), 1.0 / 10);

  for (int i = 0; i < 21; i++) {
    EXPECT_LE(model[i].x, 1);
    EXPECT_LE(model[i].y, 1);
    EXPECT_LE(model[i].z, 1);
  }
  EXPECT_EQ(model(0), Edge(1, 1));
  EXPECT_EQ(model(1), Edge(1, 2));

  model.Clear();
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  prs1.ModelNormalizer();
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
}

TEST(Model_Parser, Parser_ParseIt_Prepare) {
  std::ifstream ifs("models/test.txt");
  EXPECT_EQ(ifs.is_open(), false);

  ifs.open("models/test.obj");
  EXPECT_EQ(ifs.is_open(), true);
  ifs.close();
}

TEST(Model_Parser, Parser_ParseIt) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::parser::Parser;

  std::string file_name;
  s21::inbound_model::Model3D model;
  Parser prs(model,file_name);

  EXPECT_THROW(prs.ParseIt(), std::ios_base::failure);
  file_name = "models/test.txt";
  prs.SetFileName(file_name);
  EXPECT_THROW(prs.ParseIt(), std::ios_base::failure);
  file_name = "models/test_2.obj";
  prs.SetFileName(file_name);
  EXPECT_NO_THROW(prs.ParseIt());
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetName(), "test_2");
  EXPECT_EQ(prs.GetFilename(),file_name);
  model.Clear();
  file_name = "models/test.obj";
  prs.SetFileName(file_name);
  model = prs.ParseIt();

  EXPECT_EQ(model.GetVerticesAmount(), 175);
  double check_x, check_y, check_z;

  check_x = (model.GetCenteringVector().x + 1) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 2) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 3) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[0].x, check_x);
  EXPECT_DOUBLE_EQ(model[0].y, check_y);
  EXPECT_DOUBLE_EQ(model[0].z, check_z);

  check_x = (model.GetCenteringVector().x + 88) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 89) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 90) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[20].x, check_x);
  EXPECT_DOUBLE_EQ(model[20].y, check_y);
  EXPECT_DOUBLE_EQ(model[20].z, check_z);

  check_x = (model.GetCenteringVector().x + 98) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 99) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 100) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[23].x, check_x);
  EXPECT_DOUBLE_EQ(model[23].y, check_y);
  EXPECT_DOUBLE_EQ(model[23].z, check_z);

  size_t i = 24;
  for (size_t j = 101; model[i].x < (201.0 + model.GetCenteringVector().x) *
                                        model.GetScaleFactor();
       i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  i++;
  for (size_t j = 201; i < model.GetVerticesAmount(); i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  check_x = (model.GetCenteringVector().x + 250) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 251) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 252) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].x, check_x);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].y, check_y);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].z, check_z);

  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[124].x, check_x);
  EXPECT_DOUBLE_EQ(model[124].y, check_y);
  EXPECT_DOUBLE_EQ(model[124].z, check_z);
  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[125].x, check_x);
  EXPECT_DOUBLE_EQ(model[125].y, check_y);
  EXPECT_DOUBLE_EQ(model[125].z, check_z);

  EXPECT_EQ(model.GetEdgesAmount(), 54);
  EXPECT_EQ(model(0), Edge(0, 3));
  EXPECT_EQ(model(1), Edge(0, 15));
  EXPECT_EQ(model(2), Edge(3, 5));
  EXPECT_EQ(model(3), Edge(5, 7));
  EXPECT_EQ(model(4), Edge(7, 8));
  EXPECT_EQ(model(5), Edge(8, 11));
  EXPECT_EQ(model(6), Edge(10, 99));
  EXPECT_EQ(model(7), Edge(11, 12));
  EXPECT_EQ(model(8), Edge(11, 13));
  EXPECT_EQ(model(9), Edge(11, 96));
  EXPECT_EQ(model(10), Edge(13, 15));
  EXPECT_EQ(model(11), Edge(16, 17));
  EXPECT_EQ(model(12), Edge(16, 18));
  EXPECT_EQ(model(13), Edge(17, 18));
  EXPECT_EQ(model(14), Edge(32, 33));
  EXPECT_EQ(model(15), Edge(32, 35));
  EXPECT_EQ(model(16), Edge(33, 35));
  EXPECT_EQ(model(17), Edge(36, 37));
  EXPECT_EQ(model(18), Edge(37, 38));
  EXPECT_EQ(model(19), Edge(38, 39));
  EXPECT_EQ(model(20), Edge(39, 40));
  EXPECT_EQ(model(21), Edge(40, 41));
  EXPECT_EQ(model(22), Edge(41, 42));
  EXPECT_EQ(model(23), Edge(42, 43));
  EXPECT_EQ(model(24), Edge(43, 44));
  EXPECT_EQ(model(25), Edge(44, 45));
  EXPECT_EQ(model(26), Edge(51, 52));
  EXPECT_EQ(model(27), Edge(52, 53));
  EXPECT_EQ(model(28), Edge(53, 54));
  EXPECT_EQ(model(29), Edge(96, 97));
  EXPECT_EQ(model(30), Edge(97, 98));
  EXPECT_EQ(model(31), Edge(98, 99));
  EXPECT_EQ(model(32), Edge(100, 101));
  EXPECT_EQ(model(33), Edge(100, 102));
  EXPECT_EQ(model(34), Edge(101, 102));
  EXPECT_EQ(model(35), Edge(109, 111));
  EXPECT_EQ(model(36), Edge(109, 124));
  EXPECT_EQ(model(37), Edge(111, 113));
  EXPECT_EQ(model(38), Edge(113, 116));
  EXPECT_EQ(model(39), Edge(116, 117));
  EXPECT_EQ(model(40), Edge(117, 119));
  EXPECT_EQ(model(41), Edge(119, 121));
  EXPECT_EQ(model(42), Edge(121, 124));
  EXPECT_EQ(model(43), Edge(124, 124));
  EXPECT_EQ(model(44), Edge(165, 165));
  EXPECT_EQ(model(45), Edge(166, 166));
  EXPECT_EQ(model(46), Edge(167, 167));
  EXPECT_EQ(model(47), Edge(168, 168));
  EXPECT_EQ(model(48), Edge(169, 169));
  EXPECT_EQ(model(49), Edge(170, 170));
  EXPECT_EQ(model(50), Edge(171, 171));
  EXPECT_EQ(model(51), Edge(172, 172));
  EXPECT_EQ(model(52), Edge(173, 173));
  EXPECT_EQ(model(53), Edge(174, 174));

  EXPECT_EQ(model.GetName(), "model_1_&_model 2");

  model=prs.GetModelRef();


  EXPECT_EQ(model.GetVerticesAmount(), 175);

  check_x = (model.GetCenteringVector().x + 1) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 2) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 3) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[0].x, check_x);
  EXPECT_DOUBLE_EQ(model[0].y, check_y);
  EXPECT_DOUBLE_EQ(model[0].z, check_z);

  check_x = (model.GetCenteringVector().x + 88) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 89) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 90) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[20].x, check_x);
  EXPECT_DOUBLE_EQ(model[20].y, check_y);
  EXPECT_DOUBLE_EQ(model[20].z, check_z);

  check_x = (model.GetCenteringVector().x + 98) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 99) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 100) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[23].x, check_x);
  EXPECT_DOUBLE_EQ(model[23].y, check_y);
  EXPECT_DOUBLE_EQ(model[23].z, check_z);

  i = 24;
  for (size_t j = 101; model[i].x < (201.0 + model.GetCenteringVector().x) *
                                        model.GetScaleFactor();
       i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  i++;
  for (size_t j = 201; i < model.GetVerticesAmount(); i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  check_x = (model.GetCenteringVector().x + 250) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 251) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 252) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].x, check_x);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].y, check_y);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].z, check_z);

  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[124].x, check_x);
  EXPECT_DOUBLE_EQ(model[124].y, check_y);
  EXPECT_DOUBLE_EQ(model[124].z, check_z);
  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[125].x, check_x);
  EXPECT_DOUBLE_EQ(model[125].y, check_y);
  EXPECT_DOUBLE_EQ(model[125].z, check_z);

  EXPECT_EQ(model.GetEdgesAmount(), 54);
  EXPECT_EQ(model(0), Edge(0, 3));
  EXPECT_EQ(model(1), Edge(0, 15));
  EXPECT_EQ(model(2), Edge(3, 5));
  EXPECT_EQ(model(3), Edge(5, 7));
  EXPECT_EQ(model(4), Edge(7, 8));
  EXPECT_EQ(model(5), Edge(8, 11));
  EXPECT_EQ(model(6), Edge(10, 99));
  EXPECT_EQ(model(7), Edge(11, 12));
  EXPECT_EQ(model(8), Edge(11, 13));
  EXPECT_EQ(model(9), Edge(11, 96));
  EXPECT_EQ(model(10), Edge(13, 15));
  EXPECT_EQ(model(11), Edge(16, 17));
  EXPECT_EQ(model(12), Edge(16, 18));
  EXPECT_EQ(model(13), Edge(17, 18));
  EXPECT_EQ(model(14), Edge(32, 33));
  EXPECT_EQ(model(15), Edge(32, 35));
  EXPECT_EQ(model(16), Edge(33, 35));
  EXPECT_EQ(model(17), Edge(36, 37));
  EXPECT_EQ(model(18), Edge(37, 38));
  EXPECT_EQ(model(19), Edge(38, 39));
  EXPECT_EQ(model(20), Edge(39, 40));
  EXPECT_EQ(model(21), Edge(40, 41));
  EXPECT_EQ(model(22), Edge(41, 42));
  EXPECT_EQ(model(23), Edge(42, 43));
  EXPECT_EQ(model(24), Edge(43, 44));
  EXPECT_EQ(model(25), Edge(44, 45));
  EXPECT_EQ(model(26), Edge(51, 52));
  EXPECT_EQ(model(27), Edge(52, 53));
  EXPECT_EQ(model(28), Edge(53, 54));
  EXPECT_EQ(model(29), Edge(96, 97));
  EXPECT_EQ(model(30), Edge(97, 98));
  EXPECT_EQ(model(31), Edge(98, 99));
  EXPECT_EQ(model(32), Edge(100, 101));
  EXPECT_EQ(model(33), Edge(100, 102));
  EXPECT_EQ(model(34), Edge(101, 102));
  EXPECT_EQ(model(35), Edge(109, 111));
  EXPECT_EQ(model(36), Edge(109, 124));
  EXPECT_EQ(model(37), Edge(111, 113));
  EXPECT_EQ(model(38), Edge(113, 116));
  EXPECT_EQ(model(39), Edge(116, 117));
  EXPECT_EQ(model(40), Edge(117, 119));
  EXPECT_EQ(model(41), Edge(119, 121));
  EXPECT_EQ(model(42), Edge(121, 124));
  EXPECT_EQ(model(43), Edge(124, 124));
  EXPECT_EQ(model(44), Edge(165, 165));
  EXPECT_EQ(model(45), Edge(166, 166));
  EXPECT_EQ(model(46), Edge(167, 167));
  EXPECT_EQ(model(47), Edge(168, 168));
  EXPECT_EQ(model(48), Edge(169, 169));
  EXPECT_EQ(model(49), Edge(170, 170));
  EXPECT_EQ(model(50), Edge(171, 171));
  EXPECT_EQ(model(51), Edge(172, 172));
  EXPECT_EQ(model(52), Edge(173, 173));
  EXPECT_EQ(model(53), Edge(174, 174));

  EXPECT_EQ(model.GetName(), "model_1_&_model 2");

  s21::inbound_model::Model3D model_2;

  prs.SetModelRef(model_2);
  model=prs.GetModelRef();
  EXPECT_EQ(model.GetEdgesAmount(),0);
  EXPECT_EQ(model.GetVerticesAmount(),0);
}

TEST(Model_Parser, ModelParser_ParseModelFromFile_pointer) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  std::string file_name;
  std::unique_ptr<s21::inbound_model::Model3D> model;
  EXPECT_THROW(model = ParseModelFromFile(file_name), std::ios_base::failure);
  file_name = "models/test.txt";
  EXPECT_THROW(model = ParseModelFromFile(file_name), std::ios_base::failure);
  file_name = "models/test.obj";
  EXPECT_NO_THROW(model = ParseModelFromFile(file_name));

  EXPECT_EQ(model->GetVerticesAmount(), 175);
  double check_x, check_y, check_z;

  check_x = (model->GetCenteringVector().x + 1) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 2) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 3) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[0].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[0].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[0].z, check_z);

  check_x = (model->GetCenteringVector().x + 88) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 89) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 90) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[20].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[20].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[20].z, check_z);

  check_x = (model->GetCenteringVector().x + 98) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 99) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 100) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[23].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[23].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[23].z, check_z);

  size_t i = 24;
  for (size_t j = 101; (*model)[i].x < (201.0 + model->GetCenteringVector().x) *
                                           model->GetScaleFactor();
       i++, j++) {
    check_x = (model->GetCenteringVector().x + j) * model->GetScaleFactor();
    check_y = (model->GetCenteringVector().y + j + 1) * model->GetScaleFactor();
    check_z = (model->GetCenteringVector().z + j + 2) * model->GetScaleFactor();
    EXPECT_DOUBLE_EQ((*model)[i].x, check_x);
    EXPECT_DOUBLE_EQ((*model)[i].y, check_y);
    EXPECT_DOUBLE_EQ((*model)[i].z, check_z);
  }
  i++;
  for (size_t j = 201; i < model->GetVerticesAmount(); i++, j++) {
    check_x = (model->GetCenteringVector().x + j) * model->GetScaleFactor();
    check_y = (model->GetCenteringVector().y + j + 1) * model->GetScaleFactor();
    check_z = (model->GetCenteringVector().z + j + 2) * model->GetScaleFactor();
    EXPECT_DOUBLE_EQ((*model)[i].x, check_x);
    EXPECT_DOUBLE_EQ((*model)[i].y, check_y);
    EXPECT_DOUBLE_EQ((*model)[i].z, check_z);
  }
  check_x = (model->GetCenteringVector().x + 250) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 251) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 252) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[model->GetVerticesAmount() - 1].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[model->GetVerticesAmount() - 1].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[model->GetVerticesAmount() - 1].z, check_z);

  check_x = (model->GetCenteringVector().x + 201) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 202) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 203) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[124].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[124].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[124].z, check_z);
  check_x = (model->GetCenteringVector().x + 201) * model->GetScaleFactor();
  check_y = (model->GetCenteringVector().y + 202) * model->GetScaleFactor();
  check_z = (model->GetCenteringVector().z + 203) * model->GetScaleFactor();
  EXPECT_DOUBLE_EQ((*model)[125].x, check_x);
  EXPECT_DOUBLE_EQ((*model)[125].y, check_y);
  EXPECT_DOUBLE_EQ((*model)[125].z, check_z);

  EXPECT_EQ(model->GetEdgesAmount(), 54);
  EXPECT_EQ((*model)(0), Edge(0, 3));
  EXPECT_EQ((*model)(1), Edge(0, 15));
  EXPECT_EQ((*model)(2), Edge(3, 5));
  EXPECT_EQ((*model)(3), Edge(5, 7));
  EXPECT_EQ((*model)(4), Edge(7, 8));
  EXPECT_EQ((*model)(5), Edge(8, 11));
  EXPECT_EQ((*model)(6), Edge(10, 99));
  EXPECT_EQ((*model)(7), Edge(11, 12));
  EXPECT_EQ((*model)(8), Edge(11, 13));
  EXPECT_EQ((*model)(9), Edge(11, 96));
  EXPECT_EQ((*model)(10), Edge(13, 15));
  EXPECT_EQ((*model)(11), Edge(16, 17));
  EXPECT_EQ((*model)(12), Edge(16, 18));
  EXPECT_EQ((*model)(13), Edge(17, 18));
  EXPECT_EQ((*model)(14), Edge(32, 33));
  EXPECT_EQ((*model)(15), Edge(32, 35));
  EXPECT_EQ((*model)(16), Edge(33, 35));
  EXPECT_EQ((*model)(17), Edge(36, 37));
  EXPECT_EQ((*model)(18), Edge(37, 38));
  EXPECT_EQ((*model)(19), Edge(38, 39));
  EXPECT_EQ((*model)(20), Edge(39, 40));
  EXPECT_EQ((*model)(21), Edge(40, 41));
  EXPECT_EQ((*model)(22), Edge(41, 42));
  EXPECT_EQ((*model)(23), Edge(42, 43));
  EXPECT_EQ((*model)(24), Edge(43, 44));
  EXPECT_EQ((*model)(25), Edge(44, 45));
  EXPECT_EQ((*model)(26), Edge(51, 52));
  EXPECT_EQ((*model)(27), Edge(52, 53));
  EXPECT_EQ((*model)(28), Edge(53, 54));
  EXPECT_EQ((*model)(29), Edge(96, 97));
  EXPECT_EQ((*model)(30), Edge(97, 98));
  EXPECT_EQ((*model)(31), Edge(98, 99));
  EXPECT_EQ((*model)(32), Edge(100, 101));
  EXPECT_EQ((*model)(33), Edge(100, 102));
  EXPECT_EQ((*model)(34), Edge(101, 102));
  EXPECT_EQ((*model)(35), Edge(109, 111));
  EXPECT_EQ((*model)(36), Edge(109, 124));
  EXPECT_EQ((*model)(37), Edge(111, 113));
  EXPECT_EQ((*model)(38), Edge(113, 116));
  EXPECT_EQ((*model)(39), Edge(116, 117));
  EXPECT_EQ((*model)(40), Edge(117, 119));
  EXPECT_EQ((*model)(41), Edge(119, 121));
  EXPECT_EQ((*model)(42), Edge(121, 124));
  EXPECT_EQ((*model)(43), Edge(124, 124));
  EXPECT_EQ((*model)(44), Edge(165, 165));
  EXPECT_EQ((*model)(45), Edge(166, 166));
  EXPECT_EQ((*model)(46), Edge(167, 167));
  EXPECT_EQ((*model)(47), Edge(168, 168));
  EXPECT_EQ((*model)(48), Edge(169, 169));
  EXPECT_EQ((*model)(49), Edge(170, 170));
  EXPECT_EQ((*model)(50), Edge(171, 171));
  EXPECT_EQ((*model)(51), Edge(172, 172));
  EXPECT_EQ((*model)(52), Edge(173, 173));
  EXPECT_EQ((*model)(53), Edge(174, 174));

  EXPECT_EQ(model->GetName(), "model_1_&_model 2");
}

TEST(Model_Parser, ModelParser_ParseModelFromFile_reference) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  std::string file_name;
  s21::inbound_model::Model3D model;

  EXPECT_THROW(ParseModelFromFile(model, file_name), std::ios_base::failure);
  file_name = "models/test.txt";
  EXPECT_THROW(ParseModelFromFile(model, file_name), std::ios_base::failure);
  file_name = "models/test.obj";
  EXPECT_NO_THROW(ParseModelFromFile(model, file_name));

  EXPECT_EQ(model.GetVerticesAmount(), 175);
  double check_x, check_y, check_z;

  check_x = (model.GetCenteringVector().x + 1) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 2) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 3) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[0].x, check_x);
  EXPECT_DOUBLE_EQ(model[0].y, check_y);
  EXPECT_DOUBLE_EQ(model[0].z, check_z);

  check_x = (model.GetCenteringVector().x + 88) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 89) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 90) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[20].x, check_x);
  EXPECT_DOUBLE_EQ(model[20].y, check_y);
  EXPECT_DOUBLE_EQ(model[20].z, check_z);

  check_x = (model.GetCenteringVector().x + 98) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 99) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 100) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[23].x, check_x);
  EXPECT_DOUBLE_EQ(model[23].y, check_y);
  EXPECT_DOUBLE_EQ(model[23].z, check_z);

  size_t i = 24;
  for (size_t j = 101; model[i].x < (201.0 + model.GetCenteringVector().x) *
                                        model.GetScaleFactor();
       i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  i++;
  for (size_t j = 201; i < model.GetVerticesAmount(); i++, j++) {
    check_x = (model.GetCenteringVector().x + j) * model.GetScaleFactor();
    check_y = (model.GetCenteringVector().y + j + 1) * model.GetScaleFactor();
    check_z = (model.GetCenteringVector().z + j + 2) * model.GetScaleFactor();
    EXPECT_DOUBLE_EQ(model[i].x, check_x);
    EXPECT_DOUBLE_EQ(model[i].y, check_y);
    EXPECT_DOUBLE_EQ(model[i].z, check_z);
  }
  check_x = (model.GetCenteringVector().x + 250) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 251) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 252) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].x, check_x);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].y, check_y);
  EXPECT_DOUBLE_EQ(model[model.GetVerticesAmount() - 1].z, check_z);

  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[124].x, check_x);
  EXPECT_DOUBLE_EQ(model[124].y, check_y);
  EXPECT_DOUBLE_EQ(model[124].z, check_z);
  check_x = (model.GetCenteringVector().x + 201) * model.GetScaleFactor();
  check_y = (model.GetCenteringVector().y + 202) * model.GetScaleFactor();
  check_z = (model.GetCenteringVector().z + 203) * model.GetScaleFactor();
  EXPECT_DOUBLE_EQ(model[125].x, check_x);
  EXPECT_DOUBLE_EQ(model[125].y, check_y);
  EXPECT_DOUBLE_EQ(model[125].z, check_z);

  EXPECT_EQ(model.GetEdgesAmount(), 54);
  EXPECT_EQ(model(0), Edge(0, 3));
  EXPECT_EQ(model(1), Edge(0, 15));
  EXPECT_EQ(model(2), Edge(3, 5));
  EXPECT_EQ(model(3), Edge(5, 7));
  EXPECT_EQ(model(4), Edge(7, 8));
  EXPECT_EQ(model(5), Edge(8, 11));
  EXPECT_EQ(model(6), Edge(10, 99));
  EXPECT_EQ(model(7), Edge(11, 12));
  EXPECT_EQ(model(8), Edge(11, 13));
  EXPECT_EQ(model(9), Edge(11, 96));
  EXPECT_EQ(model(10), Edge(13, 15));
  EXPECT_EQ(model(11), Edge(16, 17));
  EXPECT_EQ(model(12), Edge(16, 18));
  EXPECT_EQ(model(13), Edge(17, 18));
  EXPECT_EQ(model(14), Edge(32, 33));
  EXPECT_EQ(model(15), Edge(32, 35));
  EXPECT_EQ(model(16), Edge(33, 35));
  EXPECT_EQ(model(17), Edge(36, 37));
  EXPECT_EQ(model(18), Edge(37, 38));
  EXPECT_EQ(model(19), Edge(38, 39));
  EXPECT_EQ(model(20), Edge(39, 40));
  EXPECT_EQ(model(21), Edge(40, 41));
  EXPECT_EQ(model(22), Edge(41, 42));
  EXPECT_EQ(model(23), Edge(42, 43));
  EXPECT_EQ(model(24), Edge(43, 44));
  EXPECT_EQ(model(25), Edge(44, 45));
  EXPECT_EQ(model(26), Edge(51, 52));
  EXPECT_EQ(model(27), Edge(52, 53));
  EXPECT_EQ(model(28), Edge(53, 54));
  EXPECT_EQ(model(29), Edge(96, 97));
  EXPECT_EQ(model(30), Edge(97, 98));
  EXPECT_EQ(model(31), Edge(98, 99));
  EXPECT_EQ(model(32), Edge(100, 101));
  EXPECT_EQ(model(33), Edge(100, 102));
  EXPECT_EQ(model(34), Edge(101, 102));
  EXPECT_EQ(model(35), Edge(109, 111));
  EXPECT_EQ(model(36), Edge(109, 124));
  EXPECT_EQ(model(37), Edge(111, 113));
  EXPECT_EQ(model(38), Edge(113, 116));
  EXPECT_EQ(model(39), Edge(116, 117));
  EXPECT_EQ(model(40), Edge(117, 119));
  EXPECT_EQ(model(41), Edge(119, 121));
  EXPECT_EQ(model(42), Edge(121, 124));
  EXPECT_EQ(model(43), Edge(124, 124));
  EXPECT_EQ(model(44), Edge(165, 165));
  EXPECT_EQ(model(45), Edge(166, 166));
  EXPECT_EQ(model(46), Edge(167, 167));
  EXPECT_EQ(model(47), Edge(168, 168));
  EXPECT_EQ(model(48), Edge(169, 169));
  EXPECT_EQ(model(49), Edge(170, 170));
  EXPECT_EQ(model(50), Edge(171, 171));
  EXPECT_EQ(model(51), Edge(172, 172));
  EXPECT_EQ(model(52), Edge(173, 173));
  EXPECT_EQ(model(53), Edge(174, 174));

  EXPECT_EQ(model.GetName(), "model_1_&_model 2");
}

// cube_first.obj
TEST(Model_Parser, ObjectFiles_SimpleModel) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  s21::inbound_model::Model3D model;
  EXPECT_NO_THROW(ParseModelFromFile(model, "models/cube_first.obj"));

  EXPECT_EQ(model.GetName(), "cube_first");

  EXPECT_DOUBLE_EQ(model[0].x, 1);
  EXPECT_DOUBLE_EQ(model[0].y, 1);
  EXPECT_DOUBLE_EQ(model[0].z, -1);

  EXPECT_DOUBLE_EQ(model[1].x, 1);
  EXPECT_DOUBLE_EQ(model[1].y, -1);
  EXPECT_DOUBLE_EQ(model[1].z, -1);

  EXPECT_DOUBLE_EQ(model[2].x, 1);
  EXPECT_DOUBLE_EQ(model[2].y, 1);
  EXPECT_DOUBLE_EQ(model[2].z, 1);

  EXPECT_DOUBLE_EQ(model[3].x, 1);
  EXPECT_DOUBLE_EQ(model[3].y, -1);
  EXPECT_DOUBLE_EQ(model[3].z, 1);

  EXPECT_DOUBLE_EQ(model[4].x, -1);
  EXPECT_DOUBLE_EQ(model[4].y, 1);
  EXPECT_DOUBLE_EQ(model[4].z, -1);

  EXPECT_DOUBLE_EQ(model[5].x, -1);
  EXPECT_DOUBLE_EQ(model[5].y, -1);
  EXPECT_DOUBLE_EQ(model[5].z, -1);

  EXPECT_DOUBLE_EQ(model[6].x, -1);
  EXPECT_DOUBLE_EQ(model[6].y, 1);
  EXPECT_DOUBLE_EQ(model[6].z, 1);

  EXPECT_DOUBLE_EQ(model[7].x, -1);
  EXPECT_DOUBLE_EQ(model[7].y, -1);
  EXPECT_DOUBLE_EQ(model[7].z, 1);

  EXPECT_EQ(model(0), Edge(0, 1));
  EXPECT_EQ(model(1), Edge(0, 2));
  EXPECT_EQ(model(2), Edge(0, 3));
  EXPECT_EQ(model(3), Edge(0, 4));
  EXPECT_EQ(model(4), Edge(1, 3));
  EXPECT_EQ(model(5), Edge(1, 4));
  EXPECT_EQ(model(6), Edge(1, 5));
  EXPECT_EQ(model(7), Edge(1, 7));
  EXPECT_EQ(model(8), Edge(2, 3));
  EXPECT_EQ(model(9), Edge(2, 4));
  EXPECT_EQ(model(10), Edge(2, 6));
  EXPECT_EQ(model(11), Edge(2, 7));
  EXPECT_EQ(model(12), Edge(3, 7));
  EXPECT_EQ(model(13), Edge(4, 5));
  EXPECT_EQ(model(14), Edge(4, 6));
  EXPECT_EQ(model(15), Edge(5, 6));
  EXPECT_EQ(model(16), Edge(5, 7));
  EXPECT_EQ(model(17), Edge(6, 7));
}

/**
 * Redundant test (unless new test / visualize method found).
TEST(Model_Parser, ObjectFiles_cubecarcas){
    using s21::inbound_model::Parser;
    using s21::inbound_model::Edge;

    s21::inbound_model::Model3D model;
    EXPECT_NO_THROW(Parser(model,"models/cubecarcas.obj"));

    EXPECT_EQ(model.GetName(),"cubecarcas");
    EXPECT_DOUBLE_EQ(model.GetVerticesAmount(),72 );
}
*/

/**
 * This test can be updated using ANY visualization way.
 * Object with medium vertices amount.
 * cuberubik.obj
 * T ~ 0,6 seconds
 */
TEST(Model_Parser, ObjectFiles_MiddleVerticesAmountModel) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  s21::inbound_model::Model3D model;
  EXPECT_NO_THROW(ParseModelFromFile(model, "models/cuberubik.obj"));

  EXPECT_EQ(model.GetName(), "cuberubik");
  EXPECT_DOUBLE_EQ(model.GetVerticesAmount(), 6696);
}

/**
 * This test can be updated using ANY visualization way.
 * Object with high vertices amount.
 * Dog.obj
 * T ~ 28 seconds
 * @warning For valgrind testing this testcase
 * (ObjectFiles_HighVerticesAmountModel) must be commented
 * or removed.
 */
TEST(Model_Parser, ObjectFiles_HighVerticesAmountModel) {
  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  s21::inbound_model::Model3D model;
  EXPECT_NO_THROW(ParseModelFromFile(model, "models/Dog.obj"));

  EXPECT_EQ(model.GetName(), "Dog");
  EXPECT_DOUBLE_EQ(model.GetVerticesAmount(), 49714);
}

/**
 * This test can be updated using ANY visualization way.
 * Object with negative vertex references.
 * skull.obj
 * T ~ 0,6 seconds
 */
TEST(Model_Parser, ObjectFiles_NegativeVertexReferenceModel) {

  using s21::inbound_model::Edge;
  using s21::inbound_model::ParseModelFromFile;

  s21::inbound_model::Model3D model;
  EXPECT_NO_THROW(ParseModelFromFile(model, "models/skull.obj"));

  EXPECT_EQ(model.GetName(), "skull");
  EXPECT_DOUBLE_EQ(model.GetVerticesAmount(), 6122);
  EXPECT_EQ(model(model.GetEdgesAmount() - 1), Edge(6119, 6121));
}