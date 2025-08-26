#include "parsing_utils.h"

namespace s21::inbound_model {

const std::vector<std::string>& CreatePrefixArray() {
  static const std::vector<std::string> array = {
      "v",       // #0 Vertex coordinates
      "vt",      // #1 Vertex texture coordinate
      "vn",      // #2 Vertex normal vector
      "vp",      // #3 Parameter space vertex
      "f",       // #4 Face (ref to verts. Ex.: f v1/vt1/vn1 v2/vt2/vn2 ...)
      "l",       // #5 Line (sequence of verts or vert/texture pairs)
      "p",       // #6 Point (used for point clouds)
      "g",       // #7 Group name
      "o",       // #8 Object name
      "s",       // #9 Smoothing group
      "mg",      // #10 Merging group
      "mtlib",   // #11 Material library file (external .mtl file)
      "usemtl",  // #12 Use material (refers to a material in .mtl file)
      "curv",    // #13 Curve
      "curv2",   // #14 2D curve
      "surf",    // #15 Surface
      "parm",    // #16 Parameter values
      "deg",     // #17 Degree of curve or surface
      "bmat",    // #18 Basis matrix
      "step",    // #19 Steps for curve/surface
      "cstype",  // #20 Curve or surface type (`bezier`, `bspline`, `rat` etc.)
      "trim",    // #21 Trimming loop
      "hole",    // #22 Hole in surface
      "scrv",    // #23 Special curve
      "sp",      // #24 Surface patch
      "end"      // #25 End statement (for groupings or surface defs)
  };

  return array;
}

bool IsNotEOF(const int& symbol) { return symbol != EOF; }

bool IsNum(const int& symbol) {
  return IsNotEOF(symbol) && std::isdigit(static_cast<unsigned char>(symbol));
}

bool IsSpaceCh(const int& symbol) {
  return IsNotEOF(symbol) && (symbol == ' ' || symbol == '\t');
}

bool IsHash(const int& symbol) { return IsNotEOF(symbol) && symbol == '#'; }

bool IsSlash(const int& symbol) { return IsNotEOF(symbol) && symbol == '/'; }

bool IsInteger(const double& number) {
  return std::abs(number) == (size_t)(std::abs(number));
}

bool IsNonzeroInteger(const double& number) {
  return IsInteger(number) && (size_t)(std::abs(number)) != 0;
}

bool IsSpaceChHashEOF(const int& symbol) {
  return IsSpaceCh(symbol) || IsHash(symbol) || !IsNotEOF(symbol);
}

bool IsNextNumber(std::istringstream& iss) {
  int symbol = iss.get();
  bool isnum_flag = (IsNotEOF(symbol));
  if (isnum_flag) {
    isnum_flag = (symbol == '-' || IsNum(symbol));
    if (symbol == '-') {
      symbol = iss.peek();
      isnum_flag = (IsNotEOF(symbol)) && IsNum(symbol);
    }
    iss.unget();
  }
  iss.clear();
  return isnum_flag;
}

/**
 * Returns false if "from"==0 or negative index is over range.
 * "to" gets changes anyway though.
 */
bool VerticeDecoder(const double& from, size_t& to, const size_t range) {
  to = (size_t)std::abs(from);
  if (to == 0) return false;
  to -= 1;
  if (from < 0) {
    if (range <= to) {
      return false;
    } else
      to = range - to - 1;
  }
  return true;
}

void RSpaceChTrim(std::string& line) {
  line.erase(std::find_if(line.rbegin(), line.rend(),
                          [](int ch) { return !IsSpaceCh(ch); })
                 .base(),
             line.end());
}

void LSpaceChTrim(std::string& line) {
  line.erase(line.begin(), std::find_if(line.begin(), line.end(),
                                        [](int ch) { return !IsSpaceCh(ch); }));
}

void LSpaceChTrim(std::istringstream& iss) { iss >> std::ws; }

}  // namespace s21::inbound_model