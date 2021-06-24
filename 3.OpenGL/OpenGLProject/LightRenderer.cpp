#include "LightRenderer.h"

LightRenderer::LightRenderer(MeshType meshType, Camera* camera) {
	this->camera = camera;

	switch (meshType) {

	case kTriangle: 
		Mesh::setTriData(vertices, indices);
		break;
	case kQuad:
		Mesh::setQuadData(vertices, indices);
		break;
	case kCube:
		Mesh::setCubeData(vertices, indices);
		break;
	case kSphere:
		Mesh::setSphereData(vertices, indices);
		break;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Vertex Attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
}