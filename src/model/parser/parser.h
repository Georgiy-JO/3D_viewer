#ifndef SRC_MODEL_PARSER_PARSER_H
#define SRC_MODEL_PARSER_PARSER_H

#include <string>

#include "../model3d/model3d.h"
#include "service_functions/service_functions.h"

namespace s21::inbound_model::parser {
/**
 * @note There are service functions "ParseModelFromFile(...)" in
 * model_parser.cpp/.h that simplify working with the parser.
 */
class Parser {
 public:
  Parser(Model3D& model_, const std::string& file_name_);

  void SetFileName(const std::string& file_name_);
  void SetModelRef(Model3D& model_);
  std::string GetFilename() const;
  Model3D& GetModelRef();
  Model3D& ParseIt();
  /**
   * @brief This function contain a list of Model3D functions that change the
   * way a model is presented (like centering, scaling etc).
   * @note The list can be easily altered for more suited format (in the sake
   * of this quick access this function is keeped in parser.cpp).
   * @warning Canging this function may affect tests.
   * @note You don't need to call this function again if you used ParseIt().
   */
  void ModelNormalizer();

 private:
  // Prefix lines managing functions:

  const std::vector<std::string>& CreatePrefixArray();
  // Check if the prefix is in the beginig of the line.
  bool LineStartsWithPrefix(const std::string& line, const std::string& prefix);

  void PrefixV(const std::string& line);
  void PrefixF(std::string& line);
  void PrefixL(const std::string& line);
  void PrefixP(const std::string& line);
  bool PrefixO(std::string& line);
  void PrefixCommonLP(const std::string& line, std::vector<double>& vertices);
  bool ProcessCharF(std::istringstream& iss, std::vector<double>& vertices,
                    int& next_symbol);
  bool ProcessCharLP(std::istringstream& iss, std::vector<double>& vertices,
                     int& next_symbol);

  // Model altering functions:

  bool VerticeDecoder(const double& from, size_t& to, const size_t range);
  void EdgesRemover(size_t amount);

  void ModelNameSetter(const std::string& name, bool clear_flag = 0);
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
  bool EdgesAdder(const std::vector<double>& vertices);
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
  bool SingleVertEdgesAdder(const std::vector<double>& vertices);

  Model3D& m_model;
  std::string m_file_name;
};

}  // namespace s21::inbound_model::parser
#endif  // SRC_MODEL_PARSER_PARSER_H