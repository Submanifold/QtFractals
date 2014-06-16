#ifndef RenderWidget_hh__
#define RenderWidget_hh__

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QOpenGLFunctions>

class RenderWidget : public QGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

  public:
    RenderWidget(QWidget* widget = nullptr);
    ~RenderWidget();

  private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

    QGLShaderProgram _shaderProgram;

    int _iterations;

    QPointF _centre;
    float _scale;
};

#endif
