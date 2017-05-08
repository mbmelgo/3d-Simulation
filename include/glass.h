#ifndef GLASS_H
#define GLASS_H

#include <string>
#include <glm/glm.hpp>
#include <algorithm>
#include <stdlib.h>

#include "shards.h"

using namespace std;

class Glass
{
    public:
        Glass();
        Glass(const string& shaderFileName, const string& textureFileName);
        virtual ~Glass();

        void init(const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setTarget(glm::vec3 target);
        void setVelocityIncoming(float velocity){
            if (velocity >= m_velocityLimit){
                m_canBreak = true;
            }
        }
        glm::vec3 getTarget();
        bool canBreak(){return m_breaks;}

    protected:

    private:
        string m_shader;
        string m_texture;
        Shards m_shards[48];
        glm::vec3 m_target;
        glm::vec3 m_UpperRight = glm::vec3(20.0, 10.0, -10.0);
        glm::vec3 m_UpperLeft = glm::vec3(20.0, 10.0, 10.0);
        glm::vec3 m_LowerRight = glm::vec3(20.0, 0.0, -10.0);
        glm::vec3 m_LowerLeft = glm::vec3(20.0, 0.0, 10.0);
        bool m_canBreak = false;
        bool m_breaks = false;

        float m_velocityLimit = 1.0;

        void generateShards();
        float mid(float x,float y);
        float third(float x,float y);
        void putShards(int position, Vertex a, Vertex b, Vertex c);
};

#endif // GLASS_H
