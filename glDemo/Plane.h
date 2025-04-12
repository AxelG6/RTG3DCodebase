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

private:
	
	GLuint	m_numFaces = 0;
	GLuint	m_vao = 0;

	int div;

	GLuint				m_vertexBuffer;
	GLuint				m_colourBuffer;
	GLuint				m_indexBuffer;

	vector<GLfloat> procedArray;
	vector<GLuint> procIndexArray;
};