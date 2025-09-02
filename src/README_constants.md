# Constants and settings

The project contains a bunch of constants that set up the way the model is interpreted and shown or are in charge of the controls. Naturally keeping those in one (or several) big files would be rather strange and counterintuitive. But keeping track of their location would be nice in chase any of those will need to be changed or/when the project will be upgraded later it would be nine to know where those are stored.

## Basic

|Constant| Description|Location|
|---|---|---|
|s21::matrix::kStraightAngle|180.0|src/core/math/matrix4x4.h|

## Vector and Matrix related 

|Constant| Description|Location|
|---|---|---|
|s21::basis::kBasisVectorX|OX basis vector (1;0;0)|src/core/math/basis.h|
|s21::basis::kBasisVectorY|OY basis vector (0;1;0)|src/core/math/basis.h|
|s21::basis::kBasisVectorZ|OZ basis vector (0;0;1)|src/core/math/basis.h|
|s21::matrix::matrix4x4::kMatrixDimention|Keeps dimensions of the Matrix4x4|src/core/math/matrix4x4.h|

## Model view: Render and View widget

|Constant| Description|Location|
|---|---|---|
|s21::render::uniforms::ProjectionMatrix::kFovAngle|Projection's field of view|src/model/render/uniforms/uniforms.h|
|s21::render::uniforms::ProjectionMatrix::kNearPlane|Projection's near plane|src/model/render/uniforms/uniforms.h|
|s21::render::uniforms::ProjectionMatrix::kFarPlane|Projection's far plane|src/model/render/uniforms/uniforms.h|
|s21::render::uniforms::CameraMatrix::kDefaultCamera|Default camera's position|src/model/render/uniforms/uniforms.h|
|gl_PointSize|Size of vertices of the model|src/model/render/shaders/shader.vert|
|FragColor|Color of vertices and edges|src/model/render/shaders/shader.frag|
|s21::gui::ModelViewer::kBackgroundColor|Background color of the viewer widget|src/view/model_viewer/model_viewer.h|
|s21::gui::ModelViewer::kLineWidth|Width of edges of the model|src/view/model_viewer/model_viewer.h|

## Mouse controls

|Constant| Description|Location|
|---|---|---|
|s21::gui::MouseActions::kRotateSensitivityFactor|Mouse movement to rotation conversion number|src/view/model_viewer/mouse_actions.h|
|s21::gui::MouseActions::kTranslateSensitivityFactor|Mouse movement to translation conversion number|src/view/model_viewer/mouse_actions.h|
|s21::gui::MouseActions::kScaleSensitivityFactor|Mouse roller to rotation conversion number|src/view/model_viewer/mouse_actions.h|

## GUI controls

|Constant| Description|Location|
|---|---|---|
|s21::gui::controles::ModelControles::kRotateRange|Range of rotate sliders|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kDefaultRotatePosition|Default rotate sliders pin location|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kRotateStep|Rotate sliders step|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kScaleRange|Range of scale slider|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kDefaultScalePosition|Default scale slider pin location|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kScaleBase|Scale base constant (base of scaling changes are added or subtracted from it)|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kScaleStep|Scale slider step|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kScaleBigStep|Scale buttons step|src/view/model_controles/model_controles.h|
|s21::gui::controles::ModelControles::kTranslateStep|Translate buttons step|src/view/model_controles/model_controles.h|

## Main window

|Constant| Description|Location|
|---|---|---|
|MainWindow::kDefaultFile|Default model file|src/view/ui/mainwindow.h|
