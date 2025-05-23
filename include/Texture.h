#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>

#include"Shader.h"

namespace Engine {
	class Texture
	{
	public:
		unsigned int ID;
		const char* type;
		GLuint unit;
		std::string path;

		Texture(const char* _path, const char* _texType, unsigned int _slot, const std::string _directory);

		void TextureFromFile(const char* _path, const std::string& _directory);

		// Assigns a texture unit to a texture
		void TexUnit(Shader& _shader, const char* _uniform, GLuint _unit);
		// Binds a texture
		void Bind();
		// Unbinds a texture
		void Unbind();
		// Deletes a texture
		void Delete();
	};

}
#endif