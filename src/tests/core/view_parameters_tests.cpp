#include <gtest/gtest.h>

#include "../../core/parameters/view_parameters.h"

TEST(Core_parameters, View_Parameters_1) {
  s21::parameters::ViewParameters prs;

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.9f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.8f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.6f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kSquare);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kSolid);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 4);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);
}

TEST(Core_parameters, View_Parameters_2) {
  s21::parameters::ViewParameters prs;

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.9f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.8f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.6f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kSquare);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kSolid);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 4);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);

  prs.SetBackgroundColor(0.5, 0.5, 0.5, 0.5);
  prs.SetModelColor(0.5, 0.5, 0.5, 0.5);
  prs.SetProjectionKind(
      s21::parameters::ViewParameters::ProjectionKind::kCentral);
  prs.SetVertexSize(5);
  prs.SetVertexKind(s21::parameters::ViewParameters::VertexKind::kNone);
  prs.SetEdgeWidth(5);
  prs.SetEdgeKind(s21::parameters::ViewParameters::EdgeKind::kNone);

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 0.5f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 0.5f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kNone);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kNone);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 5);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 5);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);
}

TEST(Core_parameters, View_Parameters_3) {
  s21::parameters::ViewParameters prs;

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 0.5f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.5f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 0.5f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kNone);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kNone);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 5);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 5);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);

  prs.SetDefaults();

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.9f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.8f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.6f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kSquare);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kSolid);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 4);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);
}

TEST(Core_parameters, View_Parameters_4) {
  s21::parameters::ViewParameters prs;

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.9f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.8f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.6f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kSquare);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kSolid);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 4);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);

  EXPECT_EQ(prs.SetBackgroundColor(0.5, 1.5, 0.5, 0.5), false);
  EXPECT_EQ(prs.SetModelColor(0.5, 0.5, 0.5, 1.5), false);
  EXPECT_EQ(prs.SetProjectionKind(2), false);
  EXPECT_EQ(prs.SetVertexSize(115), false);
  EXPECT_EQ(prs.SetVertexKind(3), false);
  EXPECT_EQ(prs.SetEdgeWidth(-5), false);
  EXPECT_EQ(prs.SetEdgeKind(-7), false);

  EXPECT_NEAR(prs.GetBackgroundColor().x, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().y, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().z, 0.1f, 1e-7);
  EXPECT_NEAR(prs.GetBackgroundColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetBackgroundColorRange().max, 1);

  EXPECT_NEAR(prs.GetModelColor().x, 0.9f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().y, 0.8f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().z, 0.6f, 1e-7);
  EXPECT_NEAR(prs.GetModelColor().w, 1.0f, 1e-7);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().min, 0);
  EXPECT_DOUBLE_EQ(prs.GetModelColorRange().max, 1);

  EXPECT_EQ(prs.GetProjectionKind(),
            s21::parameters::ViewParameters::ProjectionKind::kCentral);
  EXPECT_EQ(prs.GetProjectionKindRange().min, 0);
  EXPECT_EQ(prs.GetProjectionKindRange().max, 1);

  EXPECT_EQ(prs.GetVertexKind(),
            s21::parameters::ViewParameters::VertexKind::kSquare);
  EXPECT_EQ(prs.GetVertexKindRange().min, 0);
  EXPECT_EQ(prs.GetVertexKindRange().max, 2);

  EXPECT_EQ(prs.GetEdgeKind(),
            s21::parameters::ViewParameters::EdgeKind::kSolid);
  EXPECT_EQ(prs.GetEdgeKindRange().min, 0);
  EXPECT_EQ(prs.GetEdgeKindRange().max, 2);

  EXPECT_DOUBLE_EQ(prs.GetVertexSize(), 4);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetVertexSizeRange().max, 50);

  EXPECT_DOUBLE_EQ(prs.GetEdgeWidth(), 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().min, 1);
  EXPECT_DOUBLE_EQ(prs.GetEdgeWidthRange().max, 20);
}

TEST(Core_parameters, Settings) {
  s21::service::file::RemoveFile("settings.txt");
}
