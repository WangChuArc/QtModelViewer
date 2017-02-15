#pragma once
#ifndef _RENDER_H_
#define _RENDER_H_

#include"modelHandle.h"
#include<iostream>
#include "testcube.h"

namespace Render
{
    void draw(modelHandle::SceneWrapper&, QOpenGLShaderProgram&);
    void draw(modelHandle::NodeWrapper&, global::OpenGLVerFuncs*, QOpenGLShaderProgram&);
    void draw(modelHandle::MeshWrapper&, global::OpenGLVerFuncs*, QOpenGLShaderProgram&);

    void draw(TestCube, QOpenGLShaderProgram&, global::OpenGLVerFuncs*);
    std::string textTypeToStr(modelHandle::textureType type);
}

#endif // !_RENDER_H_

