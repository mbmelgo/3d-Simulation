#include "plane.h"

Plane::Plane(){
    //ctor
}

Plane::~Plane(){
    //dtor
}

void Plane::setPosition(glm::vec3 position){
    m_transform.setPos(position);
    m_position = position;
}

glm::vec3 Plane::getPosition(){
    return m_position;
}

Plane::Plane(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}


void Plane::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

void Plane::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    m_mesh.Draw();
}
