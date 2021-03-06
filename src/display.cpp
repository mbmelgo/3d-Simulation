#include "display.h"

Display::Display(int width, int height, const string& title, const string& path){
    m_speedValue = 2.0;
    m_angleXZValue = 0.0;
    m_angleXYValue = 0.0;
    m_massValue = 10.0;

    m_speedTimes = 1.0;
    m_angleTimes = 0.0;
    m_massTimes = 1.0;

    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);

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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("MIXER FAILED TO INITIALIZED!");
    }
    string name = path + "/res/sounds/glass.wav";
    const char *mycharp = name.c_str();
    m_glassMusic = Mix_LoadWAV(mycharp);

    if (m_glassMusic == NULL){
            printf("GLASS MUSIC NOT FOUND");
    }

    name = path + "/res/sounds/gun.wav";
    const char *mycharp2 = name.c_str();
    m_gunMusic = Mix_LoadWAV(mycharp2);

    if (m_gunMusic == NULL){
            printf("GUN MUSIC NOT FOUND");
    }

    n_isClosed = false;

    glEnable(GL_DEPTH_TEST);

//    glCullFace(GL_BACK);
//    glEnable(GL_CULL_FACE);


}

Display::~Display(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_GL_DeleteContext(m_window);
    SDL_Quit();
}

void Display::doMovements(){
    glm::vec3 cameraPosPrev = glm::vec3(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

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
    if(m_cameraPos.y<=1.0){
        m_cameraPos.y = 1.0;
    }
    if(m_cameraPos.y>=9.3){
        m_cameraPos.y = 9.3;
    }
    if(m_cameraPos.x>=45.0){
        m_cameraPos.x = 45.0;
    }
    if(m_cameraPos.x<=-45.0){
        m_cameraPos.x = -45.0;
    }
    if(m_cameraPos.z>=45.0){
        m_cameraPos.z = 45.0;
    }
    if(m_cameraPos.z<=-45.0){
        m_cameraPos.z = -45.0;
    }

    if(m_cameraPos.z <= 22.9 && m_cameraPos.z >= -22.8 && m_cameraPos.x <= 21 && m_cameraPos.x >= 19){
        m_cameraPos.x = cameraPosPrev.x;
        m_cameraPos.z = cameraPosPrev.z;
    }

//    printf("%f,%f,%f\n",m_cameraPos.x,m_cameraPos.y,m_cameraPos.z);
}

bool Display::isStart(){
    return m_start;
}

void Display::startActions(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if ( e.type == SDL_QUIT) {
            n_isClosed = true;
        } else if(e.type == SDL_KEYDOWN){
            m_firstKey = false;
            if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_d){
                m_keys[e.key.keysym.sym] = true;
            }
        } else if(e.type == SDL_KEYUP){
            if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_d){
                m_keys[e.key.keysym.sym] = false;
            }
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

void Display::menuActions(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if ( e.type == SDL_QUIT) {
            n_isClosed = true;
        } else if(e.type == SDL_KEYDOWN ){
            switch (e.key.keysym.sym){
                case SDLK_SPACE:
                    m_start = true;
                    Mix_PlayChannel(-1,m_gunMusic,0);
                    break;
                case SDLK_q:
                    m_changedSpeed = true;
                    m_speedTimes = m_speedTimes + 0.25;
                    if(m_speedTimes>1.75) m_speedTimes = 1.75;
                    m_speedValue = 2.0 * m_speedTimes;
                    break;
                case SDLK_a:
                    m_changedSpeed = true;
                    m_speedTimes = m_speedTimes - 0.25;
                    if(m_speedTimes<1) m_speedTimes = 1.0;
                    m_speedValue = 2.0 * m_speedTimes;
                    break;
                case SDLK_e:
                    m_changedAngle = true;
                    m_angleTimes = m_angleTimes + 1.0;
                    if(m_angleTimes>9) m_angleTimes = 9.0;
                    m_angleXYValue = 0.0 + (10 * m_angleTimes);
                    break;
                case SDLK_d:
                    m_changedAngle = true;
                    m_angleTimes = m_angleTimes - 1.0;
                    if(m_angleTimes<0) m_angleTimes = 0.0;
                    m_angleXYValue = 0.0 + (10 * m_angleTimes);
                    break;
                case SDLK_w:
                    m_changedMass = true;
                    m_massTimes = m_massTimes + 0.25;
                    if(m_massTimes>1.75) m_massTimes = 1.75;
                    m_massValue = 10.0 * m_massTimes;
                    break;
                case SDLK_s:
                    m_changedMass = true;
                    m_massTimes = m_massTimes - 0.25;
                    if(m_massTimes<1) m_massTimes = 1.0;
                    m_massValue = 10.0 * m_massTimes;
                    break;
            }
        }

    }
}

void Display::update(){
    SDL_GL_SwapWindow(m_window);

    m_thisTime = SDL_GetTicks();
    m_deltaTime = (float)(m_thisTime - m_lastTime) / 1000;
    m_lastTime = m_thisTime;

    doMovements();

    if(m_start){
        startActions();
    } else {
        menuActions();
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
