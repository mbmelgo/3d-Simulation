#include "bullet.h"

Bullet::Bullet(){
    //dtor
}

Bullet::Bullet(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

Bullet::~Bullet(){
    //dtor
}

void Bullet::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

void Bullet::translate(){
    m_transform.setPos(m_transform.getPos() + m_velocity);
    m_location = m_transform.getPos();
}

void Bullet::applyForce(glm::vec3 force){
    float x = force.x / m_mass;
    float y = force.y / m_mass;
    float z = force.z / m_mass;
    glm::vec3 f(x,y,z);
    m_acceleration = m_acceleration + f;
}

void Bullet::checkEdges(){

}

void Bullet::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    m_velocity = m_velocity + m_acceleration;
    translate();
    checkEdges();
    m_mesh.Draw();
}

void Bullet::setPosition(glm::vec3 pos){
    m_transform.setPos(pos);
}

void Bullet::setRotation(glm::vec3 pos){
    m_transform.setRot(pos);
}

void Bullet::rotate(glm::vec3 pos){
    m_transform.setRot(m_transform.getRot() + pos);
}

void Bullet::setScale(glm::vec3 pos){
    m_transform.setScale(pos);
}

void Bullet::scale(glm::vec3 pos){
    m_transform.setScale(m_transform.getScale() + pos);
}

void Bullet::setVelocity(glm::vec3 velocity){
    m_velocity = velocity;
}

glm::vec3 Bullet::getVelocity(){
    return m_velocity;
}

void Bullet::setLocation(glm::vec3 pos){
    m_location = pos;
    setPosition(pos);
}

glm::vec3 Bullet::getLocation(){
    return m_location;
}

void Bullet::setAcceleration(glm::vec3 acceleration){
    m_acceleration = acceleration;
}

glm::vec3 Bullet::getAcceleration(){
    return m_acceleration;
}

void Bullet::setMass(float mass){
    m_mass = mass;
}

float Bullet::getMass(){
    return m_mass;
}

