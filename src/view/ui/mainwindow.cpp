#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../model_viewer/model_viewer.h"
#include "../../controller/model_parser_worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sl_move_OX->setRange(0,100);
    ui->sl_move_OX->setValue(50);
    ui->sl_move_OX->setSingleStep(5);
    position_tmp=ui->sl_move_OX->value();

    ui->sl_rotate_OX->setRange(0,100);
    ui->sl_rotate_OX->setValue(50);
    ui->sl_rotate_OX->setSingleStep(5);
    position_tmp=ui->sl_rotate_OX->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_show_model_b_clicked(bool checked)
{
    (void)checked; // Suppress unused parameter warning
    TextMessageOutput(QString("button clicked"));

    using s21::controller::ModelParserWorker;
    using s21::inbound_model::Model3D;

    QString file_name = "tests/models/skull.obj"; //temp

    auto worker = new ModelParserWorker(file_name);
    QThread* thread = new QThread;

    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &ModelParserWorker::Process);

    connect(worker, &ModelParserWorker::finished, this, [this, thread, worker](std::shared_ptr<Model3D> model) {
        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        TextMessageOutput("Parsed");
        ui->mv_widget->SetModel(std::move(model));
        ui->mv_widget->update();
    });
    connect(worker, &ModelParserWorker::error, this, [this](const QString& msg) {
        TextMessageOutput("Not Parsed:"+ msg);
    });

    thread->start();    
}


void MainWindow::TextMessageOutput(const QString& str){
    ui->text_output->setText(str);
}
// void MainWindow::TextMessageOutput(const std::string& str){
//     TextMessageOutput(QString::fromStdString(str));
// }


void MainWindow::on_tmpButton_clicked()
{
    ui->mv_widget->RotateX(2);
    ui->mv_widget->update();
}


void MainWindow::on_sl_move_OX_sliderMoved(int position)
{
    int delta=position-position_tmp;
    ui->mv_widget->Translate(delta,0,0);
    ui->mv_widget->update();
    position_tmp=position;
}


void MainWindow::on_sl_rotate_OX_sliderMoved(int position)
{
    int delta=position-rotation_tmp;
    ui->mv_widget->RotateX(delta);
    ui->mv_widget->update();
    rotation_tmp=position;

}

