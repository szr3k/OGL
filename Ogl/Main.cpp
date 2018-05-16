#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//variables and data

unsigned int VBO;
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

std::string vs =	"#version 330 core \n\
					layout(location = 0) in vec3 aPos; \n\
					uniform float fRotate; \n\
					void main()\n\
					{ \n\
					vec2 uPosition = vec2(0.0,0.0); \n\
					uPosition.x = (cos(fRotate)*aPos.x)-(sin(fRotate)*aPos.y); \n\
					uPosition.y = (cos(fRotate)*aPos.y) + (sin(fRotate)*aPos.x); \n\
					gl_Position = vec4(uPosition.x , uPosition.y, aPos.z, 1.0); \n\
					}";
const char *c_str = vs.c_str();

std::string fs = "#version 330 core \n\
					out vec4 FragColor; \n\
					uniform float fPlusColorr; \n\
					uniform float fPlusColorg; \n\
					uniform float fPlusColorb; \n\
					void main()\n\
					{ \n\
					FragColor = vec4(0.0f , 0.0f, (fPlusColorb), 1);\n\
					}";
const char *f_str = fs.c_str();

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_FLOATING,1);

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// Generate Vertex Buffer Object

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create VerteX Shader

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &c_str, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

	//Create Fragment Shader

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &f_str, NULL);
	glCompileShader(fragmentShader);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create Shader Program

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Link Program + Shader

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint isLinked = 0;
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		
		// In this simple program, we'll just leave
	
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Activate Program

	glUseProgram(shaderProgram);

	//Point Attributes

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Create Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);

	// rotation

	float fRotate = 1;

	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float timevalue = glfwGetTime();
		float fPlusColorr = (sin(timevalue));
		float fPlusColorg = (sin(timevalue));
		float fPlusColorb = (sin(timevalue));
		glUniform1f(glGetUniformLocation(shaderProgram, "fRotate"), fRotate);
		glUniform1f(glGetUniformLocation(shaderProgram, "fPlusColorr"), fPlusColorr);
		glUniform1f(glGetUniformLocation(shaderProgram, "fPlusColorg"), fPlusColorg);
		glUniform1f(glGetUniformLocation(shaderProgram, "fPlusColorb"), fPlusColorb);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0, 0.0f, 1.0f);

		
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		fRotate += 0.001;
	
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}