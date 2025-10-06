#ifndef SRC_CONTROLLER_MODEL_PARSER_WORKER_H
#define SRC_CONTROLLER_MODEL_PARSER_WORKER_H

#include <QObject>
#include <QString>

#include "model/parser/model_parser.h"

namespace controller {

class ModelParserWorker : public QObject {
  Q_OBJECT

 public:
  explicit ModelParserWorker(const QString& filename_,
                             QObject* parent_ = nullptr);
 signals:
  void finished(std::shared_ptr<inbound_model::Model3D> model);
  void error(const QString& message);
 public slots:
  void Process();

 private:
  QString m_filename;
};
}  // namespace controller

#endif  // SRC_CONTROLLER_MODEL_PARSER_WORKER_H