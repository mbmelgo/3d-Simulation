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

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setTarget(glm::vec3 position);
        glm::vec3 getTarget();

        void setPosition(glm::vec3 position);
        glm::vec3 getPosition();

        void setVelocity(glm::vec3 velocity);
        glm::vec3 getVelocity();

        void setAcceleration(glm::vec3 acceleration);
        glm::vec3 getAcceleration();

        void setAngle(float angle);
        float getAngle();

        void applyForce(glm::vec3 force);

    protected:

    private:
        glm::vec3 m_target;
        glm::vec3 m_position;
        glm::vec3 m_velocity;
        float m_angle = 0;
        glm::vec3 m_acceleration;
        float m_mass = 4.2; //grams

        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void translate();
        void rotate();
};

#endif // BULLET_H
