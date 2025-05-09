#pragma once
#include "core.h"
#include "Model.h"

using namespace std;
using namespace glm;
class Plane : public Model
{
public:
	Plane();
	virtual ~Plane();

	void PlaneGen(int div, float width);
	void PlaneIndex(int div);
	
	
	void Render();
	void Load(ifstream& _file);

private:
	
	GLuint	m_numFaces = 0;
	GLuint	m_vao = 0;

	float div;
	float width;
	GLuint				m_vertexBuffer;
	GLuint				m_indexBuffer;
	GLuint				m_texture;

	vector<GLfloat> procedArray;
	vector<GLuint> procIndexArray;
};