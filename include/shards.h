#ifndef SHARDS_H
#define SHARDS_H

#include <string>
#include <glm/glm.hpp>

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

class Shards
{
    public:
        Shards();
        Shards(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass);
        virtual ~Shards();

        void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass);
        void draw(Camera camera);

        void applyForce(glm::vec3 force);
        void setStop(bool isStopped){m_stop = isStopped;}

    protected:

    private:
        glm::vec3 m_gravity = glm::vec3(0.0,-9.8,0.0);
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;
        glm::vec3 m_position;
        float m_positionY;

        glm::vec3 m_velocity;
        glm::vec3 m_force;
        float m_mass;
        float m_deltaTime;
        float m_time;
        bool m_stop = false;

        void translate(glm::vec3 position);
        float mid(float x, float y, float z);

};

#endif // SHARDS_H
