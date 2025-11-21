#ifndef SRC_VIEW_GUI_MAINWINDOW_MAINWINDOW_H
#define SRC_VIEW_GUI_MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "view/gui/capture/gif_maker.h"
#include "view/gui/capture/screenshot_maker.h"
#include "view/gui/controls/model_controls.h"
#include "view/gui/controls/model_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void ErrorOccured(const QString& message);
 private slots:
  void on_sl_rotate_OX_valueChanged(int value);
  void on_sl_rotate_OY_valueChanged(int value);
  void on_sl_rotate_OZ_valueChanged(int value);
  void on_bt_translate_up_pressed();
  void on_bt_translate_right_pressed();
  void on_bt_translate_left_pressed();
  void on_bt_translate_down_pressed();
  void on_bt_translate_forward_pressed();
  void on_bt_translate_backward_pressed();
  void on_sl_scale_valueChanged(int value);
  void on_bt_scale_inc_pressed();
  void on_bt_scale_dec_pressed();
  void on_bt_file_list_clicked();
  void on_bt_show_model_clicked();
  void on_bt_reset_model_pressed();

  void on_cb_projection_kind_currentIndexChanged(int index);
  void on_cb_edge_kind_currentIndexChanged(int index);
  void on_cb_vertex_kind_currentIndexChanged(int index);
  void on_sl_edge_width_valueChanged(int value);
  void on_sl_vertex_size_valueChanged(int value);
  void on_bt_model_color_clicked();
  void on_bt_background_color_clicked();
  void on_bt_reset_parameters_clicked();

  void on_bt_scree_clicked();
  void on_cb_screen_shot_format_currentIndexChanged(int index);
  void on_bt_gif_clicked();

 private:
  void TextMessageOutput(const QString& str);
  void FileNameOutput();
  void ModelDataOutput();
  void PopupMessageOutput(const QString& title_, const QString& text_);

  void OpenGLSetting();
  template <typename Func>
  void ChangeModel(Func f);

  /**
   * @note This function neet to be run due to the compatibility issues
   * caused by openGL 2.0+ vs 3.0+.
   */
  void CompatibilitySettings();

  static constexpr const char* kDefaultFile = "models/skull.obj";
  Ui::MainWindow* ui;
  gui::controls::ModelControls m_model_controls;
  gui::controls::ModelSettings m_model_settings;
  gui::capture::ScreenshotMaker m_screen_shot;
  gui::capture::GifMaker m_gif;
  QString m_file_name;
};
}  // namespace gui
#endif  // SRC_VIEW_GUI_MAINWINDOW_MAINWINDOW_H
