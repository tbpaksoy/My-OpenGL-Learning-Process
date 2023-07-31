#include "GL/glew.h"
class Shader
{
private:
	GLuint program;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Use();
};