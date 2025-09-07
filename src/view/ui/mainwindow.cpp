#include "mainwindow.h"

#include "../../controller/model_parser_worker.h"
#include "../model_viewer/model_viewer.h"
#include "./ui_mainwindow.h"

namespace s21::gui {
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_model_controls(),
      m_model_settings(),
      m_file_name(kDefaultFile) {

// /**
//  * @brief Setting up OpenGL settings.
//  * @note This function sets openGL settings that are usually set silently 
//  * by QT it self, but using these ourselves we ensure that QT set's openGL 
//  * right way. 
//  * @note by default Qt will indeed create an OpenGL context automatically, 
//  * whenever QOpenGLWidget is used, but: by default, it asks the system for 
//  * “whatever the driver wants to give me” (On some machines, that might mean 
//  * OpenGL 2.1 Compatibility Profile on others, it might mean Core 
//  * Profile 3.3) - the defaults are not consistent across OSes, drivers, 
//  * or even Qt builds.
//  */

//   /**
//    * @note Creates a QSurfaceFormat object, which specifies the desired 
//    * format of the OpenGL surface/context you want to create.
//    */      
  QSurfaceFormat format;
  format.setVersion(3, 3);                   // OpenGL version 3.3
//   /**
//    * @note Requests a Core Profile context (not a Compatibility profile).
//    * @note Core profile excludes old deprecated OpenGL functions 
//    * (like glBegin/glEnd), while ensures modern OpenGL behavior. This is 
//    * required for features like gl_PointCoord and modern GLSL shaders.
//    */
  format.setProfile(QSurfaceFormat::CoreProfile);
//   /**
//    * @note Requests a 24-bit depth buffer for your OpenGL context. 
//    * Depth buffer is used for z-testing, i.e., to determine which 
//    * objects are in front of others in 3D.
//    */
  format.setDepthBufferSize(24);
//   /**
//    * @note Requests an 8-bit stencil buffer.Stencil buffer is used 
//    * for advanced effects like masking, outlining, shadows, etc.
//    * @note Currently not needed in the project, but can be useful in 
//    * case he project grows.
//    */
  format.setStencilBufferSize(8);
//   /**
//    * @note Sets this QSurfaceFormat as the default for all QOpenGLWidgets
//    * and QOpenGLWindows created after this line. Ensures that your OpenGL 
//    * context will use OpenGL 3.3 Core Profile with the requested buffers.
//    */
  QSurfaceFormat::setDefaultFormat(format);
          
  ui->setupUi(this);
  m_model_controls.Initialize(ui->sl_rotate_OX, ui->sl_rotate_OY,
                               ui->sl_rotate_OZ, ui->sl_scale);
  m_model_settings.InitializeSliders(ui->sl_edge_width,
        ui->mv_widget->GetEdgeWidthRange(),ui->mv_widget->GetEdgeWidth(),
        ui->sl_vertex_size,
        ui->mv_widget->GetVertexSizeRange(),ui->mv_widget->GetVertexSize());
  m_model_settings.InitializeComboBoxes(ui->cb_projection_kind,ui->mv_widget->GetProjectionKind(),
                                      ui->cb_edge_kind, ui->mv_widget->GetEdgeKind(),
                                      ui->cb_vertex_kind,ui->mv_widget->GetVertexKind());
  ui->text_output->setWordWrap(true);
  ui->filename_output->setWordWrap(true);
  FileNameOutput();
  TextMessageOutput("");
  connect(ui->mv_widget,&s21::gui::ModelViewer::SignalPrintingError,this,&s21::gui::MainWindow::ErrorOccured);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::TextMessageOutput(const QString& str) {
  ui->text_output->setText(str);
}
// void MainWindow::TextMessageOutput(const std::string& str){
//     TextMessageOutput(QString::fromStdString(str));
// }
void MainWindow::FileNameOutput(){
  ui->filename_output->setText("File: "+ m_file_name);
}

void MainWindow::ErrorOccured(const QString& message){
  TextMessageOutput("ERROR! "+ message);
}

template <typename Func>
void MainWindow::ChangeModel(Func f) {
  try {
    f();
    /**
     * @note This one only schedules painting process, not does it right now 
     * due to that this try-catch won't handle exceptions from  painting 
     * the model, only changing (aka f()).
     */
    ui->mv_widget->update();
  } catch (const std::exception& e) {
    ErrorOccured(QString("Model changing -> ")+e.what());
  } 
}

void MainWindow::on_sl_rotate_OX_valueChanged(int value) {
  ChangeModel([this,value]{ui->mv_widget->RotateX(m_model_controls.GetRotateX(value));});
}

void MainWindow::on_sl_rotate_OY_valueChanged(int value) {
  ChangeModel([this,value]{ui->mv_widget->RotateY(m_model_controls.GetRotateY(value));});
}

void MainWindow::on_sl_rotate_OZ_valueChanged(int value) {
  ChangeModel([this,value]{ui->mv_widget->RotateZ(m_model_controls.GetRotateZ(value));});
}

void MainWindow::on_sl_scale_valueChanged(int value) {
  ChangeModel([this,value]{ui->mv_widget->Scale(m_model_controls.GetScale(value));});
}

void MainWindow::on_bt_translate_up_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateY(m_model_controls.GetPositiveTranslate());});
}

void MainWindow::on_bt_translate_right_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateX(m_model_controls.GetPositiveTranslate());});
}

void MainWindow::on_bt_translate_left_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateX(m_model_controls.GetNegativeTranslate());});
}

void MainWindow::on_bt_translate_down_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateY(m_model_controls.GetNegativeTranslate());});
}

void MainWindow::on_bt_translate_forward_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateZ(m_model_controls.GetPositiveTranslate());});
}

void MainWindow::on_bt_translate_backward_pressed() {
  ChangeModel([this]{ui->mv_widget->TranslateZ(m_model_controls.GetNegativeTranslate());});
}

void MainWindow::on_bt_scale_inc_pressed() {
  ChangeModel([this]{ui->mv_widget->Scale(m_model_controls.GetPositiveScale());});
}

void MainWindow::on_bt_scale_dec_pressed() {
  ChangeModel([this]{ui->mv_widget->Scale(m_model_controls.GetNegativeScale());});
}

void MainWindow::on_bt_reset_model_pressed() {
  m_model_controls.Initialize(ui->sl_rotate_OX, ui->sl_rotate_OY,
                               ui->sl_rotate_OZ, ui->sl_scale);
  ChangeModel([this]{ui->mv_widget->ResetTransformations();});
}

void MainWindow::on_bt_file_list_clicked() {
  QString new_file_name = QFileDialog::getOpenFileName(
      this, tr("Choose object file"), 
      QDir::currentPath(),
      tr("Object files (*.obj)"));

  if (!new_file_name.isEmpty()) m_file_name = new_file_name;
  FileNameOutput();
}

void MainWindow::on_bt_show_model_clicked() {
  using s21::controller::ModelParserWorker;
  using s21::inbound_model::Model3D;

  auto worker = new ModelParserWorker(m_file_name);
  QThread* thread = new QThread;

  worker->moveToThread(thread);
  connect(thread, &QThread::started, worker, &ModelParserWorker::Process);

  connect(
      worker, &ModelParserWorker::finished, this,
      [this, thread, worker](std::shared_ptr<Model3D> model) {
        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        try {
          ui->mv_widget->SetModel(std::move(model));
          TextMessageOutput(ui->mv_widget->GetModelName() + ": " +
                            QString::number(static_cast<qulonglong>(
                                ui->mv_widget->GetVertsAmount())) +
                            " vertices, " +
                            QString::number(static_cast<qulonglong>(
                                ui->mv_widget->GetEdgesAmount())) +
                            " edges.");
        } catch (const std::exception& e) {
          ErrorOccured("Model not set: " + QString::fromStdString(e.what()));
        }
        ChangeModel([this]{});
      });
  connect(worker, &ModelParserWorker::error, this, [this](const QString& msg) {
    ErrorOccured("Not Parsed: " + msg);
  });
  TextMessageOutput("Model is loading");
  thread->start();
}

void MainWindow::on_cb_projection_kind_currentIndexChanged(int index)
{
  ChangeModel([this,index]{ui->mv_widget->SetProjectionKind(index);});
}

void MainWindow::on_cb_edge_kind_currentIndexChanged(int index)
{
  ChangeModel([this,index]{ui->mv_widget->SetEdgeKind(index);});
}

void MainWindow::on_cb_vertex_kind_currentIndexChanged(int index)
{
  ChangeModel([this,index]{ui->mv_widget->SetVertexKind(index);});
}

void MainWindow::on_sl_edge_width_valueChanged(int value)
{
  ChangeModel([this,value]{ui->mv_widget->SetEdgeWidth(value);});
}

void MainWindow::on_sl_vertex_size_valueChanged(int value)
{
  ChangeModel([this,value]{ui->mv_widget->SetVertexSize(value);});
}

void MainWindow::on_bt_model_color_clicked()
{
  QColor new_color=QColorDialog::getColor(ui->mv_widget->GetModelColor(),this,tr("Choose model color:"));
  if(new_color.isValid())
    ChangeModel([this,new_color]{ui->mv_widget->SetModelColor(new_color);});
}

void MainWindow::on_bt_background_color_clicked()
{
  QColor new_color=QColorDialog::getColor(ui->mv_widget->GetBackgroundColor(),this,tr("Choose background color:"));
  if(new_color.isValid())
    ChangeModel([this,new_color]{ui->mv_widget->SetBackgroundColor(new_color);});
}

void MainWindow::on_bt_reset_parameters_clicked()
{
  ChangeModel([this]{ui->mv_widget->ResetParameters();});
  m_model_settings.InitializeSliders(ui->sl_edge_width,
        ui->mv_widget->GetEdgeWidthRange(),ui->mv_widget->GetEdgeWidth(),
        ui->sl_vertex_size,
        ui->mv_widget->GetVertexSizeRange(),ui->mv_widget->GetVertexSize());
  m_model_settings.InitializeComboBoxes(ui->cb_projection_kind,ui->mv_widget->GetProjectionKind(),
                                      ui->cb_edge_kind, ui->mv_widget->GetEdgeKind(),
                                      ui->cb_vertex_kind,ui->mv_widget->GetVertexKind());
}









}  // namespace s21::gui
