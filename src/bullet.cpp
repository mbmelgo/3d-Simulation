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

void Bullet::setRotation(glm::vec3 rotation){
    m_transform.setRot(rotation);
    m_rotation = rotation;
}

glm::vec3 Bullet::getRotation(){
    return m_rotation;
}

void Bullet::applyForce(glm::vec3 force){
    force = force / m_mass;
    m_acceleration = m_acceleration + force;
}

void Bullet::translate(){
    m_transform.setPos(m_nextPosition);
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToEuler/index.htm
void Bullet::toEuler(glm::vec3 axis,float angle) {
	float s = sin(angle);
	float c = cos(angle);
	float t = 1-c;
	if ((axis.x*axis.y*t + axis.z*s) > 0.998) { // north pole singularity detected
		m_angleY = 2*atan2(axis.x*sin(angle/2),cos(angle/2));
		m_angleX = 2.14/2;
		m_angleZ = 0;
		return;
	}
	if ((axis.x*axis.y*t + axis.z*s) < -0.998) { // south pole singularity detected
		m_angleY = -2*atan2(axis.x*sin(angle/2),cos(angle/2));
		m_angleX = -2.14/2;
		m_angleZ = 0;
		return;
	}
	m_angleY = atan2(axis.y * s- axis.x * axis.z * t , 1 - (axis.y*axis.y + axis.z*axis.z ) * t);
	m_angleX = asin(axis.x * axis.y * t + axis.z * s) ;
	m_angleZ = atan2(axis.x * s - axis.y * axis.z * t , 1 - (axis.x*axis.x + axis.z*axis.z) * t);
}


void Bullet::findAngle(){
   glm::vec3 crossProduct = glm::cross(m_position,m_nextPosition);
   float dotProduct = (m_nextPosition.x * m_position.x) + (m_nextPosition.y * m_position.y) + (m_nextPosition.z * m_position.z);
   toEuler(crossProduct,dotProduct);
}

void Bullet::rotate(){
    findAngle();
    m_rotation = glm::vec3(m_angleX,m_angleY,m_angleZ);
    setRotation(m_rotation);
}

void Bullet::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);

    m_velocity = m_velocity + m_acceleration;
    m_nextPosition = m_nextPosition + m_velocity;

    if(m_nextPosition.y <= m_lowerBoundary){
        m_velocity.y = 0.0f;
        m_nextPosition.y = m_lowerBoundary;
    }
    translate();
    rotate();
    m_mesh.Draw();
    m_acceleration = m_acceleration * 0.0f;
    m_position = m_nextPosition;
    if (m_position.y < -10.0){
        m_position.y = -10.0;
    }
}

void Bullet::init(const string& meshFileName, const string& shaderFileName, const string& textureFileName){
    m_mesh.init(meshFileName);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);

    setPosition(glm::vec3(16.0,0.0,0.0));
    m_nextPosition = glm::vec3(16.0,0.0,0.0);
    setVelocity(glm::vec3(0.0,0.0,0.0));
    setAcceleration(glm::vec3(0.0,0.0,0.0));
    setRotation(glm::vec3(0.0,0.0,0.0));
}
