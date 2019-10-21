#ifndef OBJ_HPP
#define OBJ_HPP

#include "commonHWGL.hpp"
#include "objloader.hpp"


class Obj {
public:
	int load(std::string filepath);
	virtual ~Obj ();

	int draw();
private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
	GLuint _verticesBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;

};

#endif
