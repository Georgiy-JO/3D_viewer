#ifndef SRC_VIEW_GUI__CAPTURE_GIF_MAKER_H
#define SRC_VIEW_GUI__CAPTURE_GIF_MAKER_H

#include <QImage>
#include <QPushButton>

#include "capturer.h"

typedef struct GifWriter GifWriter;  // forward declaration (⊙ _ ⊙ )
namespace gui::capture {

struct Dementions {
  size_t width;
  size_t height;
};

class GifMaker : public Capturer<GifMaker> {
  friend class Capturer<GifMaker>;

 public:
  GifMaker();
  ~GifMaker();
  void Initialize(QPushButton* gif_button_);

  const std::string GetDefaultFileName() const override;
  /**
   * @brief Function to start recording GIF.
   * @attention Add following frames with RecordGif(const QPicture& input_pic).
   * @attention After recording all the frames call SaveGif().
   * @attention This function ends recording of the current GIF (if there is
   * one).
   * @note This function will use the file_name that was set before (set it
   * before using it).
   */
  bool RecordGif();
  /**
   * @brief Function to start recording GIF.
   * @attention Add following frames with RecordGif(const QPicture& input_pic).
   * @attention After recording all the frames call SaveGif().
   * @note If you set new file_name_ while the gif is still recording old one
   * will be saved and new one will be created. This may damage the currently
   * recording GIF.
   */
  bool RecordGif(const std::string& file_name_);
  /**
   * @brief Function to start recording GIF and add frames to currently
   * recording gif.
   * @attention After recording all the frames call SaveGif().
   * @note If you set new file_name_ while the gif is still recording old one
   * will be saved and new one will be created. This may damage the currently
   * recording GIF. Due to that it's better to use this one only to start
   * recording, not to add new frames.
   */
  bool RecordGif(const std::string& file_name_, const QImage& input_pic);
  /**
   * @brief Function to  add frames to currently recording gif.
   * @attention After recording all the frames call SaveGif().
   */
  bool RecordGif(const QImage& input_pic);
  /**
   * @brief Saves recorded GIF.
   * @return Returns false if the GIF was not saved;
   */
  bool SaveGif();

  size_t GetFPS() const;
  size_t GetTime() const;

 private:
  static constexpr int kTypeAmount = 1;
  static constexpr std::array<FileType, kTypeAmount> kTypeList = {
      FileType{"GIF", ".gif"},
  };
  static constexpr size_t kFPS = 10;
  static constexpr size_t kTime = 5;
  static constexpr Dementions kDementions = {640, 480};

  bool m_recording;
  std::unique_ptr<GifWriter> m_gif;
};
}  // namespace gui::capture

#endif  // SRC_VIEW_GUI__CAPTURE_GIF_MAKER_H