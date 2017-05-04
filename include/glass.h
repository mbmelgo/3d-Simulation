#ifndef GLASS_H
#define GLASS_H

#include <string>
#include <glm/glm.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

using namespace std;

class Glass
{
    public:
        Glass();
        Glass(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        virtual ~Glass();

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setLocation(glm::vec3 position);
        void scale(glm::vec3 position);

    protected:

    private:
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        float m_velocityLimit = 1.0;
};

#endif // GLASS_H
