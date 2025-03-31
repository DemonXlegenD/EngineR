#include"Texture.h"

Texture::Texture(const char* _image, GLenum _texType, GLuint _slot, GLenum _format, GLenum _pixelType)
{
	// Assigns the type of the texture ot the texture object
	type = _texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(_image, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) {
		std::cerr << "Erreur : Impossible de charger l'image !" << std::endl;
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + _slot);
	unit = _slot;
	glBindTexture(_texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(_texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(_texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object

	glTexImage2D(_texType, 0, GL_RGBA, widthImg, heightImg, 0, _format, _pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(_texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(_texType, 0);
}

void Texture::TexUnit(Shader& _shader, const char* _uniform, GLuint _unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(_shader.ID, _uniform);
	// Shader needs to be activated before changing the value of a uniform
	_shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, _unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}