#pragma once

#include <vector>

#include "Camera.h"
#include "LightRenderer.h"

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <btBulletDynamicsCommon.h>

class MeshRenderer {

public:
	MeshRenderer(MeshType modelType, std::string _name, Camera* _camera, btRigidBody* _rigidBody);
	~MeshRenderer();

	void draw();

	void setPosition(glm::vec3 _position);
	void setScale(glm::vec3 _scale);
	void setProgram(GLuint _program);
	void setTexture(GLuint _textureID);

	btRigidBody* rigidBody;
	std::string name = "";

private:
	std::vector<Vertex>vertices;
	std::vector<GLuint>indices;
	glm::mat4 modelMatrix;

	Camera* camera;

	glm::vec3 position, scale;
	GLuint vao, vbo, ebo, texture, program;
	
};

