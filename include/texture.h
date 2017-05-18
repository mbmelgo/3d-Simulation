#ifndef TEXTURE_H
#define TEXTURE_H
#define GLEW_STATIC

#include <GL/glew.h>
#include <string>
#include <cassert>
#include <iostream>

#include "stb_image.h"

using namespace std;

// LOAD AND USE TEXTURE WITH OPENGL
class Texture
{
    public:
        Texture();
        Texture(const string& fileName); // CONSTRUCTOR THAT TAKE THE FILE PATH
        virtual ~Texture(); //DECONSTRUCTOR: DELETE THE TEXTURE

        void Bind(unsigned int unit); // BIND THE TEXTURE
        void init(const string& filename);// CONSTRUCTOR THAT TAKE THE FILE PATH

    protected:

    private:
        GLuint m_texture; //REFERENCE TO THE HANDLE TO THE TEXTURE
};

#endif // TEXTURE_H
