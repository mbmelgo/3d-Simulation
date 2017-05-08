#include "shards.h"

Shards::Shards(){
    //ctor
}

Shards::~Shards(){
    //dtor
}

Shards::Shards(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass){
    m_mesh.initV(vertices,numVertices,indices,numIndices);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}

void Shards::translate(glm::vec3 position){
    m_transform.setPos(position);
    m_position = position;
}

void Shards::applyForce(glm::vec3 force){
    force =  force / m_mass;
    m_force = m_force + force;
}

void Shards::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    applyForce(m_gravity);

    m_velocity = m_velocity + m_force/m_mass * m_deltaTime;
    glm::vec3 nextPosition = m_transform.getPos() + m_velocity * m_deltaTime;

    if(!m_stop){
        translate(nextPosition);
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

void Shards::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName, float mass){
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
    m_transform.setPos(glm::vec3(0.0,0.0,0.0));
    m_mass = mass;
    m_time = 0.0;
    m_deltaTime = 0.01;
}
