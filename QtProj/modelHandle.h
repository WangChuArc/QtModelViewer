#pragma once
#ifndef _MODEL_HANDLE_

#define _MODEL_HANDLE_

#include<vector>
#include<map>
#include"global.h"
#include<algorithm>
#include<memory>
#include<iostream>
#include<list>
#include<math.h>
#include<limits>
#include<QByteArray>
#include<QImage>
#include<QOpenGLWidget>
#include<QOpenGLVertexArrayObject>
#include<QOpenGLFunctions>
#include<QOpenGLBuffer>
#include<QOpenGLTexture>
#include "testcube.h"

namespace modelHandle
{
    using namespace std;

    /* 加载模型的库注册 */
    namespace Lib
    {
        struct LibListHead {};
#define LIB_LIST_HEAD LibListHead
#define LIB_LIST_TAIL LibListHead

        template<typename T>
        struct Liblist {};

        template<>
        struct Liblist<LIB_LIST_HEAD> { typedef void preType; };

#define ADD_TO_LIB_LIST(x) struct x {}; template<>struct Liblist<x> { typedef LIB_LIST_TAIL preType; };
    }

    /* 保存模型数据的类和一些定义 */

    template<typename T, size_t Length>
    struct vec
    {
        typedef T type;
        T data[Length];
        T& operator[] (int i) { return data[i]; }
    };


    typedef vec<GLfloat, 4> vec4;
    typedef vec<GLfloat, 3> vec3;
    typedef vec<GLfloat, 2> vec2;
    
    struct Texture;  struct Scene; struct Node; struct Mesh;
    typedef shared_ptr<Texture>  TextureShared;
    typedef shared_ptr<Scene>    SceneShared;
    typedef shared_ptr<Node>     NodeShared;
    typedef shared_ptr<Mesh>     MeshShared;

    extern vector<SceneShared> sceneVec;

    struct Vertex
    {
        union
        {
            struct
            {
                vec3 position;
                vec3 normal;
                vec2 textCoord;
            };
            global::BYTE data[sizeof(vec3) + sizeof(vec3) + sizeof(vec2)];
        };
    };


    enum class textureType { ambient, diffuse, specular, shininess, normals, height, undefined };

    struct Texture
    {
        Texture(textureType t, string&& s_n, const string& s_p) : type(t), name(s_n), path(s_p) {};
        textureType type;
        string name;
        // 用于存储材质文件目录的地址
        string path;
    };

    struct Mesh
    {
        typedef int indexType;

        const GLuint m_ID;
        vector<Vertex> m_vertexVec;
        vector<indexType> m_indexVec;
        vector<TextureShared> m_textureVec;

        Mesh() : m_ID(generate_ID()) { };

        Mesh(Mesh&&) = default;

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
    private:
        static unsigned int generate_ID() { return global::UnsignedIntGenerator(); };
    };

    struct Node
    {
        const GLuint m_ID;
        Node* m_pParent;
        vector<NodeShared> m_ChildrenPtrVec;
        vector<MeshShared> m_MeshesPtrVec;

        Node() : m_ID(generate_ID()), m_pParent(nullptr) { };

        Node(Node&&) = default;

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

    private:
        static unsigned int generate_ID() { return global::UnsignedIntGenerator(); };
    };

    struct Scene
    {
        NodeShared m_rootNode;
        vector<TextureShared> m_TexturePtrs;

        Scene() = default;
        Scene(Scene&&) = default;

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
    };


    template<typename T>
    class TraitHelper {};

    template<typename T>
    class ModelFactory {};

    class SceneWrapper;     typedef shared_ptr<SceneWrapper> SceneWrapShared;
    class NodeWrapper;      typedef shared_ptr<NodeWrapper> NodeWrapShared;
    class MeshWrapper;      typedef shared_ptr<MeshWrapper> MeshWrapShared;
    class TextureWrapper;   typedef shared_ptr<TextureWrapper> TextWrapShared;

    class SceneWrapper
    {
    public:
        SceneWrapper(Scene& scene, global::OpenGLVerFuncs* pFunc);
        void uploadTexture(Scene& scene);

        NodeWrapShared m_pRootNode;
        vector<TextWrapShared> m_textures;
        global::OpenGLVerFuncs* m_pFunc;
    };

    class NodeWrapper
    {
    public:
        NodeWrapper(Node&, SceneWrapper&);

        vector<NodeWrapShared> m_Children;
        vector<MeshWrapShared> m_Meshes;
    };

    class MeshWrapper
    {
    public:
        MeshWrapper(Mesh&, SceneWrapper&);
        ~MeshWrapper() {  };

        QOpenGLVertexArrayObject m_VAO;
        int m_vertexNum;
        int m_elementNum;
        vector<TextWrapShared> m_textures;
        vector<GLuint> m_buffers;
    };

    class TextureWrapper
    {
    public:
        TextureWrapper(Texture&);
        void TextureFromFile(string& name);

        textureType m_type;
        QOpenGLTexture m_texture;
        string m_name;
    };

    inline SceneWrapShared createTestScene(global::OpenGLVerFuncs* pFunc)
    {
        Scene scene;
        scene.m_rootNode = std::make_shared<modelHandle::Node>();
        auto m = std::make_shared<modelHandle::Mesh>();
        for (int i = 0; i < sizeof(TestCube::data)/sizeof(TestCube::data[0]); i += 3)
        {
            Vertex v;
            v.position[0] = TestCube::data[i];
            v.position[1] = TestCube::data[i+1];
            v.position[2] = TestCube::data[i+2];
            m->m_vertexVec.push_back(v);
        }
        for (auto i : TestCube::index)
        {
            m->m_indexVec.push_back(i);
        }
        scene.m_rootNode->m_MeshesPtrVec.push_back(m);
        return std::make_shared<SceneWrapper>(scene, pFunc);
    }
}


#endif // !_MODEL_HANDLE_