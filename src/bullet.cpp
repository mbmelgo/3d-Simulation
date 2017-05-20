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
    m_transform.setRot(glm::vec3(0.0,0.0,angleXY));
    m_angleXY = angleXY * 3.141459/180.00;
}

void Bullet::setAngleXZ(float angleXZ){
    m_transform.setRot(glm::vec3(0.0,angleXZ,0.0));
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

void Bullet::applyForce(glm::vec3 force){
    force =  force / m_mass;
    m_force = m_force + force;
}

void Bullet::translate(glm::vec3 position){
    m_transform.setPos(position);
}

void Bullet::rotate(glm::vec3 rot){
    if(isnan(rot.x)){
        rot.x = 0.0;
    }
    if(isnan(rot.y)){
        rot.y = 0.0;
    }
    if(isnan(rot.z)){
        rot.z = 0.0;
    }
//    glm::vec3 newRot = glm::vec3(m_transform.getRot().x+rot.x,m_transform.getRot().y+rot.y,m_transform.getRot().z+rot.z);
    m_transform.setRot(rot);
}

void Bullet::initBullet(){
    m_velocity = glm::vec3(
                           m_speed * cos(m_angleXY) * cos(m_angleXZ),
                           m_speed * sin(m_angleXY),
                           m_speed * cos(m_angleXY) * sin(m_angleXZ)
                           );
}

float Bullet::magnitude(glm::vec3 vect){
   return sqrt((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z));
}

float Bullet::getAngle(glm::vec3 currentPosition, glm::vec3 nextPosition){
    //Find the scalar/dot product of the provided 2 Vectors
   float dotProduct = glm::dot(currentPosition, nextPosition);
   //Find the product of both magnitudes of the vectors then divide dot from it
   dotProduct = dotProduct / (magnitude(currentPosition) * magnitude(nextPosition));
   //Get the arc cosin of the angle, you now have your angle in radians
   float arcAcos = acos(dotProduct);
   //Convert to degrees by Multiplying the arc cosin by 180/M_PI
   return arcAcos * 180 / M_PI;
}

void Bullet::getYawAngle(glm::vec3 nextPosition){
    m_angleYaw = getAngle(glm::vec3(0.0,0.0,m_transform.getPos().z),glm::vec3(0.0,0.0,nextPosition.z));
}

void Bullet::getRollAngle(glm::vec3 nextPosition){
    m_angleRoll = getAngle(glm::vec3(m_transform.getPos().x,0.0,0.0),glm::vec3(nextPosition.x,0.0,0.0));
}

void Bullet::getPitchAngle(glm::vec3 nextPosition){
    m_anglePitch = getAngle(glm::vec3(0.0,m_transform.getPos().y,0.0),glm::vec3(0.0,nextPosition.y,0.0));
}

glm::vec3 Bullet::getRotations(glm::vec3 nextPosition){
    getYawAngle(nextPosition);
    getRollAngle(nextPosition);
    getPitchAngle(nextPosition);

    if(isnan(m_anglePitch)){
        m_anglePitch = 0.0;
    }
    if(isnan(m_angleYaw)){
        m_angleYaw = 0.0;
    }
    if(isnan(m_angleRoll)){
        m_angleRoll = 0.0;
    }

//    glm::vec3 currentPosition(m_transform.getPos().x,m_transform.getPos().y,m_transform.getPos().z);
//
//    //a==yaw b == pitch y == roll
//    float x =   (currentPosition.x * (cos(m_angleYaw) * cos(m_anglePitch))) +
//                (currentPosition.y * ( (cos(m_angleYaw)*sin(m_anglePitch)*sin(m_angleRoll)) - (sin(m_angleYaw)*cos(m_angleRoll)) )) +
//                (currentPosition.z * ( (cos(m_angleYaw)*sin(m_anglePitch)*cos(m_angleRoll)) + (sin(m_angleYaw)*sin(m_angleRoll)) ));
//
//    float y =   (currentPosition.x * (sin(m_angleYaw)*cos(m_anglePitch)) ) +
//                (currentPosition.y * ( (sin(m_angleYaw)*sin(m_anglePitch)*sin(m_angleRoll)) + (cos(m_angleYaw)*cos(m_angleRoll)) ))+
//                (currentPosition.z * ( (sin(m_angleYaw)*sin(m_anglePitch)*cos(m_angleRoll)) - (cos(m_angleYaw)*sin(m_angleRoll)) ));
//
//    float z =   (currentPosition.x * asin(m_anglePitch)) +
//                (currentPosition.y * (cos(m_anglePitch)*sin(m_angleRoll))) +
//                (currentPosition.z * (cos(m_anglePitch)*cos(m_angleRoll)));

    glm::vec3 rot(m_angleRoll,m_anglePitch,m_angleYaw);
    return rot;
}

void Bullet::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    applyForce(m_gravity);

    m_velocity = m_velocity + m_force/m_mass * m_deltaTime;
    glm::vec3 nextPosition = m_transform.getPos() + m_velocity * m_deltaTime;

    glm::vec3 rot = getRotations(nextPosition);
    if(nextPosition.y <= m_lowerBoundary){
        m_velocity.y = 0.0f;
        nextPosition.y = m_lowerBoundary;
    }
    translate(nextPosition);
    rotate(rot);
    m_mesh.Draw();
    m_force = glm::vec3(0.0,0.0,0.0);
    if (m_transform.getPos().y <= 0.1){
        m_transform.getPos().y = 0.1;
        glm::vec3 friction = glm::vec3(m_velocity.x*-1,m_velocity.y,m_velocity.z);
        friction.x = friction.x * m_frictionConstant;
        friction.y = friction.y * m_frictionConstant;
        friction.z = friction.z * m_frictionConstant;
        applyForce(friction);
    }
    if(m_transform.getPos().x>=19.65 && !m_hasTarget){
        m_target = glm::vec3(m_transform.getPos().x,m_transform.getPos().y,m_transform.getPos().z);
        m_targetVelocity = m_velocity;
        m_hasTarget = true;
        if (m_velocity.x < m_velocityLimit && m_target.x >= 19.65 &&
            m_target.y <= m_UpperRight.y && m_target.y >= m_LowerRight.y &&
            m_target.z <= m_UpperLeft.z && m_target.z >= m_UpperRight.z){
            m_velocity.x = 0.0;
        }
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
    m_target = glm::vec3(0.0,0.0,0.0);

    m_mass = 1.0;
    m_lowerBoundary = 0.0;
    m_speed = 0.0;
    m_angleXY = 0.0;
    m_angleXZ = 0.0;
    m_time = 0.0;
    m_deltaTime = 0.01;
}
