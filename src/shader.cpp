#include "shader.h"


GLuint Shader::CreateShader(const string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0){
        cerr << "Error: Shader creation failed!" << endl;
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

    return shader;
}

string Shader::LoadShader(const string& fileName){
    ifstream file;
    file.open((fileName).c_str());

    string output;
    string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		cerr << "Unable to load shader: " << fileName << endl;
    }

    return output;
}



void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        cerr << errorMessage << ": '" << error << "'" << endl;
    }
}

Shader::Shader(const string& filename){
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0;i<NUM_SHADERS; i++){
        glAttachShader(m_program, m_shaders[i]);
    }

    glBindAttribLocation(m_program, 0,"position");
    glBindAttribLocation(m_program, 1,"texCoord");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed!");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed!");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program,"transform");
}

Shader::~Shader(){
    for(unsigned int i = 0;i<NUM_SHADERS; i++){
        glDetachShader(m_program,m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

void Shader::Bind(){
    glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera){
    glm::mat4 model = camera.getViewProjection() * transform.getModel();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

