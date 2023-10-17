#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector3D.h"
#include "Shader.h"
#include "Mesh.h"

#define Dev

const GLint w = 800, h = 800;
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
	shader.Compile();
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
	std::cout << sizeof(vertices) << std::endl;
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

int TestDrawShape(const char* v, const char* f, std::vector<GLclampf> vert)
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

	Shader shader(GL_TRUE ,v, f);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vert.size(), &vert.front(), GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	GLclampf bg[] = { randf(),randf(),randf(),1.0f };
	GLclampf fg[] = { randf(),randf(),randf(),1.0f };
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

int DrawMesh(Shader *shader, Mesh *mesh, GLclampf bg[4])
{


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, sw, sh);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	shader->Compile();

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);

	std::vector<float> data = mesh->GetData();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);

	std::vector<unsigned int> indices = mesh->GetIndices();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, indices.size());
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

int DrawTriangles(Shader* shader, GLclampf bg[4])
{
	float(*randf)() = []()->float
	{
		int lastDigits = rand() % 1000;
		return std::stof("0." + std::to_string(lastDigits));
	};

	Mesh* mesh = new Mesh();

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, sw, sh);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	shader->Compile();

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	std::vector<float> data = mesh->GetData();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);

	std::vector<unsigned int> indices = mesh->GetIndices();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	int lastEvent = GLFW_RELEASE;

	while (!glfwWindowShouldClose(window))
	{
		int currentEvent = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
		if (lastEvent != currentEvent && currentEvent == GLFW_PRESS) 
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			

			xpos = (xpos - sw / 2) / sw * 2;
			ypos = (-ypos + sh / 2) / sh * 2;



			Vertex* vertex = new Vertex(Vector3D(xpos, ypos, 0), Vector3D(randf(), randf(), randf()));
			mesh->AddVertex(vertex, true);

			std::cout << vertex->Position().X() << " " << vertex->Position().Y() << " " << vertex->Position().Z() << std::endl;

			data = mesh->GetData();
			indices = mesh->GetIndices();


			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		}
		lastEvent = currentEvent;
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, indices.size());
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

#ifdef Dev
int DrawPolygon(Shader* shader, GLclampf bg[4])
{
	std::vector<float> data;
	std::vector<unsigned int> indices;
	std::vector<Vector3D> pos;

	float(*randf)() = []()->float
	{
		int lastDigits = rand() % 1000;
		return std::stof("0." + std::to_string(lastDigits));
	};

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, sw, sh);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	shader->Compile();

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	auto IsConvex = [&](Vector3D p, Vector3D c, Vector3D n)->bool
	{
		return (c.X() - p.X()) * (n.Y() - p.Y()) - (n.X() - p.X()) * (c.Y() - p.Y()) >= 0;
	};
	auto IsInside = [&](Vector3D a, Vector3D b, Vector3D c, Vector3D p)->bool
	{
		double detT = (double)(b.X() - a.X()) * (double)(c.Y() - a.Y()) - (double)(c.X() - a.X()) * (double)(b.Y() - a.Y());
		double alpha = ((c.Y() - a.Y()) * (p.X() - a.X()) - (c.X() - a.X()) * (p.Y() - a.Y())) / detT;
		double beta = ((a.Y() - b.Y()) * (p.X() - a.X()) - (a.X() - b.X()) * (p.Y() - a.Y())) / detT;
		double gamma = 1.0 - alpha - beta;
		return alpha >= 0 && beta >= 0 && gamma >= 0;
	};
	auto IsEar = [&](std::vector<Vector3D> polygon, int i) -> bool
	{

		int s = polygon.size();
		if (s < i || s < 3)return false;
		Vector3D p = polygon[(i - 1 + s) % s];
		Vector3D c = polygon[i];
		Vector3D n = polygon[(i + 1) % s];

		if (!IsConvex(p, c, n)) 
		{
			for (int j = 0; j < s; j++) 
			{
				if (j != (i - 1 + s) % s && j != i && j != (i + 1) % s) 
				{
					if (IsInside(p, c, n, polygon[j])) 
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	};
	auto Triangulate = [&](std::vector<Vector3D> polygon) -> std::vector<unsigned int>
	{
		int n = polygon.size();
		std::vector<unsigned int> triangles;
		std::vector<unsigned int> remaining;
		for (int i = 0; i < n; i++)
		{
			remaining.push_back(i);
		}
		while (n > 2)
		{
			for (int i = 0; i < n; i++)
			{
				if (IsEar(polygon, i))
				{
					triangles.push_back((i - 1 + n) % n);
					triangles.push_back(i);
					triangles.push_back((i + 1) % n);
					remaining.erase(remaining.begin() + i);
					n--;
					break;
				}
			}
		}
		return triangles;
	};
	int lastEvent = GLFW_RELEASE;

	while (!glfwWindowShouldClose(window))
	{
		int currentEvent = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
		if (lastEvent != currentEvent && currentEvent == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			xpos = (xpos - sw / 2) / sw * 2;
			ypos = (-ypos + sh / 2) / sh * 2;
			Vertex* vertex = new Vertex(Vector3D(xpos, ypos, 0), Vector3D(randf(), randf(), randf()));
			for (float f : vertex->GetData()) data.push_back(f);
			if (indices.size() >= 3)
			{
				indices.push_back(indices.size() - 1);
			}
			else 
			{
				indices.push_back(indices.size());
			}
			for (unsigned int i : indices) std::cout << i << " ";
			std::cout << std::endl;

			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		}
		lastEvent = currentEvent;
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		if (pos.size() > 1)
		{
			glBegin(GL_LINE);
			for (int i = 0; i < pos.size() - 1; i++)
			{
				glVertex2f(pos[i].X(), pos[i].Y());
				glVertex2f(pos[i + 1].X(), pos[i + 1].Y());
			}
			glVertex2f(pos.front().X(), pos.front().Y());
			glVertex2f(pos.back().X(), pos.back().Y());
			glEnd();
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, indices.size());
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}
int DrawLineLoop(Shader* shader, GLclampf bg[4]) 
{
	Vertex *last = nullptr;
	std::vector<Vertex*> vertices;

	float(*randf)() = []()->float
	{
		int lastDigits = rand() % 1000;
		return std::stof("0." + std::to_string(lastDigits));
	};

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, sw, sh);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	shader->Compile();

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	auto IsConvex = [&](Vector3D p, Vector3D c, Vector3D n)->bool
	{
		return (c.X() - p.X()) * (n.Y() - p.Y()) - (n.X() - p.X()) * (c.Y() - p.Y()) >= 0;
	};
	auto IsInside = [&](Vector3D a, Vector3D b, Vector3D c, Vector3D p)->bool
	{
		double detT = (double)(b.X() - a.X()) * (double)(c.Y() - a.Y()) - (double)(c.X() - a.X()) * (double)(b.Y() - a.Y());
		double alpha = ((c.Y() - a.Y()) * (p.X() - a.X()) - (c.X() - a.X()) * (p.Y() - a.Y())) / detT;
		double beta = ((a.Y() - b.Y()) * (p.X() - a.X()) - (a.X() - b.X()) * (p.Y() - a.Y())) / detT;
		double gamma = 1.0 - alpha - beta;
		return alpha >= 0 && beta >= 0 && gamma >= 0;
	};
	auto IsEar = [&](std::vector<Vector3D> polygon, int i) -> bool
	{

		int s = polygon.size();
		if (s < i || s < 3)return false;
		Vector3D p = polygon[(i - 1 + s) % s];
		Vector3D c = polygon[i];
		Vector3D n = polygon[(i + 1) % s];

		if (!IsConvex(p, c, n))
		{
			for (int j = 0; j < s; j++)
			{
				if (j != (i - 1 + s) % s && j != i && j != (i + 1) % s)
				{
					if (IsInside(p, c, n, polygon[j]))
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	};
	auto Triangulate = [&](std::vector<Vector3D> polygon) -> std::vector<unsigned int>
	{
		int n = polygon.size();
		std::vector<unsigned int> triangles;
		std::vector<unsigned int> remaining;
		for (int i = 0; i < n; i++)
		{
			remaining.push_back(i);
		}
		while (n > 2)
		{
			for (int i = 0; i < n; i++)
			{
				if (IsEar(polygon, i))
				{
					triangles.push_back((i - 1 + n) % n);
					triangles.push_back(i);
					triangles.push_back((i + 1) % n);
					remaining.erase(remaining.begin() + i);
					n--;
					break;
				}
			}
		}
		return triangles;
	};
	int lastEvent = GLFW_RELEASE;

	while (!glfwWindowShouldClose(window))
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		xpos = (xpos - sw / 2) / sw * 2;
		ypos = (-ypos + sh / 2) / sh * 2;
		int currentEvent = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
		if (lastEvent != currentEvent && currentEvent == GLFW_PRESS)
		{
			Vertex* vertex = new Vertex(Vector3D(xpos, ypos, 0), Vector3D(randf(), randf(), randf()));
			if(last == nullptr)
			{
				Vector3D pos = Vector3D(xpos, ypos, 0.0f);
				Vector3D col = Vector3D(randf(),randf(),randf());
				last = new Vertex(pos, col);
			}
			else
			{
				vertices.push_back(last);
				last = nullptr;
			}
		}
		std::vector<float> data;
		if(!vertices.empty()) for (Vertex* vertex : vertices) for (float f : vertex->GetData()) data.push_back(f);
		std::vector<unsigned int> indices;
		for (int i = 0; i < vertices.size(); i++) indices.push_back(i);
		if(last)
		{
			Vector3D pos = Vector3D(xpos, ypos, 0.0f);
			last = new Vertex(pos, last->Color());
			for (float f : last->GetData()) data.push_back(f);
			indices.push_back(indices.size());
		}
		lastEvent = currentEvent;
		if (!data.empty()) 
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		}
		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, indices.size());
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}
int DrawLines(Shader* shader, GLclampf bg[4])
{
	Vertex* last = nullptr;
	std::vector<Vertex*> vertices;

	float(*randf)() = []()->float
	{
		int lastDigits = rand() % 1000;
		return std::stof("0." + std::to_string(lastDigits));
	};

	Vector3D col = Vector3D(randf(), randf(), randf());

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", nullptr, nullptr);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, sw, sh);

	if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW failed." << std::endl;
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	shader->Compile();

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	auto IsConvex = [&](Vector3D p, Vector3D c, Vector3D n)->bool
	{
		return (c.X() - p.X()) * (n.Y() - p.Y()) - (n.X() - p.X()) * (c.Y() - p.Y()) >= 0;
	};
	auto IsInside = [&](Vector3D a, Vector3D b, Vector3D c, Vector3D p)->bool
	{
		double detT = (double)(b.X() - a.X()) * (double)(c.Y() - a.Y()) - (double)(c.X() - a.X()) * (double)(b.Y() - a.Y());
		double alpha = ((c.Y() - a.Y()) * (p.X() - a.X()) - (c.X() - a.X()) * (p.Y() - a.Y())) / detT;
		double beta = ((a.Y() - b.Y()) * (p.X() - a.X()) - (a.X() - b.X()) * (p.Y() - a.Y())) / detT;
		double gamma = 1.0 - alpha - beta;
		return alpha >= 0 && beta >= 0 && gamma >= 0;
	};
	auto IsEar = [&](std::vector<Vector3D> polygon, int i) -> bool
	{

		int s = polygon.size();
		if (s < i || s < 3)return false;
		Vector3D p = polygon[(i - 1 + s) % s];
		Vector3D c = polygon[i];
		Vector3D n = polygon[(i + 1) % s];

		if (!IsConvex(p, c, n))
		{
			for (int j = 0; j < s; j++)
			{
				if (j != (i - 1 + s) % s && j != i && j != (i + 1) % s)
				{
					if (IsInside(p, c, n, polygon[j]))
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	};
	auto Triangulate = [&](std::vector<Vector3D> polygon) -> std::vector<unsigned int>
	{
		int n = polygon.size();
		std::vector<unsigned int> triangles;
		std::vector<unsigned int> remaining;
		for (int i = 0; i < n; i++)
		{
			remaining.push_back(i);
		}
		while (n > 2)
		{
			for (int i = 0; i < n; i++)
			{
				if (IsEar(polygon, i))
				{
					triangles.push_back((i - 1 + n) % n);
					triangles.push_back(i);
					triangles.push_back((i + 1) % n);
					remaining.erase(remaining.begin() + i);
					n--;
					break;
				}
			}
		}
		return triangles;
	};
	int lastEvent = GLFW_RELEASE;

	while (!glfwWindowShouldClose(window))
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		xpos = (xpos - sw / 2) / sw * 2;
		ypos = (-ypos + sh / 2) / sh * 2;
		last = new Vertex(Vector3D(xpos, ypos, 0), col);


		int currentEvent = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
		if (lastEvent != currentEvent && currentEvent == GLFW_PRESS)
		{
			if(vertices.size() > 1)vertices.push_back(vertices.back());
			vertices.push_back(last);
			col = Vector3D(randf(), randf(), randf());
		}



		std::vector<float> data;
		if (!vertices.empty()) for (Vertex* vertex : vertices) for (float f : vertex->GetData()) data.push_back(f);
		std::vector<unsigned int> indices;
		for (int i = 0; i < vertices.size(); i++)
		{
			indices.push_back(i);
		}
		if(vertices.size())
		{
			for (float f : vertices.back()->GetData()) data.push_back(f);
			for (float f : last->GetData()) data.push_back(f);
			indices.push_back(indices.size());
			indices.push_back(indices.size());
		}


		lastEvent = currentEvent;



		if (!data.empty() && !indices.empty())
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		}


		glfwPollEvents();
		glClearColor(bg[0], bg[1], bg[2], bg[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, indices.size());
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}
#endif
int main()
{
	
	std::string cp = std::filesystem::current_path().string();
	std::replace(cp.begin(), cp.end(), '\\', '/');
	cp = cp + "/";
	std::string v = cp + "core.vs", f = cp + "core.frag";
	Shader* shader = new Shader(v.c_str(), f.c_str());
	float bg[4] = { 0,0,0,0 };
	DrawLines(shader, bg);

}