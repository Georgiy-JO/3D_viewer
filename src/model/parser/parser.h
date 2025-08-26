#ifndef SRC_MODEL_PARSER_PARSER_H
#define SRC_MODEL_PARSER_PARSER_H

#include <fstream>
#include <memory>

#include "parsing_utils/parsing_utils.h"

namespace s21::inbound_model {

std::unique_ptr<Model3D> Parser(const std::string& file_name);
// Feature of appending existing model with another one is not present.
void Parser(Model3D& model, const std::string& file_name);
// Use a version of Parser(...) function to avoid issues.
void ParseIt(Model3D& model, std::string file_name);
/**
 * @brief This function contain a list of Model3D functions that change the
 * way a model is presented (like centering, scaling etc).
 * @note This function exist here so the list can be easily altered for
 * more suited form (due to that it is kept here and not in
 * parsing_utils/model_alterers.cpp).
 * @warning Canging this may affect the tests.
 */
void ModelNormalizer(Model3D& model);

}  // namespace s21::inbound_model
#endif  // SRC_MODEL_PARSER_PARSER_H