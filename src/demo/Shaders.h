//#define GLFW_INCLUDE_GLCOREARB
//#define GLFW_INCLUDE_GL3
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

class Shaders {
	std::vector<GLuint> _shaderList;
	std::vector<std::string> _vertexShaderText;
	std::vector<std::string> _fragmentShaderText;
	GLuint compile( GLenum eShaderType, const std::string &strShaderFile );
	GLuint link();
public:
	Shaders();
	~Shaders();
	void addToVertexList( std::string shaderFile );
	void addToFragmentList( std::string shaderFile );
	GLuint build();
};
