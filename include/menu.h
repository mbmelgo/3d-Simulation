#ifndef MENU_H
#define MENU_H

#include <string>
#include <glm/glm.hpp>

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

class Menu
{
    public:
        Menu();
        Menu(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        virtual ~Menu();

        void init(const string& meshFileName, const string& shaderFileName, const string& textureFileName);
        void draw(Camera camera);

        void setPosition(glm::vec3 position);
        glm::vec3 getPosition();
        void setScale(glm::vec3 scale);
        glm::vec3 getScale();
        void setRotation(glm::vec3 rotation);
        glm::vec3 getRotation();

        void changeTexture(const string& textureFileName);

    protected:

    private:
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;
        Transform m_transform;
};

#endif // MENU_H
