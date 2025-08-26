
#include "../model_parser.h"

namespace s21::inbound_model {

std::unique_ptr<Model3D> ParseModelFromFile(const std::string& file_name) {
  std::unique_ptr<Model3D> model{std::make_unique<Model3D>()};
  parser::Parser prs(*model, file_name);
  prs.ParseIt();
  return model;
}

void ParseModelFromFile(Model3D& model, const std::string& file_name) {
  /**
   * @brief Possible feature of appending model with another model.
   * @note It is not included in present version due to
   * lack of actuality and complexity of realization.
   * @note The code is commented and left here in case it will
   * proof it's usefulness (or until it will ne clear
   * this feature is redundant).
   * @warning Activation of this featire requre refactoring
   * of ParseIt(...) and adding the "bool clear_flag" parameter
   * to this function.
   *
  if(clear_flag)
      model.Clear();
  else
      model.UnscaleUncenter();
  */
  model.Clear();
  parser::Parser prs(model, file_name);
  prs.ParseIt();
}
}   //s21::inbound_model