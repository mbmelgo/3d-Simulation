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

        glm::vec3 getTarget(){return m_target;}
        bool hasTarget(){return m_hasTarget;}
        bool hasVelocity(){return m_hasVelocity;}
        float getTargetVelocity(){return m_targetVelocity;}

    protected:

    private:
        glm::vec3 m_gravity = glm::vec3(0.0,-9.8,0.0);
        glm::vec3 m_velocity;
        glm::vec3 m_force;
        glm::vec3 m_target;
        float m_mass;
        float m_lowerBoundary;
        float m_speed;
        float m_angleXY; //pitch
        float m_angleXZ; //yaw
        float m_deltaTime;
        float m_time;
        bool m_hasTarget = false;
        bool m_hasVelocity = false;
        float m_targetVelocity = 0.0;

        float m_anglePitch; //pitch
        float m_angleYaw; //yaw
        float m_angleRoll; //roll

        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void translate(glm::vec3 position);
        void rotate(glm::vec3 rot);
        float magnitude(glm::vec3 vect);
        float getAngle(glm::vec3 currentPosition, glm::vec3 nextPosition);
        void getPitchAngle(glm::vec3 nextPosition);
        void getYawAngle(glm::vec3 nextPosition);
        void getRollAngle(glm::vec3 nextPosition);
        glm::vec3 getRotations(glm::vec3 nextPosition);

};

#endif // BULLET_H
