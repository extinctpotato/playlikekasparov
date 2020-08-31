#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <lodepng.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint readTexture(const char *f) {
	fprintf(stdout, "Loading %s\n", f);
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	std::vector<unsigned char> image;
	unsigned w,h;
	unsigned err = lodepng::decode(image, w, h, f);

	if (err != 0) {
		std::cout << "Error " << err << ": " << lodepng_error_text(err) << std::endl;
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
