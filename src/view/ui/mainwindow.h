#ifndef SRC_VIEW_UI_MAINWINDOW_H
#define SRC_VIEW_UI_MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "../model_controles/model_controles.h"

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

  void TextMessageOutput(const QString& str);
  // void TextMessageOutput(const std::string& str);    //if won't be needed -
  // delete
  void FileNameOutput();
  void RefreshModelView();

 private:
  static constexpr const char* kDefaultFile = "models/skull.obj";
  Ui::MainWindow* ui;
  s21::gui::controles::ModelControles m_model_controles;
  QString m_file_name;
};
}  // namespace s21::gui
#endif  // SRC_VIEW_UI_MAINWINDOW_H
