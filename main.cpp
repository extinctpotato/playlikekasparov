#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"
#include "models/all.h"

float aspectRatio = 1;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
	if (height==0) return;
	aspectRatio=(float)width/(float)height;
	glViewport(0,0,width,height);
}

void init(GLFWwindow* window) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	//glfwSetKeyCallback(window,keyCallback);
}

void death(GLFWwindow* window) {
	asm("nop");
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);
}

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(600, 600, "playlikekasparov", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to initialize the window!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW!");
		exit(EXIT_FAILURE);
	}

	init(window);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window)) {
		drawScene(window);
		glfwSetTime(0);
		glfwPollEvents();
	}


}
