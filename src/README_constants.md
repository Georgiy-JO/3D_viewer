# Constants and settings

The project contains a bunch of constants that set up the way the model is interpreted and shown or are in charge of the controls. Naturally keeping those in one (or several) big files would be rather strange and counterintuitive. But keeping track of their location would be nice in chase any of those will need to be changed or/when the project will be upgraded later it would be nine to know where those are stored.

## Basic

|Constant| Description|Location|
|---|---|---|
|matrix::kStraightAngle|180.0|src/core/math/matrix4x4.h|

## Vector and Matrix related 

|Constant| Description|Location|
|---|---|---|
|basis::kBasisVectorX|OX basis vector (1;0;0)|src/core/math/basis.h|
|basis::kBasisVectorY|OY basis vector (0;1;0)|src/core/math/basis.h|
|basis::kBasisVectorZ|OZ basis vector (0;0;1)|src/core/math/basis.h|
|matrix::matrix4x4::kMatrixDimention|Keeps dimensions of the Matrix4x4|src/core/math/matrix4x4.h|
|matrix::matrix4x4::kMinialScale|Minimal single-time scale for Matrix4x4|src/core/math/matrix4x4.h|

## Inbound model constants

|Constant| Description|Location|
|---|---|---|
|inbound_model::Model3D::kDefaultScaleFactor|Default scaling factor of a model|src/model/model3d/model3d.h|

## Model view parameters

|Constant| Description|Location|
|---|---|---|
|parameters::ViewParameters::kSettingsFile|Model view parameters' save file|src/core/parameters/view_parameters.h|
|parameters::ViewParameters::kSettingsFileHead|Model view parameters file' header|src/core/parameters/view_parameters.h|
|parameters::ViewParameters::kMaxSettingsFileSize|Max model view parameters save file' size in bytes|src/core/parameters/view_parameters.h|
|parameters::ViewParameters::kBackgroundColorTag <br> parameters::ViewParameters::kModelColorTag <br> parameters::ViewParameters::kProjectionTag <br> parameters::ViewParameters::kVertexSizeTag <br> parameters::ViewParameters::kVertexKindTag <br> parameters::ViewParameters::kEdgeWidthTag <br> parameters::ViewParameters::kEdgeKindTag |Tags of the model view's parameters for saving to/reading from file. |src/core/parameters/view_parameters.h|
|parameters::ViewParameters::[...]::kDefault <br> parameters::ViewParameters::[...]::kRange <br> parameters::ViewParameters::[...]::kTag|Default value (in case no model view parameters' save file present), range of values and tag of the following variables:  <br> * m_background_color - color of background <br> * m_model_color - color of model <br> * m_projection_kind - kind of projection (Orthographic/Central) <br> * m_vertex_size - size of vertices <br> * m_vertex_kind - vertices' kind (None/Square/Circle) <br> * m_edge_width - width of edges/lines <br> * m_edge_kind - kind of edges (None/Solid/Dotted)|src/core/parameters/view_parameters.h|

## Model view rendering and View widget

### Shader files

|Constant| Description|Location|
|---|---|---|
|render::ShaderProgram::kDefaultGlobalVertexShaderPath|Default vertex shader for vertices and edges file location|src/model/render/shader_program.h|
|render::ShaderProgram::kDefaultVertexVertexShaderPath|Default vertex shader for vertices file location (NOT USED)|src/model/render/shader_program.h|
|render::ShaderProgram::kDefaultEdgeVertexShaderPath|Default vertex shader for edges file location (NOT USED)|src/model/render/shader_program.h|
|render::ShaderProgram::kDefaultEdgeGeometryShaderPath|Default geometry shader for edges file location|src/model/render/shader_program.h|
|render::ShaderProgram::kDefaultEdgeFragmentShaderPath|Default fragment shader for vertices file location|src/model/render/shader_program.h|
|render::ShaderProgram::kDefaultVertexFragmentShaderPath|Default fragment shader for edges file location|src/model/render/shader_program.h|

### Uniforms' naming (for passing to shader files)

|Constant| Description|Location|
|---|---|---|
|render::ShaderProgram::kTransformationUniform|Transformation matrix uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kCameraUniform|Camera matrix uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kProjectionUniform|Projection matrix uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kCombinedAffectUniform|Combination of Projection, camera and transformation matrices matrix uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kVertexSizeUniform|Vertices size uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kEdgeWidthUniform|Edges width uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kModelColorUniform|Model color uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kCombinedAffectSwitchUniform|Use kCombinedAffectUniform switch uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kDottedEdgeUniform|Dotted edges switch uniform's name |src/model/render/shader_program.h|
|render::ShaderProgram::kCircleVertexUniform|Circle vertices switch uniform's name |src/model/render/shader_program.h|

### Matrix uniforms' constants

|render::uniforms::ProjectionMatrix::kFovAngle|Projection's field of view for **central** projection|src/model/render/uniforms/uniforms.h|
|render::uniforms::ProjectionMatrix::kNearPlane|Projection's near plane|src/model/render/uniforms/uniforms.h|
|render::uniforms::ProjectionMatrix::kFarPlane|Projection's far plane|src/model/render/uniforms/uniforms.h|
|render::uniforms::ProjectionMatrix::kProjectionCubeSize|Size of height of projection cube for **orthographic** projection |src/model/render/uniforms/uniforms.h|
|render::uniforms::CameraMatrix::kDefaultCamera|Default camera's position|src/model/render/uniforms/uniforms.h|


## Mouse controls

|Constant| Description|Location|
|---|---|---|
|gui::MouseActions::kRotateSensitivityFactor|Mouse movement to rotation conversion number|src/view/model_viewer/mouse_actions.h|
|gui::MouseActions::kTranslateSensitivityFactor|Mouse movement to translation conversion number|src/view/model_viewer/mouse_actions.h|
|gui::MouseActions::kScaleSensitivityFactor|Mouse roller to rotation conversion number|src/view/model_viewer/mouse_actions.h|

## GUI controls

### GUI model controls

|Constant| Description|Location|
|---|---|---|
|gui::controls::ModelControls::kRotateRange|Range of rotate sliders|src/view/controls/model_controls.h|
|gui::controls::ModelControls::kDefaultRotatePosition|Default rotate sliders pin location|src/view/controls/model_controls.h|
|gui::controls::ModelControls::kRotateStep|Rotate sliders step|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kScaleRange|Range of scale slider|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kDefaultScalePosition|Default scale slider pin location|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kScaleBase|Scale base constant (base of scaling changes are added or subtracted from it)|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kScaleStep|Scale slider step|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kScaleBigStep|Scale buttons step|src/view/controlsmodel_controls.h|
|gui::controls::ModelControls::kTranslateStep|Translate buttons step|src/view/controlsmodel_controls.h|

### GUI model parameters settings

|Constant| Description|Location|
|---|---|---|
|gui::controls::ModelSettings::kProjectionKind_0|Name of first element of projection kind combo box (Orthographic Projection)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kProjectionKind_1|Name of second element of projection kind combo box (Central Projection)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kEdgeKind_0|Name of first element of edges kind combo box (No Edges)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kEdgeKind_1|Name of second element of edges kind combo box (Solid Edges)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kEdgeKind_2|Name of third element of edges kind combo box (Dotted Edges)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kVertexKind_0|Name of first element of vertices kind combo box (No Vertices)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kVertexKind_1|Name of second element of vertices kind combo box (Square Vertices)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kVertexKind_2|Name of third element of vertices kind combo box (Circle Vertices)|src/view/controls/model_settings.h|
|gui::controls::ModelSettings::kStepsPerSlide|Step of sliders (edges width and vertices size)|src/view/controls/model_settings.h|

## Main window

|Constant| Description|Location|
|---|---|---|
|MainWindow::kDefaultFile|Default model file|src/view/ui/mainwindow.h|
