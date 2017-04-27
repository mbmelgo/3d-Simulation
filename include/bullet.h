#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <glm/glm.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

using namespace std;

class Bullet
{
    public:
        Bullet();
        Bullet(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        virtual ~Bullet();


        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setVelocity(glm::vec3 velocity);
        glm::vec3 getVelocity();
        void setLocation(glm::vec3 pos);
        glm::vec3 getLocation();
        void setScale(glm::vec3 pos);
        void scale(glm::vec3 pos);
        void setAcceleration(glm::vec3 acceleration);
        glm::vec3 getAcceleration();
        void applyForce(glm::vec3 force);
        void setMass(float mass);
        float getMass();
        void checkEdges();

    protected:

    private:
        glm::vec3 m_location;
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;
        float m_mass;
        glm::vec3 m_friction;
        int bounce = 0;

        void setPosition(glm::vec3 pos);
        void setRotation(glm::vec3 pos);
        void rotate(glm::vec3 pos);
        void translate();

};

#endif // BULLET_H
