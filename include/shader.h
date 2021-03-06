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

// PROGRAMS FOR THE GPU WHICH HANDLE SPECIFIC TASK FOR THE GPU
// E.G VERTEX SHADER = TAKES THE DATA THAT IS GIVEN TO THE GPU AND CONVERT IT TO SOMETHING THAT THE GPU CAN UNDERSTAND
// FRAGMENT SHADER = TAKES THE PIXELS GENERATED BY THE GPU AND DECIDES WHAT COLOR IT IS

// LOADER OF THE SHADER PROGRAM AND BUILD THEM AND SEND THE BUILT FILES TO THE GPU
class Shader
{
    public:
        Shader();
        Shader(const string& filename);// CONSTRUCTOR ACCEPTS THE PATH OF THE FILE
        virtual ~Shader();// DECONSTRUCTOR: DELETES THE SHADER AND THE PROGRAM

        void Bind();    //      SET THE GPU IN A STATE SO THAT IT IS USING THE FRAGMENT AND VERTEX SHADER THAT THIS CLASS WILL BUILD
        void Update(const Transform& transform, const Camera& camera); // UPDATE THE TRANSFORMATION
        void init(const string& filename);// JUST LIKE THE CONSTRUCTOR ACCEPTS THE PATH OF THE FILE

    protected:

    private:
        static const unsigned int NUM_SHADERS = 2; // FOR VERTEX AND FRAGMENT SHADER

        enum {
            TRANSFORM_U,
            NUM_UNIFORMS
        };

        string LoadShader(const string& fileName); // LOAD THE TEXT FILE FROM THE HARD DRIVE
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage); //USED TO CHECK AND GENERATE ERROR MESSAGES THAT THE SHADER GENERATED IF ANY
        GLuint CreateShader(const string& text, GLenum shaderType); // HELPER FUNCTION TO CREATE A SPECIFIC SHADER

        GLuint m_program; // REFERENCE TO THE GL PROGRAM
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
