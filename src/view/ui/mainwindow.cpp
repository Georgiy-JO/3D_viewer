#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../render/model_viewer.h"
#include "../../controller/model_parser_worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

