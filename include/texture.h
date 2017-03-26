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
        Texture();
        Texture(const string& fileName);
        virtual ~Texture();

        void Bind(unsigned int unit);
        void init(const string& filename);

    protected:

    private:
        GLuint m_texture;
};

#endif // TEXTURE_H
