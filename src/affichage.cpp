#include "affichage.h"

Affichage::Affichage()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    _fenetre = SDL_CreateWindow("Scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, SDL_WINDOW_OPENGL);

    _contexte = SDL_GL_CreateContext(_fenetre);

    glEnable(GL_DEPTH_TEST);
}

Affichage::~Affichage()
{
    SDL_GL_DeleteContext(_contexte);
}

void Affichage::clear_window(){
    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Affichage::swap_fenetre(){
    SDL_GL_SwapWindow(_fenetre);
}
