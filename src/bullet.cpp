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

void Bullet::setMass(float mass){
    m_mass = mass;
}

void Bullet::setSpeed(float speed){
    m_speed = speed;
}

void Bullet::setLowerBoundary(float lowerBoundary){
    m_lowerBoundary = lowerBoundary;
}

void Bullet::setAngleXY(float angleXY){
    m_angleXY = angleXY * 3.141459/180.00;
}

void Bullet::setAngleXZ(float angleXZ){
    m_angleXZ = angleXZ * 3.141459/180.00;
}

float Bullet::getMass(){
    return m_mass;
}

float Bullet::getSpeed(){
    return m_speed;
}

float Bullet::getLowerBoundary(){
    return m_lowerBoundary;
}

float Bullet::getAngleXY(){
    return m_angleXY;
}

float Bullet::getAngleXZ(){
    return m_angleXZ;
}

void Bullet::initBullet(){
    m_velocity = glm::vec3(
                           m_speed * cos(m_angleXY) * cos(m_angleXZ),
                           m_speed * sin(m_angleXY),
                           m_speed * cos(m_angleXY) * sin(m_angleXZ)
                           );
}


void Bullet::applyForce(glm::vec3 force){
    force =  force / m_mass;
    m_force = m_force + force;
}

void Bullet::translate(glm::vec3 position){
    m_transform.setPos(position);
}

void Bullet::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);

    m_velocity = m_velocity + m_force/m_mass * m_deltaTime;
    glm::vec3 nextPosition = m_transform.getPos() + m_velocity * m_deltaTime;
    if(nextPosition.y <= m_lowerBoundary){
        m_velocity.y = 0.0f;
        nextPosition.y = m_lowerBoundary;
    }

    translate(nextPosition);
    m_mesh.Draw();
    m_force = glm::vec3(0.0,0.0,0.0);
    if (m_transform.getPos().y < -10.0){
        m_transform.getPos().y = -10.0;
    }
    m_time = m_time + m_deltaTime;
}

void Bullet::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
    m_transform.setPos(glm::vec3(-10.0,5.0,0.0));
    m_velocity = glm::vec3(0.0,0.0,0.0);
    m_force = glm::vec3(0.0,0.0,0.0);

    m_mass = 1.0;
    m_lowerBoundary = 0.0;
    m_speed = 0.0;
    m_angleXY = 0.0;
    m_angleXZ = 0.0;
    m_time = 0.0;
    m_deltaTime = 0.01;
}
