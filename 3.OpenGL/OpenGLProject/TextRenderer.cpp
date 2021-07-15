#include "TextRenderer.h"

TextRenderer::TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint program) {
	
	this->text = text;
	this->color = color;
	this->scale = 1.0;
	this->program = program;
	this->setPosition(position);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	FT_Library ft;

	// Initialise FreeType
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	// Load font
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face)) {
		std::cout << "ERROR::FREESTYLE: Failed to load font" << std::endl;
	}

	// Set size
	FT_Set_Pixel_Sizes(face, 0, size);

	// Disable byte-aligment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte i = 0; i < CHARACTERS_TO_LOAD; i++) {

		// Load character glyph
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std:endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture filtering options

		// Store character in character map
	}
}