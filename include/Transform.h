#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SDL2/SDL.h>

class Transform
{
    public:
        Transform(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& rot = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)){
            _position = pos;
            _rotation = rot;
            _scale = scale;
        }

        ~Transform(){}

        glm::mat4 modelMatrix() const{
            glm::mat4 transform;
            transform = glm::translate(transform, _position);
            transform = glm::rotate(transform, SDL_GetTicks() * 0.0025f, _rotation);
            transform = glm::scale(transform, _scale);

            return transform;
        }

        // Accesseurs
        glm::vec3& get_position(){return _position;}
        glm::vec3& get_rotation(){return _rotation;}
        glm::vec3& get_scale(){return _scale;}

        // Mutateurs
        void set_position(glm::vec3 position){_position = position;}
        void set_rotation(glm::vec3 rotation){_rotation = rotation;}
        void set_scale(glm::vec3 scale){_scale = scale;}

    private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;
};

#endif // TRANSFORM_H
