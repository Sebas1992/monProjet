#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<SDL2/SDL.h>

class Camera
{
    public:
        Camera(glm::vec3 pos, float fov, float aspectRatio, float zNear, float zFar){
            _perspective = glm::perspective(fov, aspectRatio, zNear, zFar);
            _position = pos;
            _cible = glm::vec3(0.0, 0.0f, 0.0f);
            _direction = glm::normalize(_position - _cible);
            _haut = glm::vec3(0.0f, 1.0f, 0.0f);
            _cameraDroite = glm::normalize(glm::cross(_haut, _direction));
            _cameraHaut= glm::cross(_direction, _cameraDroite);
            _cameraAvant = glm::vec3(0.0f, 0.0f, -1.0f);
        }
        ~Camera(){
        }

        glm::mat4 viewMatrix(){
            //_position = glm::vec3(_position);
            return glm::lookAt(_position, _position + _cameraAvant, _haut);
        }

        glm::mat4 ProjectionMatrix() const{
            return _perspective;
        }

        void deplacer(SDL_Keycode key){
            if(key == SDLK_w){
                _position -= _vitesseCamera * _position;
            }
            else if(key == SDLK_s){
                _position += _vitesseCamera * _position;
            }
            else if(key == SDLK_a){
                _position -= glm::normalize(glm::cross(_cameraAvant, _cameraHaut)) * _vitesseCamera;
            }
            else if(key == SDLK_d){
                _position += glm::normalize(glm::cross(_cameraAvant, _cameraHaut)) * _vitesseCamera;
            }
        }

    private:
        GLfloat _vitesseCamera = 0.05f;
        glm::mat4 _view;
        glm::mat4 _perspective;
        glm::vec3 _position;
        glm::vec3 _cible;
        glm::vec3 _direction;
        glm::vec3 _haut;
        glm::vec3 _cameraDroite;
        glm::vec3 _cameraHaut;
        glm::vec3 _cameraAvant;
        GLfloat _angle = 1;
        bool touches[1024];
};

#endif // CAMERA_H
