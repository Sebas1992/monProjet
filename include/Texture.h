#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>
#include<GL/glew.h>
#include"stb_image.h"
#include<cassert>
#include<iostream>
#include<vector>

class Texture
{
    public:
        Texture(const std::string& chemin_fichier);
        ~Texture();
        void lier(unsigned int unit);

    private:
        GLuint _texture;
};

#endif // TEXTURE_H
