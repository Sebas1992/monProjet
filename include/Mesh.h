#ifndef MESH_H
#define MESH_H

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<vector>

class Sommet{
    public:
        Sommet(const glm::vec3 pos, const glm::vec2 texCoord){
            this->_position = pos;
            this->_texCoord = texCoord;
        }
        glm::vec3 get_position(){return _position;}
        glm::vec2 get_texCoord(){return _texCoord;}
    private:
        glm::vec3 _position;
        glm::vec2 _texCoord;
};

class Mesh
{
    public:
        Mesh(Sommet* sommets, unsigned int nb_sommets);
        ~Mesh();
        void draw();

    private:
        GLuint VAO, VBO, EBO;
};

#endif // MESH_H
