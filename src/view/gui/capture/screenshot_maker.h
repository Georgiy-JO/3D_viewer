#ifndef SRC_VIEW_GUI__CAPTURE_SCREENSHOT_MAKER_H
#define SRC_VIEW_GUI__CAPTURE_SCREENSHOT_MAKER_H
#include <QComboBox>
#include <QPixmap>

#include "capturer.h"

namespace gui::capture {

class ScreenshotMaker : public Capturer<ScreenshotMaker> {
  friend class Capturer<ScreenshotMaker>;

 public:
  ScreenshotMaker() : Capturer() {}
  void Initialize(QComboBox* type_cbox_);

  /**
   * @attention This function include constant default screenshot file name.
   * It includes capture location and looks following way:
   * "captures/screenshot". That may cause issues in case porting the program to
   * windows.
   */
  const std::string GetDefaultFileName() const override;
  /**
   * @return Returns false if the screenshot was not saved.
   */
  bool SaveScreenshot(const QPixmap& shot_, const std::string& file_name_);
  /**
   * @return Returns false if the screenshot was not saved.
   * @attention Uses the file_name that was set before (set it before using this
   * function).
   */
  bool SaveScreenshot(const QPixmap& shot_) const;

 private:
  static constexpr int kTypeAmount = 3;
  static constexpr std::array<FileType, kTypeAmount> kTypeList = {
      FileType{"BMP", ".bmp"}, FileType{"JPEG", ".jpg"},
      FileType{"JPEG", ".jpeg"}};
};

}  // namespace gui::capture

#endif  // SRC_VIEW_GUI__CAPTURE_SCREENSHOT_MAKER_H