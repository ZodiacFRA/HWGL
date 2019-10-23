#include "Obj.hpp"


Obj::~Obj()
{
	// Clear VBO
	glDeleteBuffers(1, &_verticesBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteBuffers(1, &_elementBuffer);
}


int Obj::draw()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _verticesBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		_indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	return SUCCESS;
}
