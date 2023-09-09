#include "GL/glew.h"
class Shader
{
private:
	GLuint program;
	GLchar* vertexPath;
	GLchar* fragmentPath;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(GLboolean compile, const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Use();
	void Compile();
};