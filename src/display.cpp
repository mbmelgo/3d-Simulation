#include "display.h"

Display::Display(int width, int height, const string& title){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if (status != GLEW_OK){
        printf("GLEW FAILED TO INITIALIZED!");
    }

    n_isClosed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


}

Display::~Display(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_GL_DeleteContext(m_window);
    SDL_Quit();
}

void Display::doMovements(){
    if (m_keys[SDLK_a] && !m_firstKey){
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_deltaTime * m_cameraSpeed;
    }
    if (m_keys[SDLK_d] && !m_firstKey){
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_deltaTime * m_cameraSpeed;
    }
    if (m_keys[SDLK_w] && !m_firstKey){
        m_cameraPos += m_deltaTime * m_cameraSpeed * m_cameraFront;
    }
    if (m_keys[SDLK_s] && !m_firstKey){
        m_cameraPos -= m_deltaTime * m_cameraSpeed * m_cameraFront;
    }
//    if(m_cameraPos.x > m_leftBoundary){
//        m_cameraPos.x = m_leftBoundary;
//    } else if(m_cameraPos.x < m_rightBoundary){
//        m_cameraPos.x = m_rightBoundary;
//    }
//    if(m_cameraPos.y > m_upperBoundary){
//        m_cameraPos.y = m_upperBoundary;
//    } else if(m_cameraPos.y < m_lowerBoundary){
//        m_cameraPos.y = m_lowerBoundary;
//    }
//    if(m_cameraPos.z > m_frontBoundary){
//        m_cameraPos.z = m_frontBoundary;
//    } else if(m_cameraPos.z < m_backBoundary){
//        m_cameraPos.z = m_backBoundary;
//    }
//    printf("%f,%f,%f\n",m_cameraPos.x,m_cameraPos.y,m_cameraPos.z);
}

void Display::update(){
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;

    m_thisTime = SDL_GetTicks();
    m_deltaTime = (float)(m_thisTime - m_lastTime) / 1000;
    m_lastTime = m_thisTime;

    doMovements();

    while(SDL_PollEvent(&e)){
        if ( e.type == SDL_QUIT) {
            n_isClosed = true;
        } else if(e.type == SDL_KEYDOWN){
            m_firstKey = false;
            m_keys[e.key.keysym.sym] = true;
        } else if(e.type == SDL_KEYUP){
            m_keys[e.key.keysym.sym] = false;
        } else if( e.type == SDL_MOUSEBUTTONDOWN){
            m_firstX =  e.button.x;
            m_firstY =  e.button.y;
        }
        else if( e.type == SDL_MOUSEBUTTONUP){
            m_lastX =  e.button.x;
            m_lastY =  e.button.y;

            if (m_firstMouse){
                m_lastX = m_firstX;
                m_lastY = m_firstY;
                m_firstMouse = false;
            }

            float xoffset = m_firstX - m_lastX;
            float yoffset = m_lastY - m_firstY;

            xoffset *= m_sensitivity;
            yoffset *= m_sensitivity;

            m_yaw   += xoffset;
            m_pitch += yoffset;

            if(m_pitch > 89.0f)
                m_pitch = 89.0f;
            if(m_pitch < -89.0f)
                m_pitch = -89.0f;

            glm::vec3 frnt;
            frnt.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            frnt.y = sin(glm::radians(m_pitch));
            frnt.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            m_cameraFront = glm::normalize(frnt);
        }
    }
}

bool Display::isClosed(){
    return n_isClosed;
}

void Display::Clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Display::getDeltaTime(){
    return m_deltaTime;
}

glm::vec3 Display::getCameraPosition(){
    return m_cameraPos;
}

glm::vec3 Display::getCameraFront(){
    return m_cameraFront;
}

glm::vec3 Display::getCameraUp(){
    return m_cameraUp;
}
