#include "model_parser_worker.h"

namespace controller {
ModelParserWorker::ModelParserWorker(const QString& filename_, QObject* parent_)
    : QObject(parent_), m_filename(filename_) {}

void ModelParserWorker::Process() {
  using inbound_model::Model3D;
  try {
    std::unique_ptr<Model3D> model =
        inbound_model::ParseModelFromFile(m_filename.toStdString());
    emit finished(std::shared_ptr<Model3D>(std::move(model)));
  } catch (const std::exception& e) {
    emit error(QString::fromStdString(e.what()));
  }
}
}  // namespace controller