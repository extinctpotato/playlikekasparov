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
#include "models/all.h"
#include "misc.h"
#include "shaderprogram.h"

const float PI = 3.141592653589793f;

ShaderProgram *s1;

GLuint lwood;
GLuint dwood;

float aspectRatio = 1;
unsigned int VAOtest, VBOtest;

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
	
	s1 = new ShaderProgram("shaders/v_simplest.glsl", NULL, "shaders/f_simplest.glsl");

	dwood = readTexture("textures/dwood.png");
	lwood = readTexture("textures/lwood.png");
}

void death(GLFWwindow* window) {
	asm("nop");
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertices = knightVerts;
	float* normals = knightNormals;
	float* texCoords = knightTexCoords;
	int vertexCount = knightNumVerts;

	float angle_x=0; 
	float angle_y=0;

	glm::mat4 V=glm::lookAt(
			glm::vec3(0, 0, -2.5),
			glm::vec3(0,0,0),
			glm::vec3(0.0f,1.0f,0.0f));

	glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

	glm::mat4 M=glm::mat4(1.0f);
	M=glm::rotate(M,angle_y,glm::vec3(1.0f,0.0f,0.0f)); //Wylicz macierz modelu
	M=glm::rotate(M,angle_x,glm::vec3(0.0f,1.0f,0.0f));

	s1->use();

	glUniformMatrix4fv(s1->u("P"),1,false,glm::value_ptr(P));
	glUniformMatrix4fv(s1->u("V"),1,false,glm::value_ptr(V));
	glUniformMatrix4fv(s1->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(s1->a("vertex"));
	glVertexAttribPointer(s1->a("vertex"),4,GL_FLOAT,false,0,vertices);

	glEnableVertexAttribArray(s1->a("normal"));
	glVertexAttribPointer(s1->a("normal"), 4, GL_FLOAT, false, 0, normals);

	glEnableVertexAttribArray(s1->a("texCoord0"));
	glVertexAttribPointer(s1->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

	glUniform1i(s1->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lwood);

	glDrawArrays(GL_TRIANGLES,0,vertexCount); 

	glDisableVertexAttribArray(s1->a("vertex"));
	glDisableVertexAttribArray(s1->a("normal"));  
	glDisableVertexAttribArray(s1->a("texCoord0"));

	glfwSwapBuffers(window);
}

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!");
		exit(EXIT_FAILURE);
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.30);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.30);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
		glfwSetTime(0);
		drawScene(window);
		glfwPollEvents();
	}


}
