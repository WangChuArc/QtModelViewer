#include "stdafx.h"
#include "Render.h"
#include <sstream>
#include "Data.h"
#include <QOpenGLBuffer>

namespace Render
{
    void draw(modelHandle::SceneWrapper& scene, QOpenGLShaderProgram& prog)
    {
        draw(*scene.m_pRootNode, scene.m_pFunc, prog);
    }

    void draw(modelHandle::NodeWrapper& node, global::OpenGLVerFuncs* pFunc, QOpenGLShaderProgram& prog)
    {
        for (auto it : node.m_Meshes)
        {
            draw(*it, pFunc, prog);
        }

        for (auto it : node.m_Children)
        {
            draw(*it, pFunc, prog);
        }
    }

    void draw(modelHandle::MeshWrapper& mesh, global::OpenGLVerFuncs* pFunc, QOpenGLShaderProgram& prog)
    {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        GLuint ambientNr = 1;
        GLuint shininessNr = 1;
        GLuint heightNr = 1;
        GLuint normalsNr = 1;
        for (GLuint i = 0; i < mesh.m_textures.size(); i++)
        {
            auto& texture = mesh.m_textures[i]->m_texture;

            std::stringstream ss;
            std::string number;
            std::string name = textTypeToStr(mesh.m_textures[i]->m_type);
            if (name == "texture_diffuse")
                ss << diffuseNr++;
            else if (name == "texture_specular")
                ss << specularNr++;
            else if (name == "texture_ambient")
                ss << ambientNr++;
            else if (name == "texture_shiniess")
                ss << shininessNr++;
            else if (name == "texture_height")
                ss << heightNr++;
            else if (name == "texture_normals")
                ss << normalsNr++;
            number = ss.str();

            prog.setAttributeValue((name + number).c_str(), i);
            texture.bind(i);
        }

        // Draw mesh
        mesh.m_VAO.bind();
        pFunc->glDrawElements(GL_TRIANGLES, mesh.m_elementNum, GL_UNSIGNED_INT, 0);

        mesh.m_VAO.release();

        for (GLuint i = 0; i < mesh.m_textures.size(); i++)
        {
            auto t = &mesh.m_textures[i]->m_texture;
            t->release(i);
        }

    }

    void draw(TestCube cube, QOpenGLShaderProgram & p, global::OpenGLVerFuncs* func)
    {
        QOpenGLVertexArrayObject VAO;
        VAO.create();
        VAO.bind();

        QOpenGLBuffer VBO, EBO(QOpenGLBuffer::IndexBuffer);
        VBO.create();
        VBO.bind();
        VBO.allocate(TestCube::data, TestCube::BytesCount);
        VBO.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);

        EBO.create();
        EBO.bind();
        EBO.allocate(TestCube::index, sizeof(TestCube::index));

        func->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
        func->glEnableVertexAttribArray(0);

        func->glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        func->glDisableVertexAttribArray(0);
        VBO.release();
        VAO.release();
    }

    std::string textTypeToStr(modelHandle::textureType type)
    {
        std::string str;
        switch (type)
        {
        case modelHandle::textureType::ambient:
            str = "texture_ambient";
            break;
        case modelHandle::textureType::diffuse:
            str = "texture_diffuse";
            break;
        case modelHandle::textureType::specular:
            str = "texture_specular";
            break;
        case modelHandle::textureType::shininess:
            str = "texture_shininess";
            break;
        case modelHandle::textureType::normals:
            str = "texture_normals";
            break;
        case modelHandle::textureType::height:
            str = "texture_height";
            break;
        case modelHandle::textureType::undefined:
            break;
        default:
            break;
        }
        return str;
    }
}
