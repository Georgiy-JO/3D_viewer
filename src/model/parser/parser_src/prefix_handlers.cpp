#include "../parser.h"
namespace inbound_model::parser {
using namespace service_functions;

const std::vector<std::string>& Parser::CreatePrefixArray() {
  static const std::vector<std::string> array = {
      "v",            // #0 Vertex coordinates
      // "vt",        // #1 Vertex texture coordinate
      // "vn",        // #2 Vertex normal vector
      // "vp",        // #3 Parameter space vertex
      "f",            // #4 Face (ref to verts. Ex.: f v1/vt1/vn1 v2/vt2/vn2 ...)
      "l",            // #5 Line (sequence of verts or vert/texture pairs)
      "p",            // #6 Point (used for point clouds)
      // "g",         // #7 Group name
      "o"             // #8 Object name
      // "s",         // #9 Smoothing group
      // "mg",        // #10 Merging group
      // "mtlib",     // #11 Material library file (external .mtl file)
      // "usemtl",    // #12 Use material (refers to a material in .mtl file)
      // "curv",      // #13 Curve
      // "curv2",     // #14 2D curve
      // "surf",      // #15 Surface
      // "parm",      // #16 Parameter values
      // "deg",       // #17 Degree of curve or surface
      // "bmat",      // #18 Basis matrix
      // "step",      // #19 Steps for curve/surface
      // "cstype",    // #20 Curve or surface type (`bezier`, `bspline`, `rat` etc.)
      // "trim",      // #21 Trimming loop 
      // "hole",      // #22 Hole in surface
      // "scrv",      // #23 Special curve
      // "sp",        // #24 Surface patch
      // "end"        // #25 End statement (for groupings or surface defs)
  };
  return array;
}

bool Parser::LineStartsWithPrefix(const std::string& line,
                                  const std::string& prefix) {
  if (line.length() == 0 || prefix.length() == 0 || line[0] != prefix[0])
    return false;
  auto prefix_position = line.find(prefix);
  if (prefix_position == line.npos || prefix_position != 0) return false;
  auto next_ch_position = prefix.length();
  if (next_ch_position >= line.length() || next_ch_position == line.npos)
    return false;
  return IsSpaceCh(line[next_ch_position]);
}

void Parser::PrefixV(const std::string& line) {
  std::istringstream iss(line);
  double x = 0.0, y = 0.0, z = 0.0;

  if (iss >> x >> y >> z) {
    m_model.AddVert(x, y, z);

    LSpaceChTrim(iss);
    if (IsNextNumber(iss)) iss >> x;  // Optional 4th value
    LSpaceChTrim(iss);
    int symbol = iss.peek();
    if (!IsHash(symbol) && IsNotEOF(symbol))
      m_model.RemoveVert(m_model.GetVerticesAmount() - 1);
  }
}

void Parser::PrefixF(std::string& line) {
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
    EdgesAdder(vertices);
}

void Parser::PrefixL(const std::string& line) {
  std::vector<double> vertices;
  PrefixCommonLP(line, vertices);

  if (vertices.size() >= 2) {  // l prefix allow only 2+ vertices included
    if (EdgesAdder(vertices)) m_model.RemoveEdge(m_model.GetEdgesAmount() - 1);
  }
}

void Parser::PrefixP(const std::string& line) {
  std::vector<double> vertices;
  PrefixCommonLP(line, vertices);

  if (vertices.size() >= 1)  // p prefix allow only 1+ vertices included
    SingleVertEdgesAdder(vertices);
}

bool Parser::PrefixO(std::string& line) {
  size_t position = line.find('#');
  if (position != line.npos) line.erase(line.begin() + position, line.end());
  RSpaceChTrim(line);
  LSpaceChTrim(line);

  if (line.length() != 0)
    ModelNameSetter(line);
  else
    return false;
  return true;
}

void Parser::PrefixCommonLP(const std::string& line,
                            std::vector<double>& vertices) {
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
bool Parser::ProcessCharF(std::istringstream& iss,
                          std::vector<double>& vertices, int& next_symbol) {
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
bool Parser::ProcessCharLP(std::istringstream& iss,
                           std::vector<double>& vertices, int& next_symbol) {
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

}  // namespace inbound_model::parser