#ifndef TEXTURE_H
#define TEXTURE_H
#define GLEW_STATIC

#include <GL/glew.h>
#include <string>
#include <cassert>
#include <iostream>

#include "stb_image.h"

using namespace std;

class Texture
{
    public:
        Texture(const string& fileName);
        virtual ~Texture();

        void Bind(unsigned int unit);

    protected:

    private:
        Texture(const Texture& other){};
        void operator=(const Texture& other){};

        GLuint m_texture;
};

#endif // TEXTURE_H
