#pragma once

#include <vector>

#include "Camera.h"
#include "LightRenderer.h"

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class MeshRenderer {

public:
	MeshRenderer(MeshType modelType, Camera* _camera);
	~MeshRenderer();

	void draw();

	void setPosition(glm::vec3 _position);
	void setScale(glm::vec3 _scale);
	void setProgram(GLuint _program);
	void setTexture(GLuint _textureID);

private:
	std::vector<Vertex>vertices;
	std::vector<GLuint>indices;
	glm::mat4 modelMatrix;

	Camera* camera;

	glm::vec3 position, scale;
	Gluint vao, vbo, ebo, texture, program;
};

