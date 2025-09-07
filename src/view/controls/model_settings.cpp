#include "model_settings.h"


namespace s21::gui::controls {
    void ModelSettings::InitializeSliders(QSlider* edge_, std::pair<double,double> edge_range, double edge_value,
                            QSlider* vertex_, std::pair<double,double> vertex_range, double vertex_value) 
    {
        Slider sl_temp;
        sl_temp.Reset(edge_, edge_range, edge_value, (edge_range.second-edge_range.first)/kStepsPerSlide);
        sl_temp.Reset(vertex_, vertex_range, vertex_value, (vertex_range.second-vertex_range.first)/kStepsPerSlide);
    }
    void ModelSettings::InitializeComboBoxes(QComboBox * projection_cbox_, const int projection_cbox_value, 
                                QComboBox * edge_cbox_, const int edge_cbox_value, 
                                QComboBox *vertex_cbox_, const int vertex_cbox_value){
        projection_cbox_->clear();
        projection_cbox_->addItem(kProjectionKind_0);
        projection_cbox_->addItem(kProjectionKind_1);
        projection_cbox_->setCurrentIndex(projection_cbox_value);

        edge_cbox_->clear();
        edge_cbox_->addItem(kEdgeKind_0);
        edge_cbox_->addItem(kEdgeKind_1);
        edge_cbox_->addItem(kEdgeKind_2);
        edge_cbox_->setCurrentIndex(edge_cbox_value);

        vertex_cbox_->clear();
        vertex_cbox_->addItem(kVertexKind_0);
        vertex_cbox_->addItem(kVertexKind_1);
        vertex_cbox_->addItem(kVertexKind_2);
        vertex_cbox_->setCurrentIndex(vertex_cbox_value);
    }
        

}   //s21::gui::controls