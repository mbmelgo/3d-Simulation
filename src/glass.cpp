#include "glass.h"

Glass::Glass(){
    //dtor
}

Glass::Glass(const string& shaderFileName, const string& textureFileName){
    m_shader = shaderFileName;
    m_texture = textureFileName;
}

Glass::~Glass(){
    //dtor
}

float Glass::mid(float x, float y){
    return (x + y) / 2.0 ;
}

float Glass::third(float x, float y){
    return (x + y) / 3.0 ;
}

void Glass::putShards(int position, Vertex a, Vertex b, Vertex c){
    Vertex vertices[] = {a,b,c};
    unsigned int indices[] = { 0,1,2 };
    m_shards[position].init(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]), m_shader, m_texture, 1.0);
}

void Glass::generateShards(){
    glm::vec3 midUpper  = glm::vec3(m_target.x,  m_UpperRight.y ,    m_target.z);
    glm::vec3 midLeft   = glm::vec3(m_target.x,  m_target.y ,        m_UpperLeft.z);
    glm::vec3 midLower  = glm::vec3(m_target.x,  m_LowerRight.y ,    m_target.z);
    glm::vec3 midRight  = glm::vec3(m_target.x,  m_target.y  ,        m_UpperRight.z );

    glm::vec3 midUpperRight  =  glm::vec3(m_target.x,     m_UpperRight.y ,                 mid(m_UpperRight.z,midUpper.z));
    glm::vec3 midUpperLeft  =   glm::vec3(m_target.x,     m_UpperLeft.y ,                  mid(midUpper.z,m_UpperLeft.z));
    glm::vec3 midLeftUpper  =   glm::vec3(m_target.x,     mid(m_UpperLeft.y,midLeft.y) ,   m_UpperLeft.z);
    glm::vec3 midLeftLower  =   glm::vec3(m_target.x,     mid(midLeft.y,m_LowerLeft.y) ,   m_LowerLeft.z);

    glm::vec3 midLowerLeft  =   glm::vec3(m_target.x,     m_LowerLeft.y ,                    mid(midLower.z,m_LowerLeft.z));
    glm::vec3 midLowerRight  =  glm::vec3(m_target.x,     m_LowerRight.y ,                   mid(m_LowerRight.z,midLower.z));
    glm::vec3 midRightLower  =  glm::vec3(m_target.x,     mid(midRight.y,m_LowerRight.y) ,   m_LowerRight.z);
    glm::vec3 midRightUpper  =  glm::vec3(m_target.x,     mid(m_UpperRight.y,midRight.y) ,   m_UpperRight.z);

    float mids[] = {    abs(mid(midUpper.y, m_target.y)),
                        abs(mid(midLower.y, m_target.y)),
                        abs(mid(midLeft.z, m_target.z)),
                        abs(mid(midRight.z, m_target.z))
                    };

    float minimum = *min_element(mids,mids+4);

    glm::vec3 A = glm::vec3(m_target.x, m_target.y+minimum,m_target.z);
    glm::vec3 I = glm::vec3(m_target.x, m_target.y-minimum,m_target.z);

    float angle =  atan((midUpperLeft.z - m_target.z) / (midUpper.y - m_target.y));
    glm::vec3 B = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 P = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));
    glm::vec3 H = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 J = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));

    angle =  atan((m_UpperLeft.z - m_target.z) / (midUpper.y - m_target.y));
    glm::vec3 C = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 O = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));
    glm::vec3 G = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 K = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));

    angle =  atan((midLeftUpper.z - m_target.z) / (midLeftUpper.y - m_target.y));
    glm::vec3 D = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 N = glm::vec3(m_target.x, m_target.y+(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));
    glm::vec3 F = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z+(minimum * sin(angle)));
    glm::vec3 L = glm::vec3(m_target.x, m_target.y-(minimum * cos(angle)), m_target.z-(minimum * sin(angle)));

    glm::vec3 E = glm::vec3(m_target.x, m_target.y, m_target.z+minimum);
    glm::vec3 M = glm::vec3(m_target.x, m_target.y, m_target.z-minimum);


// INNER
    putShards(0,Vertex(A,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(B,glm::vec2(1,0.0)));
    putShards(1,Vertex(B,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(C,glm::vec2(1,0.0)));
    putShards(2,Vertex(C,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(D,glm::vec2(1,0.0)));
    putShards(3,Vertex(D,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(E,glm::vec2(1,0.0)));
    putShards(4,Vertex(E,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(F,glm::vec2(1,0.0)));
    putShards(5,Vertex(F,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(G,glm::vec2(1,0.0)));
    putShards(6,Vertex(G,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(H,glm::vec2(1,0.0)));
    putShards(7,Vertex(H,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(I,glm::vec2(1,0.0)));
    putShards(8,Vertex(I,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(J,glm::vec2(1,0.0)));
    putShards(9,Vertex(J,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(K,glm::vec2(1,0.0)));
    putShards(10,Vertex(K,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(L,glm::vec2(1,0.0)));
    putShards(11,Vertex(L,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(M,glm::vec2(1,0.0)));
    putShards(12,Vertex(M,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(N,glm::vec2(1,0.0)));
    putShards(13,Vertex(N,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(O,glm::vec2(1,0.0)));
    putShards(14,Vertex(O,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(P,glm::vec2(1,0.0)));
    putShards(15,Vertex(P,glm::vec2(0.0,1)),Vertex(m_target,glm::vec2(0.0,0.0)),Vertex(A,glm::vec2(1,0.0)));

//OUTER
    putShards(16,Vertex(midUpper,glm::vec2(0.0,1)),Vertex(A,glm::vec2(0.0,0.0)),Vertex(midUpperLeft,glm::vec2(1,0.0)));
    putShards(17,Vertex(midUpperLeft,glm::vec2(0.0,1)),Vertex(A,glm::vec2(0.0,0.0)),Vertex(B,glm::vec2(1,0.0)));
    putShards(18,Vertex(midUpperLeft,glm::vec2(0.0,1)),Vertex(B,glm::vec2(0.0,0.0)),Vertex(m_UpperLeft,glm::vec2(1,0.0)));
    putShards(19,Vertex(m_UpperLeft,glm::vec2(0.0,1)),Vertex(B,glm::vec2(0.0,0.0)),Vertex(C,glm::vec2(1,0.0)));
    putShards(20,Vertex(m_UpperLeft,glm::vec2(0.0,1)),Vertex(C,glm::vec2(0.0,0.0)),Vertex(D,glm::vec2(1,0.0)));
    putShards(21,Vertex(m_UpperLeft,glm::vec2(0.0,1)),Vertex(D,glm::vec2(0.0,0.0)),Vertex(midLeftUpper,glm::vec2(1,0.0)));
    putShards(22,Vertex(midLeftUpper,glm::vec2(0.0,1)),Vertex(D,glm::vec2(0.0,0.0)),Vertex(E,glm::vec2(1,0.0)));
    putShards(23,Vertex(midLeftUpper,glm::vec2(0.0,1)),Vertex(E,glm::vec2(0.0,0.0)),Vertex(midLeft,glm::vec2(1,0.0)));
    putShards(24,Vertex(midLeft,glm::vec2(0.0,1)),Vertex(E,glm::vec2(0.0,0.0)),Vertex(midLeftLower,glm::vec2(1,0.0)));
    putShards(25,Vertex(E,glm::vec2(0.0,1)),Vertex(F,glm::vec2(0.0,0.0)),Vertex(midLeftLower,glm::vec2(1,0.0)));
    putShards(26,Vertex(F,glm::vec2(0.0,1)),Vertex(m_LowerLeft,glm::vec2(0.0,0.0)),Vertex(midLeftLower,glm::vec2(1,0.0)));
    putShards(27,Vertex(F,glm::vec2(0.0,1)),Vertex(G,glm::vec2(0.0,0.0)),Vertex(m_LowerLeft,glm::vec2(1,0.0)));
    putShards(28,Vertex(G,glm::vec2(0.0,1)),Vertex(H,glm::vec2(0.0,0.0)),Vertex(m_LowerLeft,glm::vec2(1,0.0)));
    putShards(29,Vertex(H,glm::vec2(0.0,1)),Vertex(midLowerLeft,glm::vec2(0.0,0.0)),Vertex(m_LowerLeft,glm::vec2(1,0.0)));
    putShards(30,Vertex(I,glm::vec2(0.0,1)),Vertex(midLowerLeft,glm::vec2(0.0,0.0)),Vertex(H,glm::vec2(1,0.0)));
    putShards(31,Vertex(I,glm::vec2(0.0,1)),Vertex(midLower,glm::vec2(0.0,0.0)),Vertex(midLowerLeft,glm::vec2(1,0.0)));
    putShards(32,Vertex(midLowerRight,glm::vec2(0.0,1)),Vertex(midLower,glm::vec2(0.0,0.0)),Vertex(I,glm::vec2(1,0.0)));
    putShards(33,Vertex(J,glm::vec2(0.0,1)),Vertex(midLowerRight,glm::vec2(0.0,0.0)),Vertex(I,glm::vec2(1,0.0)));
    putShards(34,Vertex(midLowerRight,glm::vec2(0.0,1)),Vertex(J,glm::vec2(0.0,0.0)),Vertex(m_LowerRight,glm::vec2(1,0.0)));
    putShards(35,Vertex(K,glm::vec2(0.0,1)),Vertex(m_LowerRight,glm::vec2(0.0,0.0)),Vertex(J,glm::vec2(1,0.0)));
    putShards(36,Vertex(L,glm::vec2(0.0,1)),Vertex(m_LowerRight,glm::vec2(0.0,0.0)),Vertex(K,glm::vec2(1,0.0)));
    putShards(37,Vertex(L,glm::vec2(0.0,1)),Vertex(midRightLower,glm::vec2(0.0,0.0)),Vertex(m_LowerRight,glm::vec2(1,0.0)));
    putShards(38,Vertex(M,glm::vec2(0.0,1)),Vertex(midRightLower,glm::vec2(0.0,0.0)),Vertex(L,glm::vec2(1,0.0)));
    putShards(39,Vertex(M,glm::vec2(0.0,1)),Vertex(midRight,glm::vec2(0.0,0.0)),Vertex(midRightLower,glm::vec2(1,0.0)));
    putShards(40,Vertex(M,glm::vec2(0.0,1)),Vertex(midRightUpper,glm::vec2(0.0,0.0)),Vertex(midRight,glm::vec2(1,0.0)));
    putShards(41,Vertex(N,glm::vec2(0.0,1)),Vertex(midRightUpper,glm::vec2(0.0,0.0)),Vertex(M,glm::vec2(1,0.0)));
    putShards(42,Vertex(midRightUpper,glm::vec2(0.0,1)),Vertex(N,glm::vec2(0.0,0.0)),Vertex(m_UpperRight,glm::vec2(1,0.0)));
    putShards(43,Vertex(m_UpperRight,glm::vec2(0.0,1)),Vertex(N,glm::vec2(0.0,0.0)),Vertex(O,glm::vec2(1,0.0)));
    putShards(44,Vertex(m_UpperRight,glm::vec2(0.0,1)),Vertex(O,glm::vec2(0.0,0.0)),Vertex(P,glm::vec2(1,0.0)));
    putShards(45,Vertex(m_UpperRight,glm::vec2(0.0,1)),Vertex(P,glm::vec2(0.0,0.0)),Vertex(midUpperRight,glm::vec2(1,0.0)));
    putShards(46,Vertex(midUpperRight,glm::vec2(0.0,1)),Vertex(P,glm::vec2(0.0,0.0)),Vertex(A,glm::vec2(1,0.0)));
    putShards(47,Vertex(midUpperRight,glm::vec2(0.0,1)),Vertex(A,glm::vec2(0.0,0.0)),Vertex(midUpper,glm::vec2(1,0.0)));

}

void Glass::setTarget(glm::vec3 target){
    m_target = target;
    if( m_canBreak && target.x >= m_LowerLeft.x &&
        target.y <= m_UpperRight.y && target.y >= m_LowerRight.y &&
        target.z <= m_UpperLeft.z && target.x >= m_UpperRight.z){
        m_shards[0].setStop(false);
        m_breaks = true;
        generateShards();
    } else {
         Vertex vertices[] = {  Vertex(m_UpperRight,glm::vec2(0.0,1.0)),
                                Vertex(m_LowerRight,glm::vec2(0.0,0.0)),
                                Vertex(m_LowerLeft,glm::vec2(1.0,0.0)),
                                Vertex(m_UpperRight,glm::vec2(0.0,1.0)),
                                Vertex(m_LowerLeft,glm::vec2(1.0,0.0)),
                                Vertex(m_UpperLeft,glm::vec2(1.0,1.0))
                            };
        unsigned int indices[] = { 0,1,2,3,4,5 };
        m_shards[0].init(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]), m_shader, m_texture, 100.0);
        m_shards[0].setStop(true);
    }
}

glm::vec3 Glass::getTarget(){
    return m_target;
}

void Glass::draw(Camera camera){
    if(m_canBreak){
        for(int i=0;i<48;i++){
            m_shards[i].draw(camera);
        }
    } else {
        m_shards[0].draw(camera);
    }
}

void Glass::init(const string& shaderFileName, const string& textureFileName){
    m_shader = shaderFileName;
    m_texture = textureFileName;
}
