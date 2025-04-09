#include "Shader.h"

namespace Engine {
	// Reads a text file and outputs a string with everything in the text file
	std::string GetFileContents(const char* _filename) {
		std::ifstream in(_filename, std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw(errno);
	}


	Shader::Shader() {
	}

	// Activates the Shader Program
	void Shader::Load(const char* _vertexFile, const char* _fragmentFile) {
		// Read vertexFile and fragmentFile and store the strings
		std::string vertex_code = GetFileContents(_vertexFile);
		std::string fragment_code = GetFileContents(_fragmentFile);

		// Convert the shader source strings into character arrays
		const char* vertex_source = vertex_code.c_str();
		const char* fragment_source = fragment_code.c_str();

		// Create Vertex Shader Object and get its reference
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		//Attach Vertex Shader source to the Vertex Shader Object
		glShaderSource(vertex_shader, 1, &vertex_source, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(vertex_shader);
		CompileErrors(vertex_shader, "VERTEX");

		// Create Fragment Shader Object and get its reference
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach Fragment Shader source to the Fragment Shader Object
		glShaderSource(fragment_shader, 1, &fragment_source, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(fragment_shader);
		CompileErrors(fragment_shader, "FRAGMENT");

		// Create Shader Program Object and get its reference
		ID = glCreateProgram();
		// Attach the Vertex and Fragment Shaders to the Shader Program
		glAttachShader(ID, vertex_shader);
		glAttachShader(ID, fragment_shader);
		// Wrap-up/Link all the shaders together into the Shader Program
		glLinkProgram(ID);
		CompileErrors(ID, "PROGRAM");

		// Delete the now useless Vertex and Fragment Shader objects
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	void Shader::Activate() {
		glUseProgram(ID);
	}

	// Deletes the Shader Program
	void Shader::Unload() {
		glDeleteProgram(ID);
	}

	void Shader::CompileErrors(unsigned int _shader, const char* _type)
	{
		GLint has_compiled;
		char info_log[1024];

		if (_type != "PROGRAM") {
			glGetShaderiv(_shader, GL_COMPILE_STATUS, &has_compiled);

			if (has_compiled == GL_FALSE) {
				glGetShaderInfoLog(_shader, 1024, NULL, info_log);
				std::cout << "SHADER_COMPILATION_ERROR for : " << _type << "\n" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(_shader, GL_COMPILE_STATUS, &has_compiled);

			if (has_compiled == GL_FALSE) {
				glGetProgramInfoLog(_shader, 1024, NULL, info_log);
				std::cout << "SHADER_LINKING_ERROR for : " << _type << "\n" << std::endl;
			}
		}
	}

}