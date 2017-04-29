#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

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

        void setRotation(glm::vec3 rotation);
        glm::vec3 getRotation();

        void applyForce(glm::vec3 force);

    protected:

    private:
        glm::vec3 m_target;
        glm::vec3 m_position;
        glm::vec3 m_nextPosition;
        glm::vec3 m_rotation;
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;
        float m_mass = 4.2; //grams
        float m_lowerBoundary = -10.0;
        float m_angleX = 0.0;
        float m_angleY = 0.0;
        float m_angleZ = 0.0;


        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void translate();
        void toEuler(glm::vec3 axis,float angle);
        void rotate();
        void findAngle();
};

#endif // BULLET_H
