#include "Texture.h"

Texture::Texture(const std::string& chemin_fichier)
{
    int hauteur, largeur, nbComposants;
    unsigned char* donneeImage = stbi_load(chemin_fichier.c_str(), &largeur, &hauteur, &nbComposants, 4);

    if(donneeImage == NULL){
        std::cerr << "Erreur lors du telechargement de la texture" << std::endl;
        std::cerr << stbi_failure_reason();
    }

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largeur, hauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, donneeImage);

    stbi_image_free(donneeImage);
    glBindTexture(1, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}

void Texture::lier(unsigned int unit){
    assert(unit>=0 && unit <=31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, _texture);
}
