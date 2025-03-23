#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string GetFileContents(const char* _filename){
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


Shader::Shader(const char* _vertexFile, const char* _fragmentFile) {
	// Read vertexFile and fragmentFile and store the strings
	std::string vertex_code = GetFileContents(_vertexFile);
	std::string fragment_code = GetFileContents(_fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertex_source = vertex_code.c_str();
	const char* fragment_source = fragment_code.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertex_source, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragment_source, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() {
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete() {
	glDeleteProgram(ID);
}