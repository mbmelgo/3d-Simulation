#include "particle.h"

Particle::Particle(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

Particle::~Particle(){
    //dtor
}

void Particle::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    m_mesh.Draw();
}

void Particle::setPosition(glm::vec3 pos){
    m_transform.setPos(pos);
}

void Particle::translate(glm::vec3 pos){
    m_transform.setPos(m_transform.getPos() + pos);
}

void Particle::setRotation(glm::vec3 pos){
    m_transform.setRot(pos);
}

void Particle::rotate(glm::vec3 pos){
    m_transform.setRot(m_transform.getRot() + pos);
}

void Particle::setScale(glm::vec3 pos){
    m_transform.setScale(pos);
}

void Particle::scale(glm::vec3 pos){
    m_transform.setScale(m_transform.getScale() + pos);
}
