#include <gtest/gtest.h>

#include <QOffscreenSurface>

#include "../../model/parser/model_parser.h"
#include "../../model/render/gui_model.h"

TEST(Render_GUI_Model, Basic) {
  render::GPU_Model model;

  EXPECT_EQ(model.GetVertexArrayObject(), 0);
  EXPECT_EQ(model.GetEdgesCount(), 0);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  EXPECT_EQ(model.GetModelName().empty(), true);

  EXPECT_THROW(model.InitializeModel(), std::runtime_error);

  // Magic to make the test work: setting up local gl context.
  // QApplication is required too - it is provided by main.cpp
  QOpenGLContext context;
  context.setFormat(QSurfaceFormat::defaultFormat());
  ASSERT_TRUE(context.create());
  QOffscreenSurface surface;
  surface.setFormat(context.format());
  surface.create();
  ASSERT_TRUE(context.makeCurrent(&surface));
  // End of spell.

  model.InitializeModel();
  EXPECT_NE(model.GetVertexArrayObject(), 0);
  EXPECT_EQ(model.GetEdgesCount(), 0);
  EXPECT_EQ(model.GetEdgesAmount(), 0);
  EXPECT_EQ(model.GetVerticesAmount(), 0);
  EXPECT_EQ(model.GetModelName().empty(), true);
  model.InitializeModel();

  std::shared_ptr<inbound_model::Model3D> p_model{std::move(
      inbound_model::ParseModelFromFile("models/cube_first.obj"))};
  model.SetModelData(p_model);
  EXPECT_NE(model.GetVertexArrayObject(), 0);
  EXPECT_EQ(model.GetEdgesCount(), 36);
  EXPECT_EQ(model.GetEdgesAmount(), 18);
  EXPECT_EQ(model.GetVerticesAmount(), 8);
  EXPECT_EQ(model.GetModelName().empty(), false);
  EXPECT_EQ(model.GetModelName(), "cube_first");
  context.doneCurrent();
}