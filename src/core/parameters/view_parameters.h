#ifndef SRC_CORE_SETTINGS_VIEW_PARAMETERS_H
#define SRC_CORE_SETTINGS_VIEW_PARAMETERS_H

#include "../math/vec4.h"
#include "../service/service.h"

namespace s21::parameters {

template <typename N>
struct Range {
  N min;
  N max;
};

/**
 * @brief Template for viewer parameters.
 *
 * @param T - main type of parameter;
 * @param N - type of parameter's elements / parent type of parameter;
 * @param min - minimal parameter/parameter element value;
 * @param max - maximal parameter/parameter element value;
 * @param Tag - tag of the parameter.
 *
 * @note That is not an independant class, it must be used with caution and
 * values passed to it must be chacked in advance.
 */
template <typename T, typename N, T default_val, N Min, N Max, const char* Tag>
class ViewParameter {
 public:
  static constexpr T kDefault{default_val};
  static constexpr Range<N> kRange{Min, Max};
  static constexpr const char* kTag = Tag;

  inline const T& GetValue() const { return m_value; }
  /**
   * @attention Does not check if the receving value is in range!
   */
  inline void SetValue(const T& value_ = kDefault) { m_value = value_; }

 private:
  T m_value = kDefault;
};

class ViewParameters {
 public:
  enum class ProjectionKind {
    kOrthographic = 0,
    kCentral = 1,
  };
  enum class VertexKind {
    kNone = 0,
    kSquare = 1,
    kCircle = 2,
  };
  enum class EdgeKind {
    kNone = 0,
    kSolid = 1,
    kDotted = 2,
  };

 public:
  inline ViewParameters() { ReadFromSettingsFile(); }
  inline ~ViewParameters() { SaveToSettingsFile(); }

  bool ReadFromSettingsFile(const std::string& file_name = kSettingsFile);
  void SetDefaults();

  inline s21::vectors::Vec4 GetBackgroundColor() const {
    return m_background_color.GetValue();
  }
  inline s21::vectors::Vec4 GetModelColor() const {
    return m_model_color.GetValue();
  }
  inline s21::parameters::ViewParameters::ProjectionKind GetProjectionKind()
      const {
    return m_projection_kind.GetValue();
  }
  inline double GetVertexSize() const { return m_vertex_size.GetValue(); }
  inline s21::parameters::ViewParameters::VertexKind GetVertexKind() const {
    return m_vertex_kind.GetValue();
  }
  inline double GetEdgeWidth() const { return m_edge_width.GetValue(); }
  inline s21::parameters::ViewParameters::EdgeKind GetEdgeKind() const {
    return m_edge_kind.GetValue();
  }

  inline s21::parameters::Range<double> GetBackgroundColorRange() const {
    return m_background_color.kRange;
  }
  inline s21::parameters::Range<double> GetModelColorRange() const {
    return m_model_color.kRange;
  }
  inline s21::parameters::Range<int> GetProjectionKindRange() const {
    return m_projection_kind.kRange;
  }
  inline s21::parameters::Range<double> GetVertexSizeRange() const {
    return m_vertex_size.kRange;
  }
  inline s21::parameters::Range<int> GetVertexKindRange() const {
    return m_vertex_kind.kRange;
  }
  inline s21::parameters::Range<double> GetEdgeWidthRange() const {
    return m_edge_width.kRange;
  }
  inline s21::parameters::Range<int> GetEdgeKindRange() const {
    return m_edge_kind.kRange;
  }

  inline void SetBackgroundColor() { m_background_color.SetValue(); }
  inline bool SetBackgroundColor(const double input_x, const double input_y,
                                 const double input_z, const double input_w) {
    return SetBackgroundColor(
        s21::vectors::Vec4(input_x, input_y, input_z, input_w));
  }
  bool SetBackgroundColor(const s21::vectors::Vec4& input);
  inline void SetModelColor() { m_model_color.SetValue(); }
  inline bool SetModelColor(const double input_x, const double input_y,
                            const double input_z, const double input_w) {
    return SetModelColor(
        s21::vectors::Vec4(input_x, input_y, input_z, input_w));
  }
  bool SetModelColor(const s21::vectors::Vec4& input);
  inline void SetProjectionKind() { m_projection_kind.SetValue(); }
  inline bool SetProjectionKind(
      const s21::parameters::ViewParameters::ProjectionKind& input) {
    return SetProjectionKind(static_cast<int>(input));
  }
  bool SetProjectionKind(const int input);
  inline void SetVertexSize() { m_vertex_size.SetValue(); }
  bool SetVertexSize(const double input);
  inline void SetVertexKind() { m_vertex_kind.SetValue(); }
  inline bool SetVertexKind(
      const s21::parameters::ViewParameters::VertexKind& input) {
    return SetVertexKind(static_cast<int>(input));
  }
  bool SetVertexKind(const int input);
  inline void SetEdgeWidth() { m_edge_width.SetValue(); }
  bool SetEdgeWidth(const double input);
  inline void SetEdgeKind() { m_edge_kind.SetValue(); }
  inline bool SetEdgeKind(
      const s21::parameters::ViewParameters::EdgeKind& input) {
    return SetEdgeKind(static_cast<int>(input));
  }
  bool SetEdgeKind(const int input);

 private:
  static constexpr const char* kSettingsFile = "view_parameters.txt";
  static constexpr const char* kSettingsFileHead =
      "# The file structure is important, it should not changed manually "
      "otherwise it may end up in settings not to be activly set.";
  static constexpr uintmax_t kMaxSettingsFileSize = 2000;  // in bytes

  static constexpr const char kBackgroundColorTag[]{"bc"};
  static constexpr const char kModelColorTag[]{"mc"};
  static constexpr const char kProjectionTag[]{"pr"};
  static constexpr const char kVertexSizeTag[]{"vs"};
  static constexpr const char kVertexKindTag[]{"vk"};
  static constexpr const char kEdgeWidthTag[]{"ew"};
  static constexpr const char kEdgeKindTag[]{"ek"};

  void SaveToSettingsFile() const;
  void ReadDataAfterTag(std::ifstream& ifs, const std::string& tag);

  /**
   * @brief Default parameters provided in case there is not settings file.
   * @note Following block contain constant parameters' elements like:
   * default values, minimal and maximal values. Furthermore, it connects
   * paramener to it's tag, set before. And sets parameters' types.
   */
  s21::parameters::ViewParameter<
      s21::vectors::Vec4,                          // parameter type
      double,                                      // parameter element type
      s21::vectors::Vec4(0.1f, 0.1f, 0.1f, 1.0f),  // default:dark gray color
      0.0, 1.0,                                    // element min max
      kBackgroundColorTag>                         // parameter's tag
      m_background_color;
  s21::parameters::ViewParameter<
      s21::vectors::Vec4,                          // parameter type
      double,                                      // element type
      s21::vectors::Vec4(0.9f, 0.8f, 0.6f, 1.0f),  // default:tan-like color
      0.0, 1.0,                                    // element min max
      kModelColorTag>                              // parameter's tag
      m_model_color;
  s21::parameters::ViewParameter<
      s21::parameters::ViewParameters::ProjectionKind,  // parameter type
      int,  // parameter's parent type
      s21::parameters::ViewParameters::ProjectionKind::kCentral,  // default
      0, 1,            // parameter min max
      kProjectionTag>  // parameter's tag
      m_projection_kind;
  s21::parameters::ViewParameter<double,          // parameter type
                                 double,          // parameter type
                                 4.0,             // default
                                 1.0, 50.0,       // parameter min max
                                 kVertexSizeTag>  // parameter's tag
      m_vertex_size;
  s21::parameters::ViewParameter<
      s21::parameters::ViewParameters::VertexKind,  // parameter type
      int,                                          // parameter's parent type
      s21::parameters::ViewParameters::VertexKind::kSquare,  // default
      0, 2,            // parameter min max
      kVertexKindTag>  // parameter's tag
      m_vertex_kind;
  s21::parameters::ViewParameter<double,         // parameter type
                                 double,         // parameter type
                                 1.0,            // default
                                 1.0, 20.0,      // parameter min max
                                 kEdgeWidthTag>  // parameter's tag
      m_edge_width;
  s21::parameters::ViewParameter<
      s21::parameters::ViewParameters::EdgeKind,  // parameter type
      int,                                        // parameter's parent type
      s21::parameters::ViewParameters::EdgeKind::kSolid,  // default
      0, 2,                                               // parameter min max
      kEdgeKindTag>                                       // parameter's tag
      m_edge_kind;
};

}  // namespace s21::parameters

#endif  // SRC_CORE_SETTINGS_VIEW_PARAMETERS_H