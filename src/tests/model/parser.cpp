#include "../../model/parser/parser.h"

#include <gtest/gtest.h>

#include <fstream>

#include "../../model/parser/model_parser.h"

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNum) {
  int ch = 'k';
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch), false);
  for (ch = 0; ch < 127; ch++) {
    if (ch <= 57 && ch >= 48)
      EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch), true);
    else
      EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNum(ch),
                false);
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
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num),
              true);
  }
  for (num = -50.1; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num),
              false);
  }
  for (num = -50.5; num < 100; num++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsInteger(num),
              false);
  }
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNonzeroInteger) {
  double num = 0.0;

  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
      false);
  for (num = -50.0; num < 0; num++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
        true);
  }
  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
      false);
  num++;
  for (; num < 100; num++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
        true);
  }
  for (num = -50.1; num < 100; num++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
        false);
  }
  for (num = -50.5; num < 100; num++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsNonzeroInteger(num),
        false);
  }
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsSpaceCh) {
  int ch = 33;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(ch),
              false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(' '),
            true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh('\t'),
            true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceCh(EOF),
            false);
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
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch),
              false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch), true);
  ch++;
  for (; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(ch),
              false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash('/'), true);
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSlash(EOF), false);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsSpaceChHashEOF) {
  int ch = 33;
  for (ch = 0; ch < '\t'; ch++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
        false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
            true);
  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsSpaceChHashEOF('\t'),
      true);
  ch++;
  for (; ch < ' '; ch++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
        false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
            true);
  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(' '),
      true);
  ch++;
  for (; ch < '#'; ch++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
        false);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
            true);
  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsSpaceChHashEOF('#'),
      true);
  ch++;
  for (; ch < 127; ch++) {
    EXPECT_EQ(
        s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(ch),
        false);
  }
  EXPECT_EQ(
      s21::inbound_model::parser::service_functions::IsSpaceChHashEOF(EOF),
      true);
}

TEST(Model_Parser, ParssingUnits_ServiseFunctions_IsNotEOF) {
  int ch = 33;
  for (ch = 0; ch < 127; ch++) {
    EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNotEOF(ch),
              true);
  }
  EXPECT_EQ(s21::inbound_model::parser::service_functions::IsNotEOF(EOF),
            false);
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

  s21::inbound_model::parser::Parser prs1(model, "nothing.txt");
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
  Parser prs(model, file_name);

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
  EXPECT_EQ(prs.GetFilename(), file_name);
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

  model = prs.GetModelRef();

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
  model = prs.GetModelRef();
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
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