#pragma once
#include <vector>

namespace s21 {
 using Edge=std::pair<size_t,size_t>;

  struct Edges {
        std::vector<Edge> eds;

        void sortEdges();
  }; //struct Edges

}  // namespace s21