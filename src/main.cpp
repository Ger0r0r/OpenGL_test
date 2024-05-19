#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	printf("Vendor:			%s\n", glGetString(GL_VENDOR));
	printf("Renderer:		%s\n", glGetString(GL_RENDERER));
	printf("Version OpenGL:	%s\n", glGetString(GL_VERSION));
	printf("Version GLSL:	%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("../shaders/3.3.shader.vs", "../shaders/3.3.shader.fs"); // you can name your shader files however you like

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);  

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 0 red
		0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 1 red
		0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 3 red
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 0 red
		0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 3 red
		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	// 2 red

		
		0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	// 1 green
		0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	// 5 green
		0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	// 7 green
		0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	// 1 green
		0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	// 7 green
		0.5f,	0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	// 3 green
		
		-0.5f,	0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	// 2 blue
		0.5f,	0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	// 3 blue
		0.5f,	0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	// 7 blue
		-0.5f,	0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	// 2 blue
		0.5f,	0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	// 7 blue
		-0.5f,	0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	// 6 blue

		-0.5f,	-0.5f,	0.5f,	1.0f,	0.0f,	1.0f,	// 4 purple
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,	// 0 purple
		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,	// 2 purple
		-0.5f,	-0.5f,	0.5f,	1.0f,	0.0f,	1.0f,	// 4 purple
		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,	// 2 purple
		-0.5f,	0.5f,	0.5f,	1.0f,	0.0f,	1.0f,	// 6 purple

		0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 5 cyen
		-0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 4 cyen
		-0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 6 cyen
		0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 5 cyen
		-0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 6 cyen
		0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// 7 cyen
		
		-0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,	// 4 yellow
		0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,	// 5 yellow
		0.5f,	-0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,	// 1 yellow
		-0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,	// 4 yellow
		0.5f,	-0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,	// 1 yellow
		-0.5f,	-0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,	// 0 yellow
	};

	unsigned int indices[] = {  // note that we start from 0!
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
    };

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	float lastTime = glfwGetTime();
 	int nbFrames = 0;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat timeValue = glfwGetTime();
		GLuint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glm::mat4 mat_rotate = glm::mat4(1.0f);
		// mat_rotate = glm::rotate(mat_rotate, 45.0f, glm::vec3(1.0f,0.0f,1.0f));
		mat_rotate = glm::rotate(mat_rotate, timeValue, glm::vec3(-1.0f,-1.0f,-1.0f));
		// mat_rotate = glm::rotate(mat_rotate, timeValue, glm::vec3(1.0f,0.0f,0.0f));

		// render the triangle
		ourShader.use();

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat_rotate));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6*6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		nbFrames++;
		if (timeValue - lastTime >= 1.0 ) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%i\t%f ms\n", nbFrames, 1000.0/(float)nbFrames);
			nbFrames = 0;
			lastTime += 1.0;
		}
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}