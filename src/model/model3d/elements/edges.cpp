
#include "mesh.h"

namespace s21::inbound_model {

// Edge methods

Edge::Edge(size_t beg_, size_t end_) {
  if (beg_ > end_) {
    begin = end_;
    end = beg_;
  } else {
    begin = beg_;
    end = end_;
  }
}

Edge::Edge(const Edge& other) : begin(other.begin), end(other.end) {}

Edge& Edge::operator=(const Edge& other) {
  begin = other.begin;
  end = other.end;
  return *this;
}

bool Edge::operator==(const Edge& other) const {
  return this->begin == other.begin && this->end == other.end;
}

bool Edge::operator!=(const Edge& other) const { return !(*this == other); }

bool Edge::operator<(const Edge& other) const {
  return this->begin < other.begin ||
         (this->begin == other.begin && this->end < other.end);
}

bool Edge::operator>(const Edge& other) const {
  return this->begin > other.begin ||
         (this->begin == other.begin && this->end > other.end);
}

bool Edge::operator<=(const Edge& other) const {
  return (*this < other) || (*this == other);
}

bool Edge::operator>=(const Edge& other) const {
  return (*this > other) || (*this == other);
}

// Edges methods

std::vector<Edge>& Edges::operator*() { return edges; }

std::vector<Edge>* Edges::operator->() { return &edges; }

const std::vector<Edge>& Edges::operator*() const { return edges; }

const std::vector<Edge>* Edges::operator->() const { return &edges; }

void Edges::Sort() {
  if (edges.size() > 1) QuickSort(0, edges.size() - 1);
}

void Edges::QuickSort(size_t first, size_t last) {
  if (first < last) {
    size_t left = first, right = last, middle = (first + last) / 2;
    Edge pivot = edges[middle];
    do {
      while (left < last && edges[left] < pivot) {
        left++;
      }
      while (right > first && edges[right] > pivot) {
        right--;
      }
      if (left <= right) {
        Swap(left, right);
        if (left < last) left++;
        if (right > first) right--;
      }

    } while (left <= right);
    QuickSort(left, last);
    QuickSort(first, right);
  }
}

void Edges::Swap(size_t first, size_t last) {
  auto temp_edge = edges[first];
  edges[first] = edges[last];
  edges[last] = temp_edge;
}

void Edges::Deduplicate() {
  if (edges.size() > 1) {
    for (size_t i = edges.size() - 1; i > 0; i--) {
      if (edges[i] == edges[i - 1]) edges.erase(edges.begin() + i - 1);
    }
  }
}

void Edges::Normalize() {
  Sort();
  Deduplicate();
}
}  // namespace s21::inbound_model