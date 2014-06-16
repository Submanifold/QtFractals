#include "RenderWidget.hh"

#include <QDebug>
#include <QMouseEvent>

RenderWidget::RenderWidget(QWidget* parent)
  : QGLWidget(parent)
  , _scale(1.f)
{
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
  this->initializeOpenGLFunctions();
  this->qglClearColor(Qt::black);

  glEnable(GL_DEPTH_TEST);

  _shaderProgram.addShaderFromSourceCode(QGLShader::Vertex,
                                         "attribute highp vec4 vertex;\n"
                                         "attribute highp vec2 texture_in;\n"
                                         "varying   highp vec2 texture_out;\n"
                                         "void main()\n"
                                         "{\n"
                                         "  gl_Position = vertex;\n"
                                         "  texture_out = texture_in;\n"
                                         "}\n");

  bool fragmentShaderAdded
    = _shaderProgram.addShaderFromSourceFile(QGLShader::Fragment,
                                             ":/Mandelbrot.glsl");

  if(!fragmentShaderAdded)
    qDebug() << _shaderProgram.log();

  _shaderProgram.link();
  _shaderProgram.bind();

  qDebug() << _shaderProgram.log();
}

void RenderWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const GLfloat quadVertices[] =
  {
    -1.f, -1.f,
    1.f, -1.f,
    1.f, 1.f,
    -1.f, 1.f
  };

  const GLfloat textureCoordinates[] =
  {
    0.f, 0.f,
    1.f, 0.f,
    1.f, 1.f,
    0.f, 1.f
  };

  int vertexLocation  = _shaderProgram.attributeLocation("vertex");
  int textureLocation = _shaderProgram.attributeLocation("texture_in");

  _shaderProgram.enableAttributeArray(vertexLocation);
  _shaderProgram.setAttributeArray(vertexLocation, quadVertices, 2);
  _shaderProgram.enableAttributeArray(textureLocation);
  _shaderProgram.setAttributeArray(textureLocation, textureCoordinates, 2);

  glDrawArrays(GL_QUADS, 0, 4);
}

void RenderWidget::mousePressEvent(QMouseEvent* event)
{
  QPointF windowPosition   = event->windowPos();
  QPointF absolutePosition = QPointF(  3.f / this->width() * windowPosition.x() - 2.f,
                                      -2.f / this->height() * windowPosition.y() + 1.f );

  qDebug() << absolutePosition;
}
