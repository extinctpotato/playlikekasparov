#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "models/all.h"
#include "misc.h"
#include "shaderprogram.h"

ShaderProgram *s1;

GLuint lwood;
GLuint dwood;

float aspectRatio = 1;

glm::vec3 cameraPos   = glm::vec3(3.5f, 3.5f, -10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
bool grabbed = false;
float yaw   = 450.0f;	// yaw of 0.0 results in a direction vector pointing to the right
float pitch =  -12.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::ifstream bsn;
std::vector<std::string> board(8);
int games;

std::map<std::string, int> keyValueModel;

void next_move() {
	for (int i = 0; i < 8; i++) {
		bsn >> board[i];
	}
	if(bsn.eof()) {
		printf("The game has concluded.\n");
	}
}


/// INPUT & MISC CALLBACKS ///
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (!grabbed) return;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
	if (action==GLFW_PRESS) {
		if (key==GLFW_KEY_G) {
			if (!grabbed) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				firstMouse = true;
			} else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			grabbed = !grabbed;
		}
		if (key==GLFW_KEY_N) {
			next_move();
		}
	}
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 3.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
	if (height==0) return;
	aspectRatio=(float)width/(float)height;
	glViewport(0,0,width,height);
}

/// END OF INPUT & MISC CALLBACKS ///

void generateVAO() {
	int models = sizeof(figures) / sizeof(Guacamole);

	for (int i = 0; i < models; i++) {
		unsigned int vao, vbo[3];

		Guacamole f = figures[i];

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(3, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, f.vertsSize, f.verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, f.normalsSize, f.normals, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, f.texCoordsSize, f.texCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		figures[i].vao = vao;
		std::string l(1, figures[i].letter);
		keyValueModel[l] = i;
		printf("Generated VAO: %d\n", figures[i].vao);
	}
}

void init(GLFWwindow* window) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetKeyCallback(window,keyCallback);

	s1 = new ShaderProgram("shaders/v_simplest.glsl", NULL, "shaders/f_simplest.glsl");

	dwood = readTexture("textures/dwood.png");
	lwood = readTexture("textures/lwood.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lwood);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dwood);

	generateVAO();

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void death(GLFWwindow* window) {
	asm("nop");
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float angle_x=0; 
	float angle_y=0;

	glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 P=glm::perspective(glm::radians(fov), aspectRatio, 0.01f, 50.0f);

	s1->use();

	glUniformMatrix4fv(s1->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(s1->u("V"),1,false,glm::value_ptr(V));



	s1->use();

	bool fieldTex = 1;
	for (int i = 0; i < 8; i++) {
		float fieldCounter = 0.0f;
		for (char const &c: board[i]) {
			glBindVertexArray(figures[6].vao);
			glUniform1i(s1->u("textureMap0"), fieldTex);

			glm::vec3 pos = glm::vec3(fieldCounter, 0.0f, i);
			glm::mat4 M = glm::mat4(1.0f);
			M = glm::translate(M, pos);
			float angle = 0;
			M = glm::rotate(M, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(s1->u("M"),1,false,glm::value_ptr(M));
			glDrawArrays(GL_TRIANGLES, 0, figures[6].vertexCount);

			if (c != '.') {
				std::string piece(1, tolower(c));
				int figureId = keyValueModel[piece];
				int figureTex = 1;
				float figureAngle = 180.0f;

				if (c >= 'A' && c <= 'Z') {
					figureTex = 0;
					figureAngle = 0.0f;
				}

				glm::mat4 M2 = glm::mat4(1.0f);
				M2 = glm::translate(M2, pos);
				M2 = glm::rotate(M2, glm::radians(figureAngle), glm::vec3(0.0f, 1.0f, 0.0f));
				M2 = glm::rotate(M2, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				glUniformMatrix4fv(s1->u("M"),1,false,glm::value_ptr(M2));
				
				glBindVertexArray(figures[figureId].vao);
				glUniform1i(s1->u("textureMap0"), figureTex);
				glDrawArrays(GL_TRIANGLES, 0, figures[figureId].vertexCount);
			}

			fieldTex = !fieldTex;
			fieldCounter += 1.0f;
		}
		fieldTex = !fieldTex;
	}



	glfwSwapBuffers(window);
}

int main(int argc, char** argv) {
	setenv("MESA_GL_VERSION_OVERRIDE", "3.3", 1);
	bsn.open(argv[1]);

	bsn >> games;

	printf("%d board states ahead of us...\n", games);

	next_move();

	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glEnable(GL_MULTISAMPLE);  

	window = glfwCreateWindow(800, 800, "playlikekasparov", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to initialize the window!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW!\n");
		exit(EXIT_FAILURE);
	}

	init(window);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		drawScene(window);
		glfwPollEvents();
	}


}
