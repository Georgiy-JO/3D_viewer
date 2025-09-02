#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../model_viewer/model_viewer.h"
#include "../../controller/model_parser_worker.h"

namespace s21::gui{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_model_controles(),
    m_file_name(kDefaultFile)
{
    ui->setupUi(this);
    m_model_controles.Initialize(ui->sl_rotate_OX,ui->sl_rotate_OY,ui->sl_rotate_OZ,ui->sl_scale);
    ui->sl_scale->setVisible(false);
    ui->text_output->setWordWrap(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TextMessageOutput(const QString& str){
    ui->text_output->setText(str);
}
// void MainWindow::TextMessageOutput(const std::string& str){
//     TextMessageOutput(QString::fromStdString(str));
// }

void MainWindow::RefreshModelView(){
    try{
        ui->mv_widget->update();
    }
    catch(const std::exception& e){
        TextMessageOutput("Error while showing the model: "+ QString::fromStdString(e.what()));
    }
}


void MainWindow::on_sl_rotate_OX_valueChanged(int value)
{
    ui->mv_widget->RotateX(m_model_controles.GetRotateX(value));
    RefreshModelView();
}


void MainWindow::on_sl_rotate_OY_valueChanged(int value)
{
    ui->mv_widget->RotateY(m_model_controles.GetRotateY(value));
    RefreshModelView();
}


void MainWindow::on_sl_rotate_OZ_valueChanged(int value)
{
    ui->mv_widget->RotateZ(m_model_controles.GetRotateZ(value));
    RefreshModelView();
}


void MainWindow::on_sl_scale_valueChanged(int value)
{
    ui->mv_widget->Scale(m_model_controles.GetScale(value));
    RefreshModelView();
}


void MainWindow::on_bt_translate_up_pressed()
{
    ui->mv_widget->TranslateY(m_model_controles.GetPositiveTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_translate_right_pressed()
{
    ui->mv_widget->TranslateX(m_model_controles.GetPositiveTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_translate_left_pressed()
{
    ui->mv_widget->TranslateX(m_model_controles.GetNegativeTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_translate_down_pressed()
{
    ui->mv_widget->TranslateY(m_model_controles.GetNegativeTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_translate_forward_pressed()
{
    ui->mv_widget->TranslateZ(m_model_controles.GetPositiveTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_translate_backward_pressed()
{
    ui->mv_widget->TranslateZ(m_model_controles.GetNegativeTranslate());
    RefreshModelView();
}


void MainWindow::on_bt_scale_inc_pressed()
{
    ui->mv_widget->Scale(m_model_controles.GetPositiveScale());
    RefreshModelView();
}


void MainWindow::on_bt_scale_dec_pressed()
{
    ui->mv_widget->Scale(m_model_controles.GetNegativeScale());
    RefreshModelView();
}

void MainWindow::on_bt_reset_model_pressed()
{
    m_model_controles.Initialize(ui->sl_rotate_OX,ui->sl_rotate_OY,ui->sl_rotate_OZ,ui->sl_scale);
    ui->mv_widget->ResetTransformations();
    RefreshModelView();
}

void MainWindow::on_bt_file_list_clicked()
{
    QString new_file_name = QFileDialog::getOpenFileName(
        this,
        tr("Choose object file"),
        QDir::currentPath(),
        tr("Object files (*.obj)")
    );

    if(!new_file_name.isEmpty())
        m_file_name=new_file_name;
}


void MainWindow::on_bt_show_model_clicked()
{
    using s21::controller::ModelParserWorker;
    using s21::inbound_model::Model3D;


    auto worker = new ModelParserWorker(m_file_name);
    QThread* thread = new QThread;

    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &ModelParserWorker::Process);

    connect(worker, &ModelParserWorker::finished, this, [this, thread, worker](std::shared_ptr<Model3D> model) {
        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        try{
            ui->mv_widget->SetModel(std::move(model));
            TextMessageOutput(ui->mv_widget->GetModelName()+": "+ 
                QString::number(static_cast<qulonglong> (ui->mv_widget->GetVertsAmount()))+" vertices, "+
                QString::number(static_cast<qulonglong> (ui->mv_widget->GetEdgesAmount()))+" edges.");
        }
        catch(const std::exception& e){
            TextMessageOutput("Not Parsed: "+ QString::fromStdString(e.what()));
        }
        RefreshModelView();
    });
    connect(worker, &ModelParserWorker::error, this, [this](const QString& msg) {
        TextMessageOutput("Not Parsed: "+ msg);
    });
    TextMessageOutput("Model is loading");
    thread->start(); 
}
} //s21::gui


