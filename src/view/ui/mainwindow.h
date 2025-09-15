#ifndef SRC_VIEW_UI_MAINWINDOW_H
#define SRC_VIEW_UI_MAINWINDOW_H

#include <QDateTime>  // Для генерации уникального имени файла
#include <QMainWindow>
#include <QString>

#include "../controls/model_controls.h"
#include "../controls/model_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21::gui {
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

  void TextMessageOutput(const QString& str);
  void FileNameOutput();

  void on_bt_scree_clicked();
  void on_cb_screen_format_currentIndexChanged(int index);
  void on_bt_gif_clicked();

 private:
  void OpenGLSetting();
  template <typename Func>
  void ChangeModel(Func f);

  static constexpr const char* kDefaultFile = "models/skull.obj";
  Ui::MainWindow* ui;
  s21::gui::controls::ModelControls m_model_controls;
  s21::gui::controls::ModelSettings m_model_settings;
  QString m_file_name;

  QString m_selectedSuffix = ".bmp";  // Суффикс по умолчанию
};
}  // namespace s21::gui
#endif  // SRC_VIEW_UI_MAINWINDOW_H
