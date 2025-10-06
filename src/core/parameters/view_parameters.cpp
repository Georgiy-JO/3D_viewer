#include "view_parameters.h"

#include <fstream>
#include <stdexcept>

namespace parameters {

bool ViewParameters::ReadFromSettingsFile(const std::string& file_name) {
  SetDefaults();
  if (!service::file::IsFileOk(file_name, kMaxSettingsFileSize))
    return false;

  std::ifstream ifs(file_name);
  if (!ifs.is_open())
    throw std::ios_base::failure(
        "Settings file can't opened (Something went terribly wrong).");

  std::string flush_line;
  int next_char = ifs.peek();
  std::string tag;

  while (service::character::IntIsNotEOF(next_char)) {
    if (service::character::IntIsHash(next_char))
      std::getline(ifs, flush_line);
    else {
      if (ifs >> tag) ReadDataAfterTag(ifs, tag);
    }
    next_char = ifs.peek();
  }
  ifs.close();
  return true;
}

void ViewParameters::SaveToSettingsFile() const {
  service::file::RemoveFile(kSettingsFile);
  std::ofstream ofs(kSettingsFile, std::ios::out);
  if (!ofs.is_open())
    throw std::ios_base::failure("Settings file can't be saved.");

  ofs << kSettingsFileHead << '\n';
  ofs << m_background_color.kTag << ' ' << m_background_color.GetValue().x
      << ' ' << m_background_color.GetValue().y << ' '
      << m_background_color.GetValue().z << ' '
      << m_background_color.GetValue().w << '\n';
  ofs << m_model_color.kTag << ' ' << m_model_color.GetValue().x << ' '
      << m_model_color.GetValue().y << ' ' << m_model_color.GetValue().z << ' '
      << m_model_color.GetValue().w << '\n';
  ofs << m_projection_kind.kTag << ' '
      << static_cast<int>(m_projection_kind.GetValue()) << '\n';
  ofs << m_vertex_size.kTag << ' ' << m_vertex_size.GetValue() << '\n';
  ofs << m_vertex_kind.kTag << ' ' << static_cast<int>(m_vertex_kind.GetValue())
      << '\n';
  ofs << m_edge_width.kTag << ' ' << m_edge_width.GetValue() << '\n';
  ofs << m_edge_kind.kTag << ' ' << static_cast<int>(m_edge_kind.GetValue());

  ofs.close();
}

void ViewParameters::SetDefaults() {
  SetBackgroundColor();
  SetModelColor();
  SetProjectionKind();
  SetVertexSize();
  SetVertexKind();
  SetEdgeWidth();
  SetEdgeKind();
}

void ViewParameters::ReadDataAfterTag(std::ifstream& ifs,
                                      const std::string& tag) {
  if (tag == m_background_color.kTag) {
    vectors::Vec4 temp_var;
    if (ifs >> temp_var.x >> temp_var.y >> temp_var.z >> temp_var.w)
      SetBackgroundColor(temp_var);
  }
  if (tag == m_model_color.kTag) {
    vectors::Vec4 temp_var;
    if (ifs >> temp_var.x >> temp_var.y >> temp_var.z >> temp_var.w)
      SetModelColor(temp_var);
  }
  if (tag == m_projection_kind.kTag) {
    int temp_var;
    if (ifs >> temp_var) SetProjectionKind(temp_var);
  }
  if (tag == m_vertex_size.kTag) {
    double temp_var;
    if (ifs >> temp_var) SetVertexSize(temp_var);
  }
  if (tag == m_vertex_kind.kTag) {
    int temp_var;
    if (ifs >> temp_var) SetVertexKind(temp_var);
  }
  if (tag == m_edge_width.kTag) {
    double temp_var;
    if (ifs >> temp_var) SetEdgeWidth(temp_var);
  }
  if (tag == m_edge_kind.kTag) {
    int temp_var;
    if (ifs >> temp_var) SetEdgeKind(temp_var);
  }
}

bool ViewParameters::SetBackgroundColor(const vectors::Vec4& input) {
  if (input.x <= m_background_color.kRange.max &&
      input.x >= m_background_color.kRange.min &&
      input.y <= m_background_color.kRange.max &&
      input.y >= m_background_color.kRange.min &&
      input.z <= m_background_color.kRange.max &&
      input.z >= m_background_color.kRange.min &&
      input.w <= m_background_color.kRange.max &&
      input.w >= m_background_color.kRange.min) {
    m_background_color.SetValue(input);
    return true;
  }
  return false;
}

bool ViewParameters::SetModelColor(const vectors::Vec4& input) {
  if (input.x <= m_model_color.kRange.max &&
      input.x >= m_model_color.kRange.min &&
      input.y <= m_model_color.kRange.max &&
      input.y >= m_model_color.kRange.min &&
      input.z <= m_model_color.kRange.max &&
      input.z >= m_model_color.kRange.min &&
      input.w <= m_model_color.kRange.max &&
      input.w >= m_model_color.kRange.min) {
    m_model_color.SetValue(input);
    return true;
  }
  return false;
}

bool ViewParameters::SetProjectionKind(const int input) {
  if (input >= m_projection_kind.kRange.min &&
      input <= m_projection_kind.kRange.max) {
    m_projection_kind.SetValue(
        static_cast<parameters::ViewParameters::ProjectionKind>(input));
    return true;
  }
  return false;
}

bool ViewParameters::SetVertexSize(const double input) {
  if (input >= m_vertex_size.kRange.min && input <= m_vertex_size.kRange.max) {
    m_vertex_size.SetValue(input);
    return true;
  }
  return false;
}

bool ViewParameters::SetVertexKind(const int input) {
  if (input >= m_vertex_kind.kRange.min && input <= m_vertex_kind.kRange.max) {
    m_vertex_kind.SetValue(
        static_cast<parameters::ViewParameters::VertexKind>(input));
    return true;
  }
  return false;
}

bool ViewParameters::SetEdgeWidth(const double input) {
  if (input >= m_edge_width.kRange.min && input <= m_edge_width.kRange.max) {
    m_edge_width.SetValue(input);
    return true;
  }
  return false;
}

bool ViewParameters::SetEdgeKind(const int input) {
  if (input >= m_edge_kind.kRange.min && input <= m_edge_kind.kRange.max) {
    m_edge_kind.SetValue(
        static_cast<parameters::ViewParameters::EdgeKind>(input));
    return true;
  }
  return false;
}

}  // namespace parameters