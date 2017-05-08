#include "menu.h"

Menu::Menu(){
    //ctor
}

Menu::~Menu(){
    //dtor
}

void Menu::setPosition(glm::vec3 position){
    m_transform.setPos(position);
}

glm::vec3 Menu::getPosition(){
    return m_transform.getPos();
}

void Menu::setScale(glm::vec3 scale){
    m_transform.setScale(scale);
}

glm::vec3 Menu::getScale(){
    return m_transform.getScale();
}

void Menu::setRotation(glm::vec3 rotation){
    m_transform.setRot(rotation);
}

glm::vec3 Menu::getRotation(){
    return m_transform.getRot();
}

Menu::Menu(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}


void Menu::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

void Menu::changeTexture(const string& textureFileName){
    m_texture.init(textureFileName);
}

void Menu::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    m_mesh.Draw();
}
