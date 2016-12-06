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
            return glm::lookAt(_position, _position + _cameraAvant, _cameraHaut);
        }

        glm::mat4 ProjectionMatrix() const{
            return _perspective;
        }

        void deplacer(const Uint8*& key){
            GLfloat _vitesseCamera = 5.0f * _deltaTime;
            if(key[SDL_SCANCODE_W] == 1){
                _position -= _vitesseCamera * _position;
            }
            if(key[SDL_SCANCODE_S] == 1){
                _position += _vitesseCamera * _position;
            }
            if(key[SDL_SCANCODE_A] == 1){
                _position -= glm::normalize(glm::cross(_cameraAvant, _cameraHaut)) * _vitesseCamera;
            }
            if(key[SDL_SCANCODE_D] == 1){
                _position += glm::normalize(glm::cross(_cameraAvant, _cameraHaut)) * _vitesseCamera;
            }
                       // std::cout << "position: " << _position.x << ", " << _position.y << ", " << _position.z << std::endl;
        }

        void deplacerSouris(Sint32& posx, Sint32& posy){
            if(_premier){
                dernierePosx = posx;
                dernierePosy = posy;
                _premier = false;
            }

            GLfloat xoffset = posx - dernierePosx;
            GLfloat yoffset = dernierePosy - posy;

            dernierePosx = posx;
            dernierePosy = posy;

            GLfloat sensibilite = 0.05f;
            xoffset *= sensibilite;
            yoffset *= sensibilite;

            _yaw += xoffset;
            _pitch += yoffset;

            if(_pitch > 89.0f)
                _pitch = 89.0f;
            if(_pitch < -89.0f)
                _pitch = -89.0f;

            glm::vec3 avant;
            avant.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            avant.y = sin(glm::radians(_pitch));
            avant.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            _cameraAvant = glm::normalize(avant);
            std::cout << "CameraAvant: " << _cameraAvant.x << ", " << _cameraAvant.y << ", " << _cameraAvant.z << std::endl;
        }

        GLfloat get_deltaTime(){
            return _deltaTime;
        }
        GLfloat get_lastFrame(){
            return _lastFrame;
        }

        void set_deltaTime(GLfloat frameActuelle){
            _deltaTime = frameActuelle - _lastFrame;
        }

        void set_lastFrame(GLfloat frameActuelle){
            _lastFrame = frameActuelle;
        }

    private:
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
        GLfloat _deltaTime = 0.0f;
        GLfloat _lastFrame = 0.0f;
        bool _premier = true;
        GLfloat _yaw = -90.0f;
        GLfloat _pitch = 0.0f;

        GLfloat dernierePosx = 400.0f, dernierePosy = 300.0f;
};

#endif // CAMERA_H
