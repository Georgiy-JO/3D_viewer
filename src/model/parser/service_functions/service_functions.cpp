#include "service_functions.h"

#include <algorithm>

namespace inbound_model::parser::service_functions {

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
  return std::abs(number) == static_cast<size_t>(std::abs(number));
}

bool IsNonzeroInteger(const double& number) {
  return IsInteger(number) && static_cast<size_t>(std::abs(number)) != 0;
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

}  // namespace inbound_model::parser::service_functions