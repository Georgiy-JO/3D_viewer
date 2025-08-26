#ifndef SRC_VIEW_UI_MAINWINDOW_H
#define SRC_VIEW_UI_MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void TextMessageOutput(const QString& str);
    // void TextMessageOutput(const std::string& str);    //if won't be needed - delete

   private slots:
    void on_show_model_b_clicked(bool checked);

    void on_tmpButton_clicked();

    void on_sl_move_OX_sliderMoved(int position);

   private:
    Ui::MainWindow *ui;
};
#endif // SRC_VIEW_UI_MAINWINDOW_H
