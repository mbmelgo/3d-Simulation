#include "mesh.h"

// HELPER METHOD TO INITIALIZE THE MESH
void Mesh::InitMesh(const IndexedModel& model){
    m_drawCount = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject); // GENERATE THE VERTEX ARRAY OBJECT AND STORE IT TO THE SECOND PARAMETER
    glBindVertexArray(m_vertexArrayObject); // BIND THE VERTEX ARRAY OBJECT

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer); // GENERATE THE BUFFERS NEEDED FROM THE GPU
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]); // BIND THOSE BUFFER SO THAT OPENGL WILL KNOW HOW TO INTERPRET THOSE BUFFERS
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);//PUT ALL THE VERTEX DATA IN THE ARRAY IN THE GPU

    // TELL OPENGL HOW TO INTERPRET THE DATA
    glEnableVertexAttribArray(0);   // ENABLE THE POSITION ATTRIBUTE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // TELL OPENGL HOW TO LOOK AT THE ATTRIBUTE AS AN ARRAY

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[TEXCOORD_VB]); // BIND THOSE BUFFER SO THAT OPENGL WILL KNOW HOW TO INTERPRET THOSE BUFFERS
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);//PUT ALL THE VERTEX DATA IN THE ARRAY IN THE GPU

    glEnableVertexAttribArray(1); // ENABLE THE TEXTURE ATTRIBUTE
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // TELL OPENGL HOW TO LOOK AT THE ATTRIBUTE AS AN ARRAY

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0); // UNBIND THE VERTEX ARRAY OBJECT
}

// THE CONSTRUCTOR WHICH ACCEPT THE PATH OF THE OBJ FILE
Mesh::Mesh(const string& fileName){
    IndexedModel model = OBJModel(fileName).ToIndexedModel();

    InitMesh(model);
}

Mesh::Mesh(){

}

// THE CONSTRUCTOR WHICH ACCEPT THE PATH OF THE OBJ FILE
void Mesh::init(const string& fileName){
    IndexedModel model = OBJModel(fileName).ToIndexedModel();

    InitMesh(model);
}

// THE CONSTRUCTOR WHICH ACCEPTS VERTICES
void Mesh::initV(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices){
    IndexedModel model;

    for(int i=0;i<numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
    }

    for(int i=0;i<numIndices; i++){
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

// THE CONSTRUCTOR WHICH ACCEPTS VERTICES
Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices){
    IndexedModel model;

    for(int i=0;i<numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
    }

    for(int i=0;i<numIndices; i++){
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

// DELETE THE VERTEX ARRAY OBJECT
Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw(){
    glBindVertexArray(m_vertexArrayObject); // BIND THE VERTEX ARRAY OBJECT

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0); // DRAW THE ARRAY OF DATA

    glBindVertexArray(0); // UNBIND THE VERTEX ARRAY OBJECT
}

