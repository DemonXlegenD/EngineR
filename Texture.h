#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>

#include"Shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLuint unit;

	Texture(const char* _image, GLenum _texType, GLuint _slot, GLenum _format, GLenum _pixelType);

	// Assigns a texture unit to a texture
	void TexUnit(Shader& _shader, const char* _uniform, GLuint _unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
#endif