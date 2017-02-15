#pragma once
#ifndef _DATA_H_
#define _DATA_H_

#include<string>
#include<QList>
#include"modelHandle.h"
#include"global.h"
#include"assimpModelLoad.h"
#include<QOpenGLShaderProgram>

namespace Data
{
    typedef modelHandle::Lib::assimp defaultModelLib;

    class Model
    {

    public:
        static QList<modelHandle::SceneShared>* getModel();
        template<typename TLib = defaultModelLib> static global::Result add_model(std::string& str);

    private:
        static QList<modelHandle::SceneShared> model_list;
    };

}

#endif //_DATA_H_