#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <glm/glm.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

class Plane
{
    public:
        Plane();
        Plane(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        virtual ~Plane();

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setPosition(glm::vec3 position);
        glm::vec3 getPosition();
        void setScale(glm::vec3 scale);
        glm::vec3 getScale();

    protected:

    private:
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;

        void drawCoordinates();
};

#endif // FLOOR_H
