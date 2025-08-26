#include "parser.h"

namespace s21::inbound_model {

std::unique_ptr<Model3D> Parser(const std::string& file_name) {
  std::unique_ptr<Model3D> model{std::make_unique<Model3D>()};
  ParseIt(*model, file_name);
  return model;
}

void Parser(Model3D& model, const std::string& file_name) {
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
  ParseIt(model, file_name);
}

void ParseIt(Model3D& model, std::string file_name) {
  std::ifstream ifs(file_name);
  if (!ifs.is_open()) {
    ModelNormalizer(model);
    throw std::ios_base::failure("File not found: " + file_name);
  }
  auto prefix_array = CreatePrefixArray();
  std::string line{""};
  bool prefix_o_flag = false;

  while (std::getline(ifs, line)) {
    LSpaceChTrim(line);
    for (size_t i = 0; line.size() != 0 && i < prefix_array.size(); i++) {
      if (LineStartsWithPrefix(line, prefix_array[i])) {
        line.erase(0, prefix_array[i].length());
        if (prefix_array[i] == "v")
          PrefixV(model, line);
        else if (prefix_array[i] == "f")
          PrefixF(model, line);
        else if (prefix_array[i] == "l")
          PrefixL(model, line);
        else if (prefix_array[i] == "p")
          PrefixP(model, line);
        else if (prefix_array[i] == "o")
          prefix_o_flag |= PrefixO(model, line);
        break;
      }
    }
  }
  file_name.erase((file_name.size() - 4), 4);
  file_name.erase(
      file_name.begin(),
      (std::find_if(file_name.rbegin(), file_name.rend(), [](int ch) {
        return IsSlash(ch);
      })).base());
  if (!prefix_o_flag) ModelNameSetter(model, file_name);
  ifs.close();

  ModelNormalizer(model);
}

void ModelNormalizer(Model3D& model) {
  model.CenterScale();
  // model.AddSingleVertEdges();  // may become needed
  model.ManageEdges();
}

}  // namespace s21::inbound_model
