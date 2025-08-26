#include "parsing_utils.h"

namespace s21::inbound_model {

bool EdgesAdder(Model3D& model, const std::vector<double>& vertices) {
  if (vertices.size() != 0) {
    size_t vert_1 = 0, vert_2 = 0;
    for (size_t added_amount = 0; added_amount < vertices.size() - 1;
         added_amount++) {
      if (!VerticeDecoder(vertices[added_amount], vert_1,
                          model.GetVerticesAmount())) {
        EdgesRemover(model, added_amount);
        return false;
      }
      if (!VerticeDecoder(vertices[added_amount + 1], vert_2,
                          model.GetVerticesAmount())) {
        EdgesRemover(model, added_amount);
        return false;
      }
      model.AddEdge(vert_1, vert_2);
    }

    VerticeDecoder(vertices[0], vert_1, model.GetVerticesAmount());
    VerticeDecoder(vertices[vertices.size() - 1], vert_2,
                   model.GetVerticesAmount());
    model.AddEdge(vert_1, vert_2);
    return true;
  }
  return false;
}

bool SingleVertEdgesAdder(Model3D& model, const std::vector<double>& vertices) {
  if (vertices.size() != 0) {
    size_t vert_1 = 0;
    for (size_t added_amount = 0; added_amount < vertices.size();
         added_amount++) {
      if (!VerticeDecoder(vertices[added_amount], vert_1,
                          model.GetVerticesAmount())) {
        EdgesRemover(model, added_amount);
        return false;
      }
      model.AddEdge(vert_1, vert_1);
    }
    return true;
  }
  return false;
}

void EdgesRemover(Model3D& model, size_t amount) {
  while (amount) {
    model.RemoveEdge(model.GetEdgesAmount() - 1);
    amount--;
  }
}

void ModelNameSetter(Model3D& model, const std::string& name, bool clear_flag) {
  if (!name.empty()) {
    std::string new_name{""};
    if (!clear_flag && !model.GetName().empty())
      new_name = model.GetName() + "_&_";
    new_name = new_name + name;
    model.SetName(new_name);
  }
}

}  // namespace s21::inbound_model