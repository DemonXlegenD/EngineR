#include"Texture.h"

Texture::Texture(const char* _path, const char* _texType, unsigned int _slot, const std::string _directory)
{
	// Assigns the type texture of the texture object
	type = _texType;
	path = _path;

	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + _slot);
	unit = _slot;

	TextureFromFile(_path, _directory);
}

void Texture::TextureFromFile(const char* _path, const std::string& _directory) {
	std::string filename = _directory + "/" + std::string(_path);

	glGenTextures(1, &ID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	stbi_set_flip_vertically_on_load(true);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		std::cerr << "Échec du chargement de la texture : " << filename << std::endl;
		stbi_image_free(data);
	}
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
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}