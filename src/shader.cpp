#include "shader.h"

Shader::Shader(){

}

// HELPER FUNCTION TO CREATE A SPECIFIC SHADER
GLuint Shader::CreateShader(const string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType); // CREATE THE SHADER

    // ERROR CHECKING
    if (shader == 0){
        cerr << "Error: Shader creation failed!" << endl;
    }

    //CONVERT STD STRING TO C STRING SINCE OPENGL IS A C PROGRAM
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLengths[0] = text.length();

    // SEND THE SOURCE CODE TO OPENGL SO THAT IT CAN COMPILE IT
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!"); // CHECK IF THE COMPILATION FAILED

    return shader;
}

// LOAD THE TEXT FILE FROM THE HARD DRIVE
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

//USED TO CHECK AND GENERATE ERROR MESSAGES THAT THE SHADER GENERATED IF ANY
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

// CONSTRUCTOR ACCEPTS THE PATH OF THE FILE
Shader::Shader(const string& filename){
    m_program = glCreateProgram(); // CREATE A NEW SHADER PROGRAM WHICH RETURNS SOME NUMBER TO REFER TO IT BY
    m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER); // CREATE THE VERTEX SHADER
    m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER); // CREATE THE FRAGMENT SHADER

    // ATTACH THE SHADERS TO THE PROGRAM
    for(unsigned int i = 0;i<NUM_SHADERS; i++){
        glAttachShader(m_program, m_shaders[i]); // THIS WILL TAKE THE PROGRAM AND ADD THE SHADER TO IT
    }

    glBindAttribLocation(m_program, 0,"position"); // TELLS OPENGL WHAT PART OF THE DATA TO READ AND WHAT VARIABLE IN THE SHADER PORGRAM
    glBindAttribLocation(m_program, 1,"texCoord"); // TELLS OPENGL WHAT PART OF THE DATA TO READ AND WHAT VARIABLE IN THE SHADER PORGRAM

    glLinkProgram(m_program); //LINK THE PROGRAM
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed!"); //ERROR CHECKER

    glValidateProgram(m_program); // VALIDATE THE PROGRAM IF IT HAS THE VALID SHADER
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed!"); //ERROR CHECKER

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program,"transform"); // GET THE HANDLE TO THE UNIFORM
}

// JUST LIKE THE CONSTRUCTOR ACCEPTS THE PATH OF THE FILE
void Shader::init(const string& filename){
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

// DECONSTRUCTOR: DELETES THE SHADER AND THE PROGRAM
Shader::~Shader(){
    //DELETE THE INDIVIDUAL SHADERS
    for(unsigned int i = 0;i<NUM_SHADERS; i++){
        glDetachShader(m_program,m_shaders[i]); // DETACH THE SHADER
        glDeleteShader(m_shaders[i]); // DELETE THE SHADER
    }
    glDeleteProgram(m_program); // DELETE THE PROGRAM
}

//      SET THE GPU IN A STATE SO THAT IT IS USING THE FRAGMENT AND VERTEX SHADER THAT THIS CLASS WILL BUILD
void Shader::Bind(){
    glUseProgram(m_program); // JUST BINDS THE SHADER TO THE PROGRAM
}

// UPDATE THE TRANSFORMATION
void Shader::Update(const Transform& transform, const Camera& camera){
    glm::mat4 model = camera.getViewProjection() * transform.getModel(); // GET THE TRANSFORMATION MODEL

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]); // UPDATE THE TRANSFORMATION
}

