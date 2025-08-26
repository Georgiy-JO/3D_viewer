#include <iostream>

#include "parsing_utils.h"

namespace s21::inbound_model {

bool LineStartsWithPrefix(const std::string& line, const std::string& prefix) {
  if (line.length() == 0 || prefix.length() == 0) return false;
  auto prefix_position = line.find(prefix);
  if (prefix_position == line.npos || prefix_position != 0) return false;
  auto next_ch_position = prefix.length();
  if (next_ch_position >= line.length() || next_ch_position == line.npos)
    return false;
  return IsSpaceCh(line[next_ch_position]);
}

void PrefixV(Model3D& model, const std::string& line) {
  std::istringstream iss(line);
  double x = 0.0, y = 0.0, z = 0.0;

  if (iss >> x >> y >> z) {
    model.AddVert(x, y, z);

    LSpaceChTrim(iss);
    if (IsNextNumber(iss)) iss >> x;  // Optional 4th value
    LSpaceChTrim(iss);
    int symbol = iss.peek();
    if (!IsHash(symbol) && IsNotEOF(symbol))
      model.RemoveVert(model.GetVerticesAmount() - 1);
  }
}

void PrefixF(Model3D& model, std::string& line) {
  RSpaceChTrim(line);
  std::istringstream iss(line);
  int next_symbol = EOF;
  std::vector<double> vertices;

  LSpaceChTrim(iss);
  next_symbol = iss.peek();
  iss.clear();
  while (IsNotEOF(next_symbol)) {
    if (!ProcessCharF(iss, vertices, next_symbol)) break;
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
    iss.clear();
  }

  if (vertices.size() >= 3)  // f prefix allow only 3+ vertices included
    EdgesAdder(model, vertices);
}

void PrefixL(Model3D& model, const std::string& line) {
  std::vector<double> vertices;
  PrefixCommonLP(line, vertices);

  if (vertices.size() >= 2) {  // l prefix allow only 2+ vertices included
    if (EdgesAdder(model, vertices))
      model.RemoveEdge(model.GetEdgesAmount() - 1);
  }
}

void PrefixP(Model3D& model, const std::string& line) {
  std::vector<double> vertices;
  PrefixCommonLP(line, vertices);

  if (vertices.size() >= 1)  // p prefix allow only 1+ vertices included
    SingleVertEdgesAdder(model, vertices);
}

bool PrefixO(Model3D& model, std::string& line) {
  size_t position = line.find('#');
  if (position != line.npos) line.erase(line.begin() + position, line.end());
  RSpaceChTrim(line);
  LSpaceChTrim(line);

  if (line.length() != 0)
    ModelNameSetter(model, line);
  else
    return false;
  return true;
}

void PrefixCommonLP(const std::string& line, std::vector<double>& vertices) {
  std::istringstream iss(line);
  LSpaceChTrim(iss);
  int next_symbol = iss.peek();
  while (IsNotEOF(next_symbol)) {
    if (!ProcessCharLP(iss, vertices, next_symbol)) break;
    LSpaceChTrim(iss);
    next_symbol = iss.peek();
  }
}

// Allowed for vertex referencing: 3. = 3.0 = 3.
bool ProcessCharF(std::istringstream& iss, std::vector<double>& vertices,
                  int& next_symbol) {
  double number = 0;
  if (IsHash(next_symbol) || !IsNotEOF(next_symbol)) return false;

  if (!IsNextNumber(iss) || !(iss >> number) || !IsNonzeroInteger(number)) {
    vertices.clear();
    return false;
  }
  vertices.push_back(number);
  next_symbol = iss.peek();
  // End of elements: "v"
  if (IsSpaceChHashEOF(next_symbol)) return true;
  if (IsSlash(next_symbol)) {  // Process first slash
    iss.get();                 // Skip the slash
    next_symbol = iss.peek();
    iss.clear();
    if (IsNextNumber(iss)) {
      if (!(iss >> number) || !IsNonzeroInteger(number)) {
        vertices.clear();
        return false;
      }
      next_symbol = iss.peek();
      iss.clear();
      // End of elements: "v/vt"
      if (IsSpaceChHashEOF(next_symbol)) return true;
    }
    if (IsSlash(next_symbol)) {  // Process second slash
      iss.get();                 // Skip the slash
      if (IsNextNumber(iss)) {
        if (!(iss >> number) || !IsNonzeroInteger(number)) {
          vertices.clear();
          return false;
        }
        next_symbol = iss.peek();
        iss.clear();
        // End of elements: ""v//vn" or "v/vt/vn"
        if (IsSpaceChHashEOF(next_symbol)) return true;
      }
    }
  }
  vertices.clear();
  return false;
}

// Allowed for vertex referencing: 3. = 3.0 = 3.
bool ProcessCharLP(std::istringstream& iss, std::vector<double>& vertices,
                   int& next_symbol) {
  double number = 0;
  if (IsNextNumber(iss)) {
    iss >> number;
    next_symbol = iss.peek();
    iss.clear();
    if (IsNonzeroInteger(number) && IsSpaceChHashEOF(next_symbol))
      vertices.push_back(number);
    else {
      vertices.clear();
      return false;
    }
  } else if (IsHash(next_symbol))
    return false;
  else {
    vertices.clear();
    return false;
  }
  return true;
}

}  // namespace s21::inbound_model