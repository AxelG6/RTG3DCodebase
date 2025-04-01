#include "Plane.h"

using namespace std;
using namespace glm;

Plane::Plane()
{
	PlaneGen(10, 10);
	glGenVertexArrays(1, &m_planeIndex);
}

Plane::~Plane()
{

}

vector<GLfloat> Plane::PlaneGen(int div, float width)
{

	vector<GLfloat> plane;

	float triangleSide = width / div;
	for (int row = 0; row < div + 1; row++)
	{
		for (int col = 0; col < div + 1; col++)
		{
			vec3 crntVec = vec3(col * triangleSide, 0.0, row * -triangleSide);
			plane.push_back(crntVec.x);
			plane.push_back(crntVec.y);
			plane.push_back(crntVec.z);
		}
	}
	return plane;
}

vector<GLuint> Plane::PlaneIndex(int div)
{

	for (int row = 0; row < div; row++)
	{
		for (int col = 0; col < div; col++)
		{
			int index = row * (div + 1) + col;
			v_planeIndex.push_back(index);
			v_planeIndex.push_back(index + (div + 1) + 1);
			v_planeIndex.push_back(index + (div + 1));

			v_planeIndex.push_back(index);
			v_planeIndex.push_back(index + 1);
			v_planeIndex.push_back(index + (div + 1) + 1);
		}
	}
	return v_planeIndex;
}

void Plane::Render() {
	vector<GLuint>planeIndex = PlaneIndex(10);
	glBindVertexArray(m_planeIndex);
	glDrawElements(GL_TRIANGLES, v_planeIndex.size() * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}

vector<GLfloat>Plane::line(vec3 start, vec3 end, int div)
{
	vector<GLfloat> line;
	vec3 diff = end - start;
	vec3 step = vec3(diff.x / div, diff.y / div, diff.z / div);
	for (int i = 0; i < div + 1; i++)
	{
		vec3 crntVec = start + (step.x * i, step.y * i, step.z * i);
		line.push_back(crntVec.x);
		line.push_back(crntVec.y);
		line.push_back(crntVec.z);
	}
	return line;
}

vector<GLfloat>Plane::planeVertices(vec3 v0, vec3 v1, vec3 v2, vec3 v3, int div)
{
	vector<GLfloat> plane;
	vec3 vec03 = vec3 ((v3 - v0).x / div, (v3 - v0).y / div, (v3 - v0).z / div);
	vec3 vec12 = vec3 ((v2 - v1).x / div, (v2 - v1).y / div, (v2 - v1).z / div);

	for (int row = 0; row < div + 1; row++)
	{
		vec3 start = v0 + vec3((vec03.x * row), (vec03.y * row), (vec03.z * row));
		vec3 end = v1 + vec3((vec12.x * row), (vec12.y * row), (vec12.z * row));
		plane.push_back(line(start,end,div));
		
	}
}