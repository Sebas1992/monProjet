#ifndef _SHADER_H
#define _SHADER_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
#include"Transform.h"
#include"Camera.h"

using namespace std;

class Shader
{
public:
	//Program ID
	GLuint program;
	//Lit et construit le shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void update(const Transform& transf, Camera& camera);
	//Utilise le programme
	void Use();
};
#endif
