#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include<GL/glew.h>
#include<SDL2/SDL.h>


class Affichage
{
    public:
        Affichage();
        ~Affichage();
        void clear_window();
        void swap_fenetre();

    private:
        SDL_Window* _fenetre;
        SDL_GLContext _contexte;
        const int HAUTEUR = 600;
        const int LARGEUR = 800;
};

#endif // AFFICHAGE_H
