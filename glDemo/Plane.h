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

	vector<GLfloat> PlaneGen(int div, float width);
	vector<GLuint> PlaneIndex(int div);
	vector<GLfloat> line(vec3 start, vec3 end, int div);
	vector<GLfloat>planeVertices(vec3 v0, vec3 v1, vec3 v2, vec3 v3, int div);
	void Render();
private:
	int div;
	GLuint m_planeIndex;
	vector<GLuint> v_planeIndex;
};