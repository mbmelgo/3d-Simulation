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

void Bullet::setTarget(glm::vec3 position){
    m_target = position;
}

glm::vec3 Bullet::getTarget(){
    return m_target;
}

void Bullet::setPosition(glm::vec3 position){
    m_transform.setPos(position);
    m_position = position;
}

glm::vec3 Bullet::getPosition(){
    return m_position;
}

void Bullet::setVelocity(glm::vec3 velocity){
    m_velocity = velocity;
}

glm::vec3 Bullet::getVelocity(){
    return m_velocity;
}

void Bullet::setAcceleration(glm::vec3 acceleration){
    m_acceleration = acceleration;
}

glm::vec3 Bullet::getAcceleration(){
    return m_acceleration;
}

void Bullet::setAngle(float angle){
    m_angle = angle;
}

float Bullet::getAngle(){
    return m_angle;
}


void Bullet::applyForce(glm::vec3 force){
    force = force / m_mass;
    m_acceleration = m_acceleration + force;
}

void Bullet::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);

    setPosition(glm::vec3(15.0,0.0,0.0));
    setVelocity(glm::vec3(0.0,0.0,0.0));
    setAcceleration(glm::vec3(0.0,0.0,0.0));
}

void Bullet::translate(){
    m_transform.setPos(m_position);
}

void Bullet::rotate(){

}

void Bullet::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);

    m_velocity = m_velocity + m_acceleration;
    m_position = m_position + m_velocity;

    m_angle = atan(m_velocity.y/m_velocity.x);
    translate();
    rotate();
    m_mesh.Draw();
    m_acceleration = m_acceleration * 0.0f;
}
