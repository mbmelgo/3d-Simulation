#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>


using namespace std;


class Display
{
    public:
        Display(int width, int height, const string& title, const string& path);
        virtual ~Display();

        void update();
        bool isClosed();
        void Clear(float r, float g, float b, float a);
        float getDeltaTime();
        glm::vec3 getCameraPosition();
        glm::vec3 getCameraFront();
        glm::vec3 getCameraUp();
        bool isStart();

        void setSpeedValue(float value){m_speedValue=value;}
        void setAngleXYValue(float value){m_angleXYValue=value;}
        void setAngleXZValue(float value){m_angleXZValue=value;}
        void setMassValue(float value){m_massValue=value;}

        float getSpeedValue(){return m_speedValue;}
        float getAngleXYValue(){return m_angleXYValue;}
        float getAngleXZValue(){return m_angleXZValue;}
        float getMassValue(){return m_massValue;}

        float getSpeedTimes(){return m_speedTimes;}
        float getAngleTimes(){return m_angleTimes;}
        float getMassTimes(){return m_massTimes;}

        void setCamerPosition(glm::vec3 position){m_cameraPos = position;}

        void playGlassBreak(){Mix_PlayChannel(-1,m_glassMusic,0);};

        void setChangedSpeed(bool changed){m_changedSpeed = changed;}
        bool isChangedSpeed(){return m_changedSpeed;}
        void setChangedAngle(bool changed){m_changedAngle = changed;}
        bool isChangedAngle(){return m_changedAngle;}
        void setChangedMass(bool changed){m_changedMass = changed;}
        bool isChangedMass(){return m_changedMass;}

    protected:

    private:
        Display(const Display& other){};
        Display& operator=(const Display& other){};

        void doMovements();
        void startActions();
        void menuActions();

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool n_isClosed;
        float m_deltaTime = 0.0;
        float m_thisTime = 0.0;
        float m_lastTime = 0.0;
        float m_cameraSpeed = 10.0f;
        glm::vec3 m_cameraPos   = glm::vec3(0.0f, 5.0f, 20.0f);
        glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
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
        bool m_start = false;
        bool m_changedSpeed = false;
        bool m_changedAngle = false;
        bool m_changedMass = false;


        float m_speedValue;
        float m_angleXZValue;
        float m_angleXYValue;
        float m_massValue;

        float m_speedTimes;
        float m_angleTimes;
        float m_massTimes;


        Mix_Chunk *m_gunMusic = NULL;
        Mix_Chunk *m_glassMusic = NULL;
};

#endif // DISPLAY_H
