#include "capture/screenshot_maker.h"

#include <QMessageBox>
#include <QString>
#include <stdexcept>

namespace gui::capture {

void ScreenshotMaker::Initialize(QComboBox* type_cbox_) {
  type_cbox_->clear();
  for (int i = 0; i < kTypeAmount; i++) {
    if (i == 0 || (i > 0 && kTypeList[i].type != kTypeList[i - 1].type))
      type_cbox_->addItem(kTypeList[i].type.data());
  }
  type_cbox_->setCurrentIndex(m_active_type);
}

const std::string ScreenshotMaker::GetDefaultFileName() const {
  return kCaptureLocation + std::string("/screenshot") +
         kTypeList[m_active_type].tag.data();
}

bool ScreenshotMaker::SaveScreenshot(const QPixmap& shot_,
                                     const std::string& file_name_) {
  return SetFileName(file_name_) && SaveScreenshot(shot_);
}

bool ScreenshotMaker::SaveScreenshot(const QPixmap& shot_) const {
  if (m_file_name.empty()) return false;
  int file_type = GetActiveType();
  return shot_.save(QString::fromStdString(m_file_name),
                    QString(kTypeList[file_type].type.data()).toUtf8());
}
}  // namespace gui::capture