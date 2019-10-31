#include "Texture.hpp"


int Texture::setupDraw(GLuint programID)
{
	// Texture handling
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, _texture);
	// Get a handle for our "myTextureSampler" uniform
	GLuint textureID  = glGetUniformLocation(programID, "myTextureSampler");
	glUniform1i(textureID, 0);
	return SUCCESS;
}


GLuint Texture::loadTexture(const char *t_path, bool enableFiltering)
{
	// If texture done with gimp:
	// export BMP as 24bits without colour space information
	printf("Loading image %s\n", t_path);

	// Informations from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// RGB data
	unsigned char *data;

	FILE * file = fopen(t_path,"rb");
	if (!file)
		return printError("Impossible to open file!");

	// Read the header, i.e. the 54 first bytes
	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file)!=54 ||
		// A BMP files always begins with "BM"
	   	(header[0]!='B' || header[1]!='M') ||
		// Make sure this is a 24bpp file
		*(int*)&(header[0x1E])!=0 || *(int*)&(header[0x1C])!=24) {
		printError("Not a correct BMP file (24 bits encoding needed)\n");
		fclose(file);
		return FAILURE;
	}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) // 3 : one byte for each Red, Green and Blue component
		imageSize=width*height*3;
	if (dataPos==0)  // The BMP header is done that way
		dataPos=54;

	// Create a buffer
	data = new unsigned char [imageSize];
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
	// Everything is in memory now, the file can be closed.
	fclose (file);
	// Create one OpenGL texture
	glGenTextures(1, &_texture);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _texture);
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	// OpenGL has now copied the data. Free our own version
	delete [] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (enableFiltering) {  // Trilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Requires mipmaps. Generate them automatically.
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	return _texture;
}


Texture::~Texture()
{
	glDeleteTextures(1, &_texture);
}
