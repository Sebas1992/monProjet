#include <iostream>
#include<GL/glew.h>
#include<SDL2/SDL.h>
#include"Shaders.h"
#include"Mesh.h"
#include"Texture.h"
#include"affichage.h"
#include"Transform.h"
#include"Camera.h"

#define LARGEUR 800
#define HAUTEUR 600

int main()
{
    Affichage* fenetre = new Affichage();

    if(glewInit() != GLEW_OK){
        std::cerr << "Erreur lors de l'initialisation de glew" << std::endl;
    }

    glViewport(0, 0, LARGEUR, HAUTEUR);

    SDL_Event evenement;

    Shader shader("./Shaders/vertex.vs", "./Shaders/fragment.frag");

    Sommet sommets[] = {
        Sommet(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),

        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f)),

        Sommet(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),

        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),

        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
        Sommet(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),

        Sommet(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)),
        Sommet(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
        Sommet(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
    };

    Transform transformation;
    Mesh mesh(sommets, 36);
    Texture texture("./Images/bricks.jpg");
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 70.0f, (float)LARGEUR/(float)HAUTEUR, 0.1f, 100.0f);

    bool fermer = false;

    float compteur = 0.0f;

    while(!fermer){
        SDL_PollEvent(&evenement);
        switch(evenement.type){
            case SDL_KEYDOWN:
                switch(evenement.key.keysym.sym){
                    case SDLK_ESCAPE:
                        fermer= true;
                        break;
                    case SDLK_w:
                        camera.deplacer(SDLK_w);
                        break;
                    case SDLK_s:
                        camera.deplacer(SDLK_s);
                        break;
                    case SDLK_a:
                        camera.deplacer(SDLK_a);
                        break;
                    case SDLK_d:
                        camera.deplacer(SDLK_d);
                        break;
                }
        }

        shader.Use();
        shader.update(transformation, camera);

        fenetre->clear_window();

        mesh.draw();
        texture.lier(0);

        fenetre->swap_fenetre();
        compteur += 0.05f;
    }

    delete fenetre;
    SDL_Quit();
    return 0;
}
