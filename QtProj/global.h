#pragma once

#include<string>
#include<QOpenGLContext>
#include<QOpenGLFunctions_4_3_Core>
#include<fstream>
namespace global
{
    typedef const void* OpenGLDataArrayPtr;
    typedef OpenGLDataArrayPtr DataPtr;
    typedef char BYTE;
    typedef QOpenGLFunctions_4_3_Core OpenGLVerFuncs;

    static const float PI = 3.1415926f;
    static const std::string texturePath = "./Resources/nanosuit";
    static const std::string vertexShaderPath = "./Shaders/shader.vs";
    static const std::string fragmentShaderPath = "./Shaders/shader.frag";
    static const std::string modelPath = "./Resources/nanosuit/";
    static const std::string modelName = "nanosuit.obj";
    static const std::string logFile = "./log.log";
    enum class Result
    {
        eOk, eErr
    };
    inline unsigned int UnsignedIntGenerator() { static unsigned int i = 0; return ++i; };
    inline void log(std::string str) { std::fstream log; log.open(logFile.c_str(), std::ios::out | std::ios::app);  log << str << '\n'; log.flush(); log.close(); }
}