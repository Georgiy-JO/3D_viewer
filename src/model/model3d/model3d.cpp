#include "model3d.h"

namespace s21::inbound_model {

void Model3D::AddVert(double x_, double y_, double z_) {
  Unscale();
  Uncenter();

  (*m_vertices).push_back(Vec3(x_, y_, z_));
  UpdateBounds();
}

void Model3D::RemoveVert(size_t number) {
  if (number < (*m_vertices).size()) {
    auto removed = (*m_vertices)[number];
    (*m_vertices).erase((*m_vertices).begin() + number);
    if (IsBound(removed)) RecalculateBounds();
  }
}

void Model3D::AddEdge(size_t beg_, size_t end_) {
  (*m_edges).push_back(Edge(beg_, end_));
}

void Model3D::RemoveEdge(size_t number) {
  if (number < (*m_edges).size()) {
    (*m_edges).erase((*m_edges).begin() + number);
  }
}

size_t Model3D::GetVerticesAmount() const { return (*m_vertices).size(); }

size_t Model3D::GetEdgesAmount() const { return (*m_edges).size(); }

double Model3D::GetScaleFactor() const { return m_scale_factor; }

const Vec3& Model3D::GetCenteringVector() const { return m_centering_vector; }

void Model3D::Clear() {
  m_model_name.clear();
  (*m_vertices).clear();
  (*m_edges).clear();
  m_scale_factor = c_default_scale_factor;
  m_centering_vector = DefaultCenteringVector();
  m_bounds.clear();
}

const Vec3& Model3D::DefaultCenteringVector() const {
  static const Vec3 def_vec{0.0, 0.0, 0.0};
  return def_vec;
}

bool Model3D::IsScaled() const {
  return m_scale_factor != c_default_scale_factor;
}

bool Model3D::IsCentered() const {
  return m_centering_vector != DefaultCenteringVector();
}

void Model3D::Unscale() {
  if (IsScaled()) {
    Scale(c_default_scale_factor / m_scale_factor);
    m_scale_factor = c_default_scale_factor;
  }
}

void Model3D::Uncenter() {
  if (IsCentered()) {
    Center(DefaultCenteringVector() - m_centering_vector);
    m_centering_vector = DefaultCenteringVector();
  }
}

double Model3D::Scale() {
  if (!IsScaled()) {
    SetScaleFactor();
    if (IsScaled()) Scale(m_scale_factor);
  }
  return m_scale_factor;
}

Vec3 Model3D::Center() {
  if (!IsCentered()) {
    SetCenteringVector();
    if (IsCentered()) Center(m_centering_vector);
  }
  return m_centering_vector;
}

void Model3D::SetScaleFactor() {
  using std::abs, std::max;
  double max_delta =
      max({abs(m_bounds.x.max), abs(m_bounds.x.min), abs(m_bounds.y.max),
           abs(m_bounds.y.min), abs(m_bounds.z.max), abs(m_bounds.z.min)});
  if (max_delta > c_default_scale_factor)
    m_scale_factor = c_default_scale_factor / max_delta;
}

void Model3D::SetCenteringVector() {
  m_centering_vector =
      DefaultCenteringVector() - Vec3((m_bounds.x.max + m_bounds.x.min) / 2.0,
                                      (m_bounds.y.max + m_bounds.y.min) / 2.0,
                                      (m_bounds.z.max + m_bounds.z.min) / 2.0);
}

void Model3D::Scale(double factor) {
  for (auto& vert : m_vertices.vertices) {
    vert *= factor;
  }
  ScaleBounds(factor);
}

void Model3D::Center(const Vec3& vec) {
  for (auto& vert : m_vertices.vertices) {
    vert += vec;
  }
  CenterBounds(vec);
}

const Vec3& Model3D::operator[](size_t number) const {
  if (number < (*m_vertices).size())
    return (*m_vertices)[number];
  else
    throw std::out_of_range("Vertices index is out of range.");
}

const Edge& Model3D::operator()(size_t number) const {
  if (number < (*m_edges).size())
    return (*m_edges)[number];
  else
    throw std::out_of_range("Edges index is out of range.");
}

void Model3D::ScaleBounds(double factor) {
  m_bounds.x *= factor;
  m_bounds.y *= factor;
  m_bounds.z *= factor;
}

void Model3D::CenterBounds(const Vec3& vec) {
  m_bounds.x += vec.x;
  m_bounds.y += vec.y;
  m_bounds.z += vec.z;
}

bool Model3D::IsBound(const Vec3& vec) const {
  return vec.x == m_bounds.x.min || vec.x == m_bounds.x.max ||
         vec.y == m_bounds.y.min || vec.y == m_bounds.y.max ||
         vec.z == m_bounds.z.min || vec.z == m_bounds.z.max;
}

void Model3D::UpdateBounds() {
  if ((*m_vertices).size() == 1)
    SetBoundsFirst();
  else
    SetBoundsVect((*m_vertices).back());
}

/* If this function will be made public, it needs to get !(*m_vertices).empty()
 * check*/
void Model3D::RecalculateBounds() {
  SetBoundsFirst();
  for (auto& vect : (*m_vertices)) {
    SetBoundsVect(vect);
  }
}

void Model3D::SetBoundsFirst() {
  Vec3 first_vec = (*m_vertices)[0];
  m_bounds.x.min = first_vec.x;
  m_bounds.x.max = first_vec.x;
  m_bounds.y.min = first_vec.y;
  m_bounds.y.max = first_vec.y;
  m_bounds.z.min = first_vec.z;
  m_bounds.z.max = first_vec.z;
}

void Model3D::SetBoundsVect(const Vec3& vect) {
  if (vect.x < m_bounds.x.min) m_bounds.x.min = vect.x;
  if (vect.x > m_bounds.x.max) m_bounds.x.max = vect.x;
  if (vect.y < m_bounds.y.min) m_bounds.y.min = vect.y;
  if (vect.y > m_bounds.y.max) m_bounds.y.max = vect.y;
  if (vect.z < m_bounds.z.min) m_bounds.z.min = vect.z;
  if (vect.z > m_bounds.z.max) m_bounds.z.max = vect.z;
}

void Model3D::AddSingleVertEdges() {
  size_t verts_amount = (*m_vertices).size();
  size_t edges_amount = (*m_edges).size();
  for (size_t i = 0, exist_flag = 0; i < verts_amount; i++) {
    exist_flag = 0;
    if (i < verts_amount / 2) {
      for (size_t j = 0; j < edges_amount; j++) {
        if ((*m_edges)[j].begin == i || (*m_edges)[j].end == i) {
          exist_flag = 1;
          break;
        }
      }
    } else {
      for (size_t j = edges_amount; j > 0; j--) {
        if ((*m_edges)[j - 1].begin == i || (*m_edges)[j - 1].end == i) {
          exist_flag = 1;
          break;
        }
      }
    }
    if (!exist_flag) AddEdge(i, i);
  }
}

void Model3D::RemoveSingleVertEdges() {
  for (size_t j = (*m_edges).size(); j > 0; j--) {
    if ((*m_edges)[j - 1].begin == (*m_edges)[j - 1].end) RemoveEdge(j - 1);
  }
}

void Model3D::SortEdges() { m_edges.Sort(); }

void Model3D::NormalizeEdges() { m_edges.Normalize(); }

void Model3D::RemoveGhostEdges() {
  if ((*m_edges).size() > 0) {
    size_t verts_amount = (*m_vertices).size();
    for (size_t i = (*m_edges).size(); i > 0; i--) {
      if ((*m_edges)[i - 1].begin >= verts_amount ||
          (*m_edges)[i - 1].end >= verts_amount)
        RemoveEdge(i - 1);
    }
  }
}

void Model3D::ManageEdges() {
  m_edges.Sort();

  auto verts_amount = (*m_vertices).size();

  for (size_t i = (*m_edges).size(); i > 0; i--) {
    if (i > 1 && (*m_edges)[i - 1] == (*m_edges)[i - 2]) {
      RemoveEdge(i - 1);
      continue;
    }
    if ((*m_edges)[i - 1].begin >= verts_amount ||
        (*m_edges)[i - 1].end >= verts_amount) {
      RemoveEdge(i - 1);
      continue;
    }
  }
}

void Model3D::SetName(const std::string& new_name) { m_model_name = new_name; }

const std::string& Model3D::GetName() { return m_model_name; }

void Model3D::CenterScale() {
  Center();
  Scale();
}
void Model3D::UnscaleUncenter() {
  Unscale();
  Uncenter();
}
}  // namespace s21::inbound_model