#ifndef SRC_MODEL_MODEL3D_ELEMENTS_MESH_H
#define SRC_MODEL_MODEL3D_ELEMENTS_MESH_H

#include <vector>

#include "../../../core/math/vec3.h"

namespace s21::inbound_model {

struct Edge {
  size_t begin;
  size_t end;
  Edge(size_t beg_, size_t end_);
  Edge(const Edge& other);
  ~Edge() = default;

  Edge& operator=(const Edge& other);
  bool operator==(const Edge& other) const;
  bool operator!=(const Edge& other) const;
  bool operator<(const Edge& other) const;
  bool operator>(const Edge& other) const;
  bool operator<=(const Edge& other) const;
  bool operator>=(const Edge& other) const;
};

using vectors::Vec3;

struct Vertices {
  std::vector<Vec3> vertices;
  std::vector<Vec3>& operator*();
  std::vector<Vec3>* operator->();
  const std::vector<Vec3>& operator*() const;
  const std::vector<Vec3>* operator->() const;
};

struct Edges {
  std::vector<Edge> edges;

  std::vector<Edge>& operator*();
  std::vector<Edge>* operator->();
  const std::vector<Edge>& operator*() const;
  const std::vector<Edge>* operator->() const;

  void Sort();       // Sort edges  -- ~o(n*log(n))
  void Normalize();  // Include sorting and removing duplicates -- ~o(n*log(n))

 private:
  void QuickSort(size_t first, size_t last);
  void Swap(size_t first, size_t last);
  void Deduplicate();  // ~o(n)
};

}  // namespace s21::inbound_model

#endif  // SRC_MODEL_MODEL3D_ELEMENTS_MESH_H