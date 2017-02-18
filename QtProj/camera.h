#pragma once
#ifndef _CAMERA_H_
#define _CAREMA_H_

#include<QMatrix4x4>

class Camera
{
    QPoint m_lastPos;
public:
    enum dir { up, down, left, right, forward, backward };
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    Camera()
    {
        resetCarema();
    }

    void resetCarema() { m_view.lookAt(QVector3D(0, 0, 1), QVector3D(0, 0, 0), QVector3D(0, 1, 0)); };
    void resetModel() { m_model.setToIdentity(); };

    void mousePress(float x, float y)
    {
        m_lastPos.setX(x);
        m_lastPos.setY(y);
    };

    void mouseMove(float x, float y)
    {
        float factor = 0.2f;

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

    void mouseScroll(float y)
    {
        // 虽然浮点数不应该这么比较，但我只是判断y值正负，就这么写了
        float factor = 1.0f;
        if(y > 0.0f)
            factor = 1.1f;
        else
            factor = 0.9f;
        m_view.scale(factor);
    }

    void pressKey(dir direct)
    {
        float factor = 0.3f;
        QMatrix4x4 mat;
        switch (direct)
        {
        case Camera::up:
            mat(1, 3) = -factor;
            break;
        case Camera::down:
            mat(1, 3) = factor;
            break;
        case Camera::forward:
            mat(2, 3) = factor;
            break;
        case Camera::backward:
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

    void resizeTranslate(int x, int y, int oldX, int oldY)
    {
        if (x == 0) return;
        if (x - oldX > 100) return;
        QMatrix4x4 mat;
        mat.scale((float)oldX/(float)x, (float)oldY / (float)y, 1.0f);
        mat(0, 3) = (float)(oldX - x) / (float)x;
        mat(1, 3) = (float)(y - oldY) / (float)y;
        m_model = mat*m_model;
    }


};
#endif // _CAMERA_H_
