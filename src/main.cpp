#include <iostream>
#include<GL/glew.h>
#include<SDL2/SDL.h>
#include"Shaders.h"
#include"Mesh.h"
#include"Texture.h"
#include"affichage.h"
#include"Transform.h"
#include"Camera.h"
#include<string>

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
    const Uint8* etat = SDL_GetKeyboardState(NULL);

    float compteur = 0.0f;

    SDL_WarpMouseInWindow(fenetre->get_fenetre(), LARGEUR/2, HAUTEUR/2);
    SDL_SetWindowGrab(fenetre->get_fenetre(), SDL_TRUE);
    SDL_ShowCursor(0);

    while(!fermer){
        GLfloat currentFrame = (GLfloat)SDL_GetTicks()/1000.0f;
        camera.set_deltaTime(currentFrame);
        camera.set_lastFrame(currentFrame);

        while(SDL_PollEvent(&evenement)){
            if(evenement.type == SDL_MOUSEMOTION){
                camera.deplacerSouris(evenement.motion.x, evenement.motion.y);
            }
        }
        if(evenement.type == SDL_KEYDOWN){
            if(evenement.key.keysym.sym == SDLK_ESCAPE){
                fermer = true;
            }else
                camera.deplacer(etat);
            }else{
                camera.deplacer(etat);
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
