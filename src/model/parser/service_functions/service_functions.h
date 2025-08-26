#ifndef SRC_MODEL_PARSER_SERVICE_FUNCTIONS_SERVICE_FUNCTIONS
#define SRC_MODEL_PARSER_SERVICE_FUNCTIONS_SERVICE_FUNCTIONS

#include <sstream>

namespace s21::inbound_model::parser::service_functions {

bool IsNotEOF(const int& symbol);
bool IsNum(const int& symbol);
bool IsInteger(const double& number);
bool IsNonzeroInteger(const double& number);
// Checks if the character is tab (\t) or space ( ).
bool IsSpaceCh(const int& symbol);
bool IsHash(const int& symbol);
bool IsSlash(const int& symbol);
// Check if symbol is ' ' (space), or '\t', or '#', or EOF.
bool IsSpaceChHashEOF(const int& symbol);
bool IsNextNumber(std::istringstream& iss);

void RSpaceChTrim(std::string& line);
void LSpaceChTrim(std::string& line);
void LSpaceChTrim(std::istringstream& iss);

}  // namespace s21::inbound_model::parser::service_functions 


#endif  //SRC_MODEL_PARSER_SERVICE_FUNCTIONS_SERVICE_FUNCTIONS