#pragma once
#ifndef _MODEL_GL_WIDGET_H_
#define _MODEL_GL_WIDGET_H_

#include <QOpenGLWidget>
#include "global.h"
#include "modelHandle.h"
#include "camera.h"

class ModelGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    typedef QOpenGLWidget BaseType;

    ModelGLWidget(QWidget*);
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void loadModel();

    void keyPressEvent(QKeyEvent* pEvent);

    void mouseMoveEvent(QMouseEvent* pEvent);
    void mousePressEvent(QMouseEvent* pEvent);
    //void wheelEvent(QWheelEvent* pEvent);

    global::OpenGLVerFuncs* m_pFunc;
    QList<modelHandle::SceneWrapShared> m_scenes;
    QOpenGLShaderProgram m_prog;
    Camera m_camera;
};

#endif // !_MODEL_GL_WIDGET_H_

