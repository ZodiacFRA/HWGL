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
	int draw();

	std::string _name;
private:

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

	int loadFromObjFile(FILE *file);
	int drawBuffer(GLuint buffer, int attribute, int size);
};

#endif
