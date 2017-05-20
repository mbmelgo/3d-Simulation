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
        Shards(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass, glm::vec3 velocity, bool breaksOnly);
        virtual ~Shards();

        void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass, glm::vec3 velocity, bool breaksOnly);
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
        bool m_canCrack = false;
        bool m_breaksOnly = false;

        float m_anglePitch; //pitch
        float m_angleYaw; //yaw
        float m_angleRoll; //roll

        void translate(glm::vec3 position);
        float mid(float x, float y, float z);

        void rotate(glm::vec3 rot);
        float magnitude(glm::vec3 vect);
        float getAngle(glm::vec3 currentPosition, glm::vec3 nextPosition);
        void getPitchAngle(glm::vec3 nextPosition);
        void getYawAngle(glm::vec3 nextPosition);
        void getRollAngle(glm::vec3 nextPosition);
        glm::vec3 getRotations(glm::vec3 nextPosition);

};

#endif // SHARDS_H
