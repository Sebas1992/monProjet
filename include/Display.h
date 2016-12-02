#ifndef DISPLAY_H
#define DISPLAY_H

#include<string>
#include<SDL2/SDL.h>

class Display
{
    public:
        Display(SDL_Window* window);
        ~Display();


    private:
        SDL_Window* _fenetre;
};

#endif // DISPLAY_H
