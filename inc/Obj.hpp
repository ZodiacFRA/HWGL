#ifndef OBJ_HPP
#define OBJ_HPP

#include "commonHWGL.hpp"
#include "vboindexer.hpp"
#include "Shader.hpp"


class Obj {
public:
	Obj(std::string name);
	virtual ~Obj ();

	int loadObj(std::string filepath);
	int draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	// SETTERS - GETTERS
	void setShader(Shader *shader) { _shader = shader; }
	glm::mat4 getModelMatrix() { return _modelMatrix; }

private:
	std::string _name;
	glm::mat4 _modelMatrix;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;

	std::vector<unsigned short> _indices;
	std::vector<glm::vec3> _indexed_vertices;
	std::vector<glm::vec2> _indexed_uvs;
	std::vector<glm::vec3> _indexed_normals;

	GLuint _verticesBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;
	GLuint _elementBuffer;

	Shader *_shader;

	int loadFromObjFile(FILE *file);
	int drawBuffer(GLuint buffer, int attribute, int size);
};

#endif
