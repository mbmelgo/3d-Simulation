#include "plane.h"

Plane::Plane(){
    //ctor
}

Plane::~Plane(){
    //dtor
}

void Plane::setPosition(glm::vec3 position){
    m_transform.setPos(position);
}

glm::vec3 Plane::getPosition(){
    return m_transform.getPos();
}

void Plane::setScale(glm::vec3 scale){
    m_transform.setScale(scale);
}

glm::vec3 Plane::getScale(){
    return m_transform.getScale();
}

Plane::Plane(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName){
    m_mesh.initV(vertices,numVertices,indices,numIndices);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}


void Plane::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const string& shaderFileName, const string& textureFileName){
    m_mesh.initV(vertices,numVertices,indices,numIndices);
    m_shader.init(shaderFileName);
    m_texture.init(textureFileName);
}


void Plane::drawCoordinates(){
    glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    // x aix

    glVertex3f(-100.0, 0.0f, 0.0f);
    glVertex3f(100.0, 0.0f, 0.0f);

    // arrow
    glVertex3f(100.0, 0.0f, 0.0f);
    glVertex3f(100.0, 1.0f, 0.0f);

    glVertex3f(100.0, 0.0f, 0.0f);
    glVertex3f(100.0, -1.0f, 0.0f);
    glEnd();
    glFlush();



    // y
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -100.0f, 0.0f);
    glVertex3f(0.0, 100.0f, 0.0f);

    // arrow
    glVertex3f(0.0, 100.0f, 0.0f);
    glVertex3f(1.0, 100.0f, 0.0f);

    glVertex3f(0.0, 100.0f, 0.0f);
    glVertex3f(-1.0, 100.0f, 0.0f);
    glEnd();
    glFlush();

    // z
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-100.0f );
    glVertex3f(0.0, 0.0f ,100.0f );

    // arrow
    glVertex3f(0.0, 0.0f ,100.0f );
    glVertex3f(0.0, 1.0f ,100.0f );

    glVertex3f(0.0, 0.0f ,100.0f );
    glVertex3f(0.0, -1.0f ,100.0f );
    glEnd();
    glFlush();
}

void Plane::draw(Camera camera){
    m_shader.Bind();
    m_texture.Bind(0);
    m_shader.Update(m_transform, camera);
    if(m_drawCoordinates){
        drawCoordinates();
    }
    m_mesh.Draw();
}
