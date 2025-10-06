#include "../parser.h"
namespace inbound_model::parser {

/**
 * Returns false if "from"==0 or negative index is over range.
 * "to" gets changes anyway though.
 */
bool Parser::VerticeDecoder(const double& from, size_t& to,
                            const size_t range) {
  to = static_cast<size_t>(std::abs(from));
  if (to == 0) return false;
  to -= 1;
  if (from < 0) {
    if (range <= to) {
      return false;
    } else
      to = range - to - 1;
  }
  return true;
}

void Parser::EdgesRemover(size_t amount) {
  while (amount) {
    m_model.RemoveEdge(m_model.GetEdgesAmount() - 1);
    amount--;
  }
}

void Parser::ModelNameSetter(const std::string& name, bool clear_flag) {
  if (!name.empty()) {
    std::string new_name{""};
    if (!clear_flag && !m_model.GetName().empty())
      new_name = m_model.GetName() + "_&_";
    new_name = new_name + name;
    m_model.SetName(new_name);
  }
}

bool Parser::EdgesAdder(const std::vector<double>& vertices) {
  if (vertices.size() != 0) {
    size_t vert_1 = 0, vert_2 = 0;
    for (size_t added_amount = 0; added_amount < vertices.size() - 1;
         added_amount++) {
      if (!VerticeDecoder(vertices[added_amount], vert_1,
                          m_model.GetVerticesAmount())) {
        EdgesRemover(added_amount);
        return false;
      }
      if (!VerticeDecoder(vertices[added_amount + 1], vert_2,
                          m_model.GetVerticesAmount())) {
        EdgesRemover(added_amount);
        return false;
      }
      m_model.AddEdge(vert_1, vert_2);
    }

    VerticeDecoder(vertices[0], vert_1, m_model.GetVerticesAmount());
    VerticeDecoder(vertices[vertices.size() - 1], vert_2,
                   m_model.GetVerticesAmount());
    m_model.AddEdge(vert_1, vert_2);
    return true;
  }
  return false;
}

bool Parser::SingleVertEdgesAdder(const std::vector<double>& vertices) {
  if (vertices.size() != 0) {
    size_t vert_1 = 0;
    for (size_t added_amount = 0; added_amount < vertices.size();
         added_amount++) {
      if (!VerticeDecoder(vertices[added_amount], vert_1,
                          m_model.GetVerticesAmount())) {
        EdgesRemover(added_amount);
        return false;
      }
      m_model.AddEdge(vert_1, vert_1);
    }
    return true;
  }
  return false;
}
}  // namespace inbound_model::parser