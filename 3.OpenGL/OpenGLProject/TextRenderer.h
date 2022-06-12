#pragma once

#include <iostream>
#include <string>
#include <map>

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#define CHARACTERS_TO_LOAD 128

struct Character {
	GLuint		TextureID;	// Texture ID of each glyph texture
	glm::ivec2	Size;		// glyph Size
	glm::ivec2	Bearing;	// baseline to left/top of glyph
	GLuint		Advance;	// id to next glyph
};

class TextRenderer {

public:
	TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint program);
	~TextRenderer();

	void draw();
	void setPosition(glm::vec2 _position);
	void setText(std::string _text);

private:
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	std::map<GLchar, Character> Characters;
};

