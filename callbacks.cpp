#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
	if (height==0) return;
	aspectRatio=(float)width/(float)height;
	glViewport(0,0,width,height);
}
