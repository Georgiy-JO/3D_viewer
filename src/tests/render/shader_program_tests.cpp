#include <gtest/gtest.h>

#include <QOffscreenSurface>
#include <QOpenGLFunctions_3_3_Core>

#include "../../view/render/shader_program.h"

TEST(Render_Shader_Program, Basic) {
  render::ShaderProgram sh_pr;
  render::uniforms::CameraMatrix cm;
  render::uniforms::TransformationMatrix tm;
  render::uniforms::ProjectionMatrix pm;
  cm.Reset();
  tm.Reset();
  pm.ResetCentral(10, 5);

  EXPECT_EQ(sh_pr.GetProgram().isLinked(), false);
  EXPECT_THROW(sh_pr.UploadUniforms(
                   tm, cm, pm, vectors::Vec4(0.5, 0.5, 0.5, 0.5), 0.5, 1, 1, 1),
               std::runtime_error);
  EXPECT_THROW(sh_pr.SetVertexShaders(), std::runtime_error);
  EXPECT_THROW(sh_pr.SetEdgeShaders(), std::runtime_error);

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

  EXPECT_THROW(sh_pr.SetShaders("something.vert", "something_else.frag"),
               std::ios_base::failure);
  EXPECT_EQ(sh_pr.GetProgram().isLinked(), false);
  EXPECT_THROW(sh_pr.SetShaders("shaders/shader.vert", "something_else.frag"),
               std::ios_base::failure);
  EXPECT_EQ(sh_pr.GetProgram().isLinked(), false);
  EXPECT_THROW(
      sh_pr.SetShaders("shaders/shader.vert", "shaders/edge_shader.frag",
                       "something_else.frag"),
      std::ios_base::failure);
  EXPECT_EQ(sh_pr.GetProgram().isLinked(), false);
  EXPECT_NO_THROW(sh_pr.SetVertexShaders());
  EXPECT_NO_THROW(sh_pr.SetEdgeShaders());
  EXPECT_EQ(sh_pr.GetProgram().isLinked(), true);

  sh_pr.UploadUniforms(tm, cm, pm, vectors::Vec4(0.5, 0.5, 0.5, 0.5), 1, 1, 1,
                       1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mTransformation"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mCamera"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mProjection"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("dVertexSize"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("vModelColor"), -1);
  // EXPECT_NE(sh_pr.GetProgram().uniformLocation("dEdgeWidth"),-1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("sDottedEdge"), -1);

  EXPECT_NO_THROW(sh_pr.SetVertexShaders());
  sh_pr.UploadUniforms(tm, cm, pm, vectors::Vec4(0.5, 0.5, 0.5, 0.5), 1, 1, 1,
                       1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mTransformation"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mCamera"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mProjection"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("dVertexSize"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("vModelColor"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("sCircleVertex"), -1);

  EXPECT_NO_THROW(sh_pr.SetVertexShaders());
  sh_pr.UploadUniforms((tm.GetMatrix() * cm.GetMatrix() * pm.GetMatrix()),
                       vectors::Vec4(0.5, 0.5, 0.5, 0.5), 1, 1, 1, 1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("mCombinedAffect"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("dVertexSize"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("vModelColor"), -1);
  EXPECT_NE(sh_pr.GetProgram().uniformLocation("sCircleVertex"), -1);

  context.doneCurrent();
}