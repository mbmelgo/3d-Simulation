#include "glass.h"

Glass::Glass(){
    //dtor
}

Glass::Glass(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

Glass::~Glass(){
    //dtor
}

void Glass::setLocation(glm::vec3 position){
    m_transform.setPos(position);
}

void Glass::scale(glm::vec3 scale){
    m_transform.setScale(scale);
}

void Glass::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    m_mesh.Draw();
}

void Glass::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);

    m_transform.setPos(glm::vec3(10.0,5.0,0.0));
}
