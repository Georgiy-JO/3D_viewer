#include "model_parser_worker.h"


namespace s21::controller{
    ModelParserWorker::ModelParserWorker(const QString& filename_, QObject* parent_): QObject(parent_), m_filename(filename_){}

    void ModelParserWorker::Process(){
        using s21::inbound_model::Model3D;
        try
        {
            std::unique_ptr<Model3D> model= s21::inbound_model::ParseModelFromFile(m_filename.toStdString());
            emit finished(std::shared_ptr<Model3D>(std::move(model)));
        }
        catch(const std::exception& e)
        {
            emit error(QString::fromStdString(e.what()));
        } 
    }
} // namespace s21::controller