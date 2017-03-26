#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <string>
#include <stdio.h>
#include <GL/glew.h>

using namespace std;


class Display
{
    public:
        Display(int width, int height, const string& title);
        virtual ~Display();

        void update();
        bool isClosed();
        void Clear(float r, float g, float b, float a);

    protected:

    private:
        Display(const Display& other){};
        Display& operator=(const Display& other){};

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool n_isClosed;
};

#endif // DISPLAY_H
