#ifndef SRC_MODEL_PARSER_PARSING_UNITS_PARSING_UNITS_H
#define SRC_MODEL_PARSER_PARSING_UNITS_PARSING_UNITS_H

#include <sstream>
#include <string>

#include "../../model3d/model3d.h"

namespace s21::inbound_model {

// Service functions:

const std::vector<std::string>& CreatePrefixArray();

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

bool VerticeDecoder(const double& from, size_t& to, const size_t range);

void RSpaceChTrim(std::string& line);
void LSpaceChTrim(std::string& line);
void LSpaceChTrim(std::istringstream& iss);

// Prefix lines managing functions:

// Check if the prefix is in the beginig of the line.
bool LineStartsWithPrefix(const std::string& line, const std::string& prefix);

void PrefixV(Model3D& model, const std::string& line);
void PrefixF(Model3D& model, std::string& line);
void PrefixL(Model3D& model, const std::string& line);
void PrefixP(Model3D& model, const std::string& line);
void PrefixCommonLP(const std::string& line, std::vector<double>& vertices);
bool PrefixO(Model3D& model, std::string& line);
bool ProcessCharF(std::istringstream& iss, std::vector<double>& vertices,
                  int& next_symbol);
bool ProcessCharLP(std::istringstream& iss, std::vector<double>& vertices,
                   int& next_symbol);

// Model altering functions:

void ModelNameSetter(Model3D& model, const std::string& name,
                     bool clear_flag = 0);
/**
 * @brief Add edges to the model from a list of connected vertices.
 *
 * @note Last vertex from the list will be connected to the first one (done
 * so due to fact that most of the time that is used for face adding).
 * @note Does allow adding vertices in advance: adding edge referencing
 * vertex #5 while model still has only 4 or less vertices.
 * This allows handeling .obj files more freely.
 * Ghost edges are handled in ModelNormalizer() during parsing.
 * @note Does not allow refferensing never existing vertices:
 * will not add edge that negativly referencing vertex (-4) while
 * only 3 or less vertices exist - the whole list will not be added.
 */
bool EdgesAdder(Model3D& model, const std::vector<double>& vertices);
/**
 * @brief Add edges to the model from a list of connected vertices.
 *
 * @note All vertices in the list will be treated as single
 * vertex edge (aka. all the vertices teated like not connected ones).
 * @note Does allow adding vertices in advance: adding edge referencing
 * vertex #5 while model still has only 4 or less vertices.
 * This allows handeling .obj files more freely.
 * Ghost edges are handled in ModelNormalizer() during parsing.
 * @note Does not allow refferensing never existing vertices:
 * will not add edge that negativly referencing vertex (-4) while
 * only 3 or less vertices exist - the whole list will not be added.
 */
bool SingleVertEdgesAdder(Model3D& model, const std::vector<double>& vertices);
void EdgesRemover(Model3D& model, size_t amount);

}  // namespace s21::inbound_model

#endif  // SRC_MODEL_PARSER_PARSINGUNITS_PARSINGUNITS_H