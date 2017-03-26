#ifndef SHADER_H
#define SHADER_H
#define GLEW_STATIC

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include "transform.h"
#include "camera.h"

using namespace std;

class Shader
{
    public:
        Shader(const string& filename);
        virtual ~Shader();

        void Bind();
        void Update(const Transform& transform, const Camera& camera);

    protected:

    private:
        static const unsigned int NUM_SHADERS = 2;
        Shader(const Shader& other){};
        void operator=(const Shader& other){};

        enum {
            TRANSFORM_U,
            NUM_UNIFORMS
        };

        string LoadShader(const string& fileName);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
        GLuint CreateShader(const string& text, GLenum shaderType);

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
