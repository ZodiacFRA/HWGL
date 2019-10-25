#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "commonHWGL.hpp"


class Texture {
public:
	~Texture();
	int setupDraw(GLuint programID);
	int loadTexture(const char *t_path, bool enableFiltering);

private:
	GLuint _texture;
};

#endif
