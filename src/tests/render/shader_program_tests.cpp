#include <gtest/gtest.h>

#include <QOffscreenSurface>
#include <QOpenGLFunctions_3_3_Core>

#include "../../model/render/shader_program.h"


TEST(Render_Shader_Program, Basic) {
    s21::render::ShaderProgram sh_pr;
    s21::render::uniforms::CameraMatrix cm;
    s21::render::uniforms::TransformationMatrix tm;
    s21::render::uniforms::ProjectionMatrix pm;
    cm.Reset();
    tm.Reset();
    pm.Reset(10,5);

    EXPECT_EQ(sh_pr.GetProgram().isLinked(),false);
    EXPECT_THROW (sh_pr.UploadUniforms(tm,cm,pm), std::runtime_error);
    EXPECT_THROW(sh_pr.SetShaders(),std::runtime_error);

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

    EXPECT_THROW(sh_pr.SetShaders("something.vert","something_else.frag"),std::ios_base::failure);
    EXPECT_EQ(sh_pr.GetProgram().isLinked(),false);
    EXPECT_NO_THROW(sh_pr.SetShaders());
    EXPECT_EQ(sh_pr.GetProgram().isLinked(),true);

    sh_pr.UploadUniforms(tm,cm,pm);
    EXPECT_NE(sh_pr.GetProgram().uniformLocation("model"),-1);
    EXPECT_NE(sh_pr.GetProgram().uniformLocation("view"),-1);
    EXPECT_NE(sh_pr.GetProgram().uniformLocation("projection"),-1);
    context.doneCurrent();
}