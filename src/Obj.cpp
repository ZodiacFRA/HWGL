#include "Obj.hpp"


Obj::~Obj()
{
	// Clear VBO
	glDeleteBuffers(1, &_verticesBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteBuffers(1, &_elementBuffer);
}


int Obj::loadObj(std::string filepath)
{
	if (!loadFromObjFile(filepath.c_str(), _vertices, _uvs, _normals))
		return FAILURE;

	indexVBO(_vertices, _uvs, _normals, _indices,
		_indexed_vertices, _indexed_uvs, _indexed_normals);

	// Load it into a VBO
	glGenBuffers(1, &_verticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		_indexed_vertices.size() * sizeof(glm::vec3),
		&_indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		_indexed_uvs.size() * sizeof(glm::vec2),
		&_indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		_indexed_normals.size() * sizeof(glm::vec3),
		&_indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_indices.size() * sizeof(unsigned short),
		&_indices[0] , GL_STATIC_DRAW);
	return SUCCESS;
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



int Obj::loadFromObjFile(
	const char * path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmp_vertices;
	std::vector<glm::vec2> tmp_uvs;
	std::vector<glm::vec3> tmp_normals;

	FILE * file = fopen(path, "r");
	if(!file)
		return printError("Impossible to open file!");

	while(42) {
		char lineID[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineID);
		if (res == EOF)
			break;

		if (!strcmp(lineID, "v")) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			tmp_vertices.push_back(vertex);
		} else if (!strcmp(lineID, "vt")) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			// Invert V coordinate since we will only use DDS textures
			// which are inverted. Remove if you want to use TGA or BMP loaders.
			// uv.y = -uv.y;
			tmp_uvs.push_back(uv);
		} else if (!strcmp(lineID, "vn")) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			tmp_normals.push_back(normal);
		} else if (!strcmp(lineID, "f")) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9) {
				printError("File can't be read by this parser. Try exporting with other options");
				fclose(file);
				return FAILURE;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		} else {  // Probably a comment, remove the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		// Get the attributes thanks to the index
		glm::vec3 vertex = tmp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = tmp_uvs[ uvIndex-1 ];
		glm::vec3 normal = tmp_normals[ normalIndex-1 ];
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	}

	fclose(file);
	return SUCCESS;
}
