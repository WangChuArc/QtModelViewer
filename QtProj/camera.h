#pragma once
#ifndef _CAMERA_H_
#define _CAREMA_H_

#include<QMatrix4x4>

class Camera
{
    QPoint m_lastPos;
public:
    enum dir { up, down, left, right };
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;

    Camera()
    {
        m_view.lookAt(QVector3D(0, 0, 1), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    }

    void mousePress(float x, float y)
    {
        m_lastPos.setX(x);
        m_lastPos.setY(y);
    };

    void drag(float x, float y)
    {
        float factor = 0.3f;

        float deltaX = x - m_lastPos.x();
        float deltaY = y - m_lastPos.y();
        m_lastPos.setX(x);
        m_lastPos.setY(y);

        float length = QVector2D(deltaX, deltaY).length();
        QVector3D axis(-deltaY, -deltaX, 0.0f);

        QMatrix4x4 mat; //identity matrix by default
        mat.rotate(length*factor, axis);

        m_model = mat*m_model;
    };

    void pressKey(dir direct)
    {
        float factor = 0.3f;
        QMatrix4x4 mat;
        switch (direct)
        {
        case Camera::up:
            mat(2, 3) = factor;
            break;
        case Camera::down:
            mat(2, 3) = -factor;
            break;
        case Camera::left:
            mat(0, 3) = factor;
            break;
        case Camera::right:
            mat(0, 3) = -factor;
            break;
        default:
            break;
        }
        m_model = mat*m_model;
    }
};
#endif // _CAMERA_H_
