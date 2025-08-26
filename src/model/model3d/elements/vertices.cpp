#include "mesh.h"

namespace s21::inbound_model {

std::vector<Vec3>& Vertices::operator*() { return vertices; }
std::vector<Vec3>* Vertices::operator->() { return &vertices; }
const std::vector<Vec3>& Vertices::operator*() const { return vertices; }
const std::vector<Vec3>* Vertices::operator->() const { return &vertices; }
}  // namespace s21::inbound_model