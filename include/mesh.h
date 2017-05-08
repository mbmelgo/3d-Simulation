#ifndef MESH_H
#define MESH_H
#define GLEW_STATIC

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

#include "obj_loader.h"

using namespace std;

class Vertex{
    public:
        Vertex(const glm::vec3& pos, const glm::vec2 texCoord){
            this->pos = pos;
            this->texCoord = texCoord;
        }

        inline glm::vec3* getPos() {return &pos;};
        inline glm::vec2* getTexCoord() {return &texCoord;};

    protected:

    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
};


class Mesh
{
    public:
        Mesh();
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        Mesh(const string& fileName);
        virtual ~Mesh();

        void Draw();
        void init(const string& fileName);
        void initV(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

    protected:

    private:
        void InitMesh(const IndexedModel& model);

        enum{
            POSITION_VB,
            TEXCOORD_VB,
            INDEX_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffer[NUM_BUFFERS];
        unsigned int m_drawCount;
};

#endif // MESH_H
