#include "shards.h"

Shards::Shards(){
    //ctor
}

Shards::~Shards(){
    //dtor
}

Shards::Shards(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass, glm::vec3 velocity, bool breaksOnly){
     m_mesh.initV(vertices,numVertices,indices,numIndices);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);

    m_velocity = glm::vec3(0.0,0.0,0.0);
    m_force = glm::vec3(0.0,0.0,0.0);

    m_position = glm::vec3(  0.0,
                             mid(vertices[0].getPos()->y, vertices[1].getPos()->y, vertices[2].getPos()->y),
                             mid(vertices[0].getPos()->z, vertices[1].getPos()->z, vertices[2].getPos()->z)
                                 );
    m_positionY = 0.0 - m_position.y;
    m_velocity = velocity;
    m_transform.setPos(glm::vec3(0.0,0.0,0.0));
    m_mass = mass;
    m_breaksOnly = breaksOnly;
    m_time = 0.0;
    m_deltaTime = 0.01;
}

void Shards::translate(glm::vec3 position){
    m_transform.setPos(position);
    m_position = position;
}

void Shards::applyForce(glm::vec3 force){
    force =  force / m_mass;
    m_force = m_force + force;
}

void Shards::rotate(glm::vec3 rot){
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

float Shards::magnitude(glm::vec3 vect){
   return sqrt((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z));
}

float Shards::getAngle(glm::vec3 currentPosition, glm::vec3 nextPosition){
    //Find the scalar/dot product of the provided 2 Vectors
   float dotProduct = glm::dot(currentPosition, nextPosition);
   //Find the product of both magnitudes of the vectors then divide dot from it
   dotProduct = dotProduct / (magnitude(currentPosition) * magnitude(nextPosition));
   //Get the arc cosin of the angle, you now have your angle in radians
   float arcAcos = acos(dotProduct);
   //Convert to degrees by Multiplying the arc cosin by 180/M_PI
   return arcAcos * 180 / M_PI;
}

void Shards::getYawAngle(glm::vec3 nextPosition){
    m_angleYaw = getAngle(glm::vec3(0.0,0.0,m_transform.getPos().z),glm::vec3(0.0,0.0,nextPosition.z));
}

void Shards::getRollAngle(glm::vec3 nextPosition){
    m_angleRoll = getAngle(glm::vec3(m_transform.getPos().x,0.0,0.0),glm::vec3(nextPosition.x,0.0,0.0));
}

void Shards::getPitchAngle(glm::vec3 nextPosition){
    m_anglePitch = getAngle(glm::vec3(0.0,m_transform.getPos().y,0.0),glm::vec3(0.0,nextPosition.y,0.0));
}

glm::vec3 Shards::getRotations(glm::vec3 nextPosition){
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

void Shards::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);

    if(!m_stop && !m_breaksOnly){
        applyForce(m_gravity);
        m_velocity = m_velocity + m_force/m_mass * m_deltaTime;
        glm::vec3 nextPosition = m_transform.getPos() + m_velocity * m_deltaTime;
        glm::vec3 rot = getRotations(nextPosition);
        translate(nextPosition);
        rotate(rot);
    }
    m_mesh.Draw();
    m_force = glm::vec3(0.0,0.0,0.0);
    if (m_transform.getPos().y < m_positionY){
        m_transform.getPos().y = m_transform.getPos().y;
        m_stop = true;
    }
    m_time = m_time + m_deltaTime;
}

float Shards::mid(float x, float y, float z){
    return (x + y + z) / 3.0 ;
}

void Shards::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass, glm::vec3 velocity, bool breaksOnly){
    m_mesh.initV(vertices,numVertices,indices,numIndices);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);

    m_velocity = glm::vec3(0.0,0.0,0.0);
    m_force = glm::vec3(0.0,0.0,0.0);

    m_position = glm::vec3(  0.0,
                             mid(vertices[0].getPos()->y, vertices[1].getPos()->y, vertices[2].getPos()->y),
                             mid(vertices[0].getPos()->z, vertices[1].getPos()->z, vertices[2].getPos()->z)
                                 );
    m_positionY = 0.0 - m_position.y;
    m_velocity = velocity;
    m_transform.setPos(glm::vec3(0.0,0.0,0.0));
    m_mass = mass;
    m_breaksOnly = breaksOnly;
    m_time = 0.0;
    m_deltaTime = 0.01;
}
