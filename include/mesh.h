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
        glm::vec3 pos; // THE X Y Z COORDINATE OF THE VERTEX
        glm::vec2 texCoord; // THE TEXTURE COORDINATE
};

// MESH CREATION: THE ACT OF TAKING 3D DATA AND SENDING IT TO THE GPU
class Mesh
{
    public:
        Mesh();
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); // THE CONTRUCTOR WHICH ACCEPTS VERTICES
        Mesh(const string& fileName); // THE CONSTRUCTOR WHICH ACCEPT THE PATH OF THE OBJ FILE
        virtual ~Mesh(); // DELETE THE VERTEX ARRAY OBJECT

        void Draw(); // TAKE THE MESH AND DRAW THE MESH
        void init(const string& fileName);// THE CONTRUCTOR WHICH ACCEPTS VERTICES
        void initV(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);// THE CONSTRUCTOR WHICH ACCEPT THE PATH OF THE OBJ FILE

    protected:

    private:
        void InitMesh(const IndexedModel& model); // HELPER METHOD TO INITIALIZE THE MESH

        // REFERENCE TO THE VERTEX ARRAY BUFFERS
        enum{
            POSITION_VB, // POSITION BUFFER
            TEXCOORD_VB, // TEXTURE BUFFER
            INDEX_VB, // INDEX BUFFER: DRAWING ORDER
            NUM_BUFFERS // NUM BUFFER
        };

        GLuint m_vertexArrayObject; // REFERING TO THE MESH DATA OF THE GPU
        GLuint m_vertexArrayBuffer[NUM_BUFFERS];
        unsigned int m_drawCount; // THE NUMBER OF HOW MANY VERTICES OPENGL WILL DRAW
};

#endif // MESH_H
