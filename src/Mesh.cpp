#include "Mesh.h"

Mesh::Mesh(Sommet* sommets, unsigned int nb_sommets){

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    for(unsigned int i=0; i<nb_sommets; i++){
        positions.push_back(sommets[i].get_position());
        texCoords.push_back(sommets[i].get_texCoord());
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, nb_sommets * sizeof(sommets[0]), &sommets[0], GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nb_indices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(texCoords[0]) + sizeof(positions[0]), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(texCoords[0]) + sizeof(positions[0]), (GLvoid*)(3*sizeof(GLfloat)));

    glBindVertexArray(0);
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw(){
    glBindVertexArray(VAO);

    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
