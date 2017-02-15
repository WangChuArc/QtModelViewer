#include"stdafx.h"
#include"modelHandle.h"
#include<algorithm>
#include<memory>
#include<iostream>
#include<list>
#include<math.h>
#include<limits>

// debug
#include<assert.h>

namespace modelHandle
{

    SceneWrapper::SceneWrapper(Scene & scene, global::OpenGLVerFuncs* pFunc) : m_pFunc(pFunc)
    {
        uploadTexture(scene);
        m_pRootNode = make_shared<NodeWrapper>(*(scene.m_rootNode), *this);
    }

    void SceneWrapper::uploadTexture(Scene & scene)
    {
        for (auto& it : scene.m_TexturePtrs)
            m_textures.push_back(make_shared<TextureWrapper>(*it));
    }
    
    void TextureWrapper::TextureFromFile(string& name)
    {
        m_texture.setData(QImage(name.c_str()));
        m_texture.setWrapMode(QOpenGLTexture::Repeat);
        m_texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture.setMagnificationFilter(QOpenGLTexture::Linear);
    }

    NodeWrapper::NodeWrapper(Node & node, SceneWrapper& scene)
    {
        for(auto it : node.m_MeshesPtrVec)
        {
            m_Meshes.push_back(make_shared<MeshWrapper>(*it, scene));
        }

        for (auto& it : node.m_ChildrenPtrVec)
        {
            m_Children.push_back(make_shared<NodeWrapper>(*it, scene));
        }
    }

    MeshWrapper::MeshWrapper(Mesh & mesh, SceneWrapper& scene)
    {
        const size_t position_size = sizeof(Vertex::position);
        const size_t normal_size = sizeof(Vertex::normal);
        const size_t textCoord_size = sizeof(Vertex::textCoord);
        const size_t stride = sizeof(Vertex);
        const size_t vertexNum = mesh.m_vertexVec.size();   m_vertexNum = vertexNum;
        const size_t data_length = stride * vertexNum;
        const size_t indexNum = mesh.m_indexVec.size();     m_elementNum = indexNum;
        const size_t index_length =sizeof(Mesh::indexType) * indexNum;

        global::OpenGLVerFuncs& func = *scene.m_pFunc;
        global::DataPtr data = reinterpret_cast<global::DataPtr>(mesh.m_vertexVec.data()->data);
        global::DataPtr elemData = reinterpret_cast<global::DataPtr>(mesh.m_indexVec.data());
        size_t offset = 0;

        GLuint VAO, textureID;

        /* VAO */
        m_VAO.create();
        m_VAO.bind();

        /* VBO */
        QOpenGLBuffer VBO;
        VBO.create();
        VBO.bind();
        VBO.allocate(data, data_length);
        VBO.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        m_buffers.push_back(VBO.bufferId());

        /* EBO */
        QOpenGLBuffer EBO(QOpenGLBuffer::IndexBuffer);
        EBO.create();
        EBO.bind();
        EBO.allocate(elemData, index_length);
        EBO.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        m_buffers.push_back(EBO.bufferId());

        /* 开启几个顶点属性 */
        func.glVertexAttribPointer(0, position_size / sizeof(decltype(Vertex::position)::type), GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        func.glEnableVertexAttribArray(0);
        offset += position_size;

        func.glVertexAttribPointer(1, normal_size / sizeof(decltype(Vertex::normal)::type), GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        func.glEnableVertexAttribArray(1);
        offset += normal_size;

        func.glVertexAttribPointer(2, textCoord_size / sizeof(decltype(Vertex::textCoord)::type), GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        func.glEnableVertexAttribArray(2);

        /* texture */
        for (auto& it : mesh.m_textureVec) /* 内存中的mesh中的texture */
        {
            for (auto& it2 : scene.m_textures) /* 显存中的scene中的texture */
            {
                if (it->name == it2->m_name)
                {
                    m_textures.push_back(TextWrapShared(it2));
                    break;
                }
            }
        }

        m_VAO.release();
        VBO.release();
        EBO.release();
    }

    TextureWrapper::TextureWrapper(Texture & text) : m_texture(QOpenGLTexture::Target2D)
    {
        m_type = text.type;
        m_name = text.name;
        TextureFromFile(text.path + text.name);
    }

}