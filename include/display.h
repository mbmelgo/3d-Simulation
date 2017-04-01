#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;


class Display
{
    public:
        Display(int width, int height, const string& title);
        virtual ~Display();

        void update();
        bool isClosed();
        void Clear(float r, float g, float b, float a);
        float getDeltaTime();
        glm::vec3 getCameraPosition();
        glm::vec3 getCameraFront();
        glm::vec3 getCameraUp();

    protected:

    private:
        Display(const Display& other){};
        Display& operator=(const Display& other){};

        void doMovements();

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool n_isClosed;
        float m_deltaTime = 0.0;
        float m_thisTime = 0.0;
        float m_lastTime = 0.0;
        float m_cameraSpeed = 0.5f;
        glm::vec3 m_cameraPos   = glm::vec3(0.0f, 0.0f,  -5.0f);
        glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        bool m_keys[1024];
        float m_lastX;
        float m_lastY;
        float m_firstX;
        float m_firstY;
        float m_pitch = 0.0f;
        float m_yaw = -90.0f;;
        float m_sensitivity = 0.05;
        bool m_firstMouse = true;
        bool m_firstKey = true;
};

#endif // DISPLAY_H
