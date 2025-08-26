#ifndef SRC_MODEL_PARSER_MODEL_PARSER_H
#define SRC_MODEL_PARSER_MODEL_PARSER_H

#include <memory>

#include "parser.h"

namespace s21::inbound_model {

std::unique_ptr<Model3D> ParseModelFromFile(const std::string& file_name);
// Feature of appending existing model with another one is not present.
void ParseModelFromFile(Model3D& model, const std::string& file_name);

}  // namespace s21::inbound_model
#endif  // SRC_MODEL_PARSER_MODEL_PARSER_H