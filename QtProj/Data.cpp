#include"stdafx.h"
#include"Data.h"

namespace Data
{
    QList<modelHandle::SceneShared> Model::model_list;

    template<>
    global::Result Model::add_model<modelHandle::Lib::assimp>(std::string& str)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(str, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "sth wrong with assimp " << importer.GetErrorString() << std::endl;
        }
        modelHandle::ModelFactory<modelHandle::Lib::assimp> MF(scene);
        model_list.append(std::make_shared<modelHandle::Scene>(MF.produce()));

        return global::Result::eOk;
    }

    QList<modelHandle::SceneShared>* Model::getModel()
    {
        return &model_list;
    }
}