#ifndef SRC_MODEL_MODEL3D_ELEMENTS_MESH_H
#define SRC_MODEL_MODEL3D_ELEMENTS_MESH_H

#include <cstdint>
#include <vector>

#include "../../../core/math/vec3.h"

namespace inbound_model {

struct Edge {
  uint32_t begin;
  uint32_t end;
  Edge(uint32_t beg_, uint32_t end_);
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
  void QuickSort(uint32_t first, uint32_t last);
  void Swap(uint32_t first, uint32_t last);
  void Deduplicate();  // ~o(n)
};

}  // namespace inbound_model

#endif  // SRC_MODEL_MODEL3D_ELEMENTS_MESH_H