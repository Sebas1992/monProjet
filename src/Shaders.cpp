#include "Shaders.h"




Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//	==========================================
	//	1.Retrouve le code source au chemin donnée
	//  ==========================================
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		//Ouvre les fichiers
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		//Lit le contenu
		stringstream vshaderStream, fShaderStream;
		vshaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//Ferme les fichiers
		vShaderFile.close();
		fShaderFile.close();
		//Convertit le flux en tableau GLchar
		vertexCode = vshaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	//	=====================
	//	2.Compile les shaders
	//	=====================
	GLuint vertex, fragment;
	GLint succes;
	GLchar infoLog[512];
	//VertexShader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//Test si le vertex shader s'est bien compiler
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIED" << infoLog << endl;
	}
	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//Test si le fragment shader s'est bien compiler
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIED" << infoLog << endl;
	}
	//ShaderProgram
	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(program);
	// Vérifie les erreurs a la liaison du programme
	glGetProgramiv(this->program, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//on détruit les shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader()
{
}

void Shader::Use() {
	glUseProgram(this->program);
}

void Shader::update(const Transform& transf, Camera& camera){
    glm::mat4 model = transf.modelMatrix();
    glm::mat4 view = camera.viewMatrix();
    glm::mat4 projection = camera.ProjectionMatrix();

    GLuint modelLocation = glGetUniformLocation(this->program, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    GLuint viewLocation = glGetUniformLocation(this->program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLocation = glGetUniformLocation(this->program, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
