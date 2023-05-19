#include <iostream>
#include <filesystem>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

const GLint w = 600, h = 800;
const GLchar* vss = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fss = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
"}\n\0";
int TestWindow()
{
	std::srand(std::time(nullptr));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(w, h, "Learn OpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (window == nullptr)
	{
		std::cout << "Failed GLFW" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_FALSE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, sw, sh);
	GLclampf(*randf)() = []()->GLclampf
	{
		return (float)std::rand() / RAND_MAX;
	};
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetTime() > 3)
		{
			glClearColor(randf(), randf(), randf(), 1.0f);
			glfwSetTime(0);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	return EXIT_SUCCESS;
}
int TestDrawShape()
{
	std::srand(std::time(nullptr));

	GLclampf(*randf)() = []() -> GLclampf
	{
		return (GLfloat)(rand() % 2 == 0 ? 1.0f : -1.0f) * ((GLclampf)rand() / RAND_MAX);
	};

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);

	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (window == nullptr)
	{
		std::cout << "GLFW failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, sw, sh);


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Shader(vertex) failed : " << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Shader(fragment) failed : " << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "Linking failed : " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLfloat vertices[] =
	{
		randf(),randf(),randf(),
		randf(),randf(),randf(),
		randf(),randf(),randf()
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLclampf bg[] = { randf(),randf(),randf(),1.0f };
	GLclampf fg[] = { randf(),randf(),randf(),1.0f };
	bool pressing = false;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		int current = glfwGetKey(window, GLFW_KEY_SPACE);
		if (current == GLFW_PRESS && !pressing)
		{

			GLfloat vertices[] =
			{
				randf(),randf(),randf(),
				randf(),randf(),randf(),
				randf(),randf(),randf()
			};

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			pressing = true;
		}
		else if (current == GLFW_RELEASE)
		{
			pressing = false;
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(shaderProgram);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}
int TestDrawShape(const char* v, const char* f)
{
	std::srand(std::time(nullptr));

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLfloat(*randf)() = []() -> GLfloat
	{
		return (GLfloat)(rand() % 2 == 0 ? 1.0f : -1.0f) * ((GLclampf)rand() / RAND_MAX);
	};

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);

	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (window == nullptr)
	{
		std::cout << "GLFW failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, sw, sh);

	Shader shader(v, f);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Shader(vertex) failed : " << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Shader(fragment) failed : " << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "Linking failed : " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLfloat vertices[] =
	{
		randf(),randf(),randf(), 1.0f, 0.0f, 0.0f,
		randf(),randf(),randf(), 0.0f, 1.0f, 0.0f,
		randf(),randf(),randf(), 0.0f, 0.0f, 1.0f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	GLclampf bg[] = { randf(),randf(),randf(),1.0f };
	GLclampf fg[] = { randf(),randf(),randf(),1.0f };
	bool pressing = false;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		int current = glfwGetKey(window, GLFW_KEY_SPACE);
		if (current == GLFW_PRESS && !pressing)
		{

			GLfloat vertices[] =
			{
				randf(),randf(),randf(), 1.0f, 0.0f, 0.0f,
				randf(),randf(),randf(), 0.0f, 1.0f, 0.0f,
				randf(),randf(),randf(), 0.0f, 0.0f, 1.0f
			};

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			pressing = true;
		}
		else if (current == GLFW_RELEASE)
		{
			pressing = false;
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		shader.Use();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}
int TestDrawShape(const char* vs, const char* fs, GLfloat* v)
{
	std::srand(std::time(nullptr));

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLfloat(*randf)() = []() -> GLfloat
	{
		return (GLfloat)(rand() % 2 == 0 ? 1.0f : -1.0f) * ((GLclampf)rand() / RAND_MAX);
	};

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);

	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (window == nullptr)
	{
		std::cout << "GLFW failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, sw, sh);

	Shader shader(vs, fs);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Shader(vertex) failed : " << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Shader(fragment) failed : " << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "Linking failed : " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	GLclampf bg[] = { randf(),randf(),randf(),1.0f };
	GLclampf fg[] = { randf(),randf(),randf(),1.0f };
	bool pressing = false;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}
int main()
{
	std::string cp = std::filesystem::current_path().string();
	std::replace(cp.begin(), cp.end(), '\\', '/');
	cp = cp + "/";
	std::string v = cp + "core.vs", f = cp + "core.frag";
	GLfloat vert[] = 
	{
		0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f
	};
	int i = TestDrawShape(v.c_str(), f.c_str()/*, vert */ );
	std::cout << i << std::endl;
}