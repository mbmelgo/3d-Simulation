#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <glm/glm.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

using namespace std;

class Particle
{
    public:
        Particle();
        Particle(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        virtual ~Particle();


        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);
        void setPosition(glm::vec3 pos);
        void translate(glm::vec3 pos);
        void setRotation(glm::vec3 pos);
        void rotate(glm::vec3 pos);
        void setScale(glm::vec3 pos);
        void scale(glm::vec3 pos);

    protected:

    private:
};

#endif // PARTICLE_H
