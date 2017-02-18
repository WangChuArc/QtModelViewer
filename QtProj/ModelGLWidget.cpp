#include "stdafx.h"
#include "ModelGLWidget.h"
#include "Render.h"
#include "data.h"


ModelGLWidget::ModelGLWidget(QWidget *p) : BaseType(p)
{
    setFocusPolicy(Qt::ClickFocus);
}

void ModelGLWidget::initializeGL()
{
    // funcs
    m_pFunc = QOpenGLContext::currentContext()->versionFunctions<global::OpenGLVerFuncs>();
    m_pFunc->glEnable(GL_DEPTH_TEST);

    // shaders
    m_prog.addShaderFromSourceFile(QFlags<QOpenGLShader::ShaderTypeBit>(QOpenGLShader::Vertex), global::vertexShaderPath.c_str());
    m_prog.addShaderFromSourceFile(QFlags<QOpenGLShader::ShaderTypeBit>(QOpenGLShader::Fragment), global::fragmentShaderPath.c_str());

    m_camera.m_projection.perspective(50, (float)width() / (float)height(), 0.1f, 100.0f);
}

void ModelGLWidget::resizeGL(int x, int y)
{
    m_camera.resizeTranslate(x, y, m_lastTimeSize.width(), m_lastTimeSize.height());

    m_lastTimeSize.setWidth(x);
    m_lastTimeSize.setHeight(y);
}

void ModelGLWidget::paintGL()
{

    m_pFunc->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_pFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_prog.bind();

    //QMatrix4x4 projection;
    
    QMatrix4x4 model = m_camera.m_model;
    model.scale(0.2);
    m_prog.setUniformValue("projection", m_camera.m_projection);
    m_prog.setUniformValue("view", model);

    m_prog.setUniformValue("model", m_camera.m_view);

    for (auto s : m_scenes)
    {
        Render::draw(*s, m_prog);
    }
    Render::draw(TestCube(), m_prog, m_pFunc);

    m_prog.release();
}

void ModelGLWidget::loadModel()
{
    QList<modelHandle::SceneShared>* lst = Data::Model::getModel();
    auto m = lst->takeFirst();

    makeCurrent();
    modelHandle::SceneWrapShared sw = std::make_shared<modelHandle::SceneWrapper>(*m, m_pFunc);
    doneCurrent();

    m_scenes.append(sw);
    update();
    setFocus();
}

void ModelGLWidget::keyPressEvent(QKeyEvent * pEvent)
{
    Camera::dir direct;
    switch (pEvent->key())
    {
    case Qt::Key_Q:
        m_camera.pressKey(Camera::up);
        break;
    case Qt::Key_E:
        m_camera.pressKey(Camera::down);
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        m_camera.pressKey(Camera::forward);
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        m_camera.pressKey(Camera::backward);
        break;

    case Qt::Key_A:
    case Qt::Key_Left:
        m_camera.pressKey(Camera::left);
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        m_camera.pressKey(Camera::right);
        break;
    default:
        break;
    }

    BaseType::keyPressEvent(pEvent);
    update();
}

void ModelGLWidget::mouseMoveEvent(QMouseEvent * pEvent)
{
    m_camera.mouseMove(pEvent->pos().x(), pEvent->pos().y());
    update();
}

void ModelGLWidget::mousePressEvent(QMouseEvent * pEvent)
{
    m_camera.mousePress(pEvent->x(), pEvent->y());
}

void ModelGLWidget::wheelEvent(QWheelEvent * pEvent)
{
    if (pEvent->buttons() & Qt::LeftButton)
    {
        auto degree = pEvent->angleDelta();
        m_camera.mouseScroll(degree.y());
    }

    BaseType::wheelEvent(pEvent);
    update();
    return;
}

