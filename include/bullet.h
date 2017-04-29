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

        void applyForce(glm::vec3 force);

        void setMass(float mass);
        void setLowerBoundary(float lowerBoundary);
        void setSpeed(float speed);
        void setAngleXY(float angleXY);
        void setAngleXZ(float setAngleXZ);

        void initBullet();

        float getMass();
        float getLowerBoundary();
        float getSpeed();
        float getAngleXY();
        float getAngleXZ();


    protected:

    private:
        glm::vec3 m_velocity;
        glm::vec3 m_force;
        float m_mass; //grams
        float m_lowerBoundary;
        float m_speed;
        float m_angleXY;
        float m_angleXZ;
        float m_deltaTime;
        float m_time;

        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void translate(glm::vec3 position);
};

#endif // BULLET_H
