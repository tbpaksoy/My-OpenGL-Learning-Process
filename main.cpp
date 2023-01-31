#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint w = 600, h = 800;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(w,h,"Learn OpenGL",nullptr,nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if(window == nullptr)
	{
		std::cout << "Failed GLFW" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_FALSE;
	if(GLEW_OK != glewInit())
	{
		std::cout << "Failed GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, sw, sh);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetTime() > 1)
		{
			GLclampf(*randf)() = []()->GLclampf
			{
				return (float)std::rand() / RAND_MAX;
			};
			glClearColor(randf(), randf(), randf(), 1.0f);
			glfwSetTime(0);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	return EXIT_SUCCESS;
}