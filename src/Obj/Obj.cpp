#include "Obj.hpp"


Obj::Obj(std::string name)
	: _name(name)
{}

Obj::~Obj()
{
	// Clear VBOs
	glDeleteBuffers(1, &_verticesBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteBuffers(1, &_elementBuffer);
	// Shaders are destroyed by App
}


int Obj::draw()
{
	drawBuffer(_verticesBuffer, 0, 3);
	drawBuffer(_uvBuffer, 1, 2);
	drawBuffer(_normalBuffer, 2, 3);
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	// Draw the triangles
	glDrawElements(
		GL_TRIANGLES,       // mode
		_indices.size(),    // count
		GL_UNSIGNED_SHORT,  // type
		(void*)0            // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	return SUCCESS;
}


int Obj::drawBuffer(GLuint buffer, int attribute, int size)
{
	glEnableVertexAttribArray(attribute);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(
		attribute,          // attribute
		size,               // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	return SUCCESS;
}
