#include "texture.h"

Texture::Texture(){

}

// CONSTRUCTOR THAT TAKE THE FILE PATH
Texture::Texture(const string& fileName){
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(),&width, &height, &numComponents, 4); // LOAD THE TEXTURE FROM THE FILE

    // ERROR CHECKING IF TEXTURE LOADING FAILED
    if (imageData == NULL){
        cerr << "Texture loading failed for texture: " << fileName << endl;
    }

    glGenTextures(1, &m_texture); // GENERATE SPACE/BUFFER FOR THE TEXTURE
    glBindTexture(GL_TEXTURE_2D, m_texture);// BIND THE TEXTURE

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // CONTROLS TEXTURE WRAPPING FOR WIDTH, INCASE PIXEL IS OUT OF BOUNDS THEN REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // CONTROLS TEXTURE WRAPPING FOR HEIGHT, INCASE PIXEL IS OUT OF BOUNDS THEN REPEAT

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // HOW TO HANDLE MINIFICATION OF PIXEL
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // HOW TO HANDLE MAGNIFICATION OF PIXEL

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); // SEND THE TEXTURE TO THE GPU

    stbi_image_free(imageData); // FREE OR DELETE THE FILE
}

// CONSTRUCTOR THAT TAKE THE FILE PATH
void Texture::init(const string& fileName){
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(),&width, &height, &numComponents, 4);

    if (imageData == NULL){
        cerr << "Texture loading failed for texture: " << fileName << endl;
    }

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);//changed to 3d

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

//DECONSTRUCTOR: DELETE THE TEXTURE
Texture::~Texture(){
    glDeleteTextures(1, &m_texture);
}

// BIND THE TEXTURE
void Texture::Bind(unsigned int unit){
    assert(unit >=0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture); // BIND THE TEXTURE
}
