#ifndef SRC_VIEW_GUI_CAPTURE_CAPTURER_H
#define SRC_VIEW_GUI_CAPTURE_CAPTURER_H

#include <array>
#include <string>
#include <string_view>

namespace gui::capture {
struct FileType {
  std::string_view type;
  std::string_view tag;

  constexpr FileType(std::string_view type_, std::string_view tag_)
      : type(type_), tag(tag_) {}
};

/**
 * @note Child subclasses must have their own kTypeList and kTypeAmount
 * constants, and override GetDefaultFileName() function.
 */
template <typename ChildClass>
class Capturer {
 public:
  Capturer();

  int GetActiveType() const;
  void SetActiveType(int type_);
  const std::string& GetFileName() const;
  /**
   * @return False if the file_name_ can't be set.
   */
  bool SetFileName(const std::string& file_name_);
  virtual const std::string GetDefaultFileName() const = 0;
  /**
   * @note The list of types has the folowing structure: type_1 (tag_1);;type_2
   * (tag_2) etc.
   */
  const std::string GetTypeList() const;

 protected:
  /**
   * @brief Checks the file_name_: if it's empty, are there any files with same
   * name, does it has tag.
   * @throw If the file_name_ is empty throws std::runtime_error.
   * @return New fixed filename with added tag.
   */
  const std::string FixFileName(const std::string& file_name_) const;

  static constexpr const char* kCaptureLocation = "captures";

  int m_active_type;
  std::string m_file_name;

 private:
  static constexpr int kTypeAmount = 1;
  static constexpr std::array<FileType, kTypeAmount> kTypeList = {
      FileType{"TYPE", ".type"}};
};
}  // namespace gui::capture

#include "capture_src/capturer.tpp"

#endif  // SRC_VIEW_GUI_CAPTURE_CAPTURER_H