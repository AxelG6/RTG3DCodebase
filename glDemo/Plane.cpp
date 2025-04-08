#include "Plane.h"

using namespace std;
using namespace glm;


static float positionArray[] = {

	//top
	-1.0f, 1.0f, 1.0f, 1.0f, //top, front, left, 0
	-1.0f, 1.0f, -1.0f, 1.0f, //top, back, left, 1
	1.0f, 1.0f, -1.0f, 1.0f, //top, back, right 2
	1.0f, 1.0f, 1.0f, 1.0f, //top front right 3

	//bottom
	-1.0f, -1.0f, 1.0f, 1.0f, //bottom front left 4
	-1.0f, -1.0f, -1.0f, 1.0f,//bottom back left 5
	1.0f, -1.0f, -1.0f, 1.0f, //bottom back right 6
	1.0f, -1.0f, 1.0f, 1.0f, //bottom front right 7

	//right
	1.0f, 1.0f, -1.0f, 1.0f, //top, back, right 8
	1.0f, 1.0f, 1.0f, 1.0f, //top front right 9
	1.0f, -1.0f, -1.0f, 1.0f, //bottom back right 10
	1.0f, -1.0f, 1.0f, 1.0f, //bottom front right 11

	//left
	-1.0f, 1.0f, 1.0f, 1.0f, //top, front, left, 12
	-1.0f, 1.0f, -1.0f, 1.0f, //top, back, left, 13
	-1.0f, -1.0f, 1.0f, 1.0f, //bottom front left 14
	-1.0f, -1.0f, -1.0f, 1.0f,//bottom back left 15

	//front
	-1.0f, 1.0f, 1.0f, 1.0f, //top, front, left, 16
	1.0f, 1.0f, 1.0f, 1.0f, //top front right 17
	-1.0f, -1.0f, 1.0f, 1.0f, //bottom front left 18
	1.0f, -1.0f, 1.0f, 1.0f, //bottom front right 19

	//back
	-1.0f, 1.0f, -1.0f, 1.0f, //top, back, left, 20
	1.0f, 1.0f, -1.0f, 1.0f, //top, back, right 21
	-1.0f, -1.0f, -1.0f, 1.0f,//bottom back left 22
	1.0f, -1.0f, -1.0f, 1.0f //bottom back right 23

};

// Packed colour buffer for principle axes model
static float colourArray[] = {

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f
};


// Line list topology to render principle axes
static unsigned int indexArray[] = {

	// Top face
	2, 1, 0,
	3, 2, 0,

	// Bottom face
	5, 6, 4,
	6, 7, 4,

	// Right face
	8, 9, 11,
	10, 8, 11,

	// Left face
	12, 13, 15,
	14, 12, 15,

	// Front face
	17, 16, 18,
	19, 17, 18,


	// Back face
	20, 21, 22,
	21, 23, 22
};

Plane::Plane()
{
	PlaneGen(10, 10);

	m_numFaces = 6 * 2;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray), positionArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup vbo for colour attribute
	glGenBuffers(1, &m_colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionArray), colourArray, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Plane::~Plane()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_colourBuffer);
	glDeleteBuffers(1, &m_indexBuffer);

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

	glBindVertexArray(m_planeIndex);
	glDrawElements(GL_LINES, v_planeIndex.size() * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}

vector<GLfloat>Plane::lines(vec3 start, vec3 end, int div)
{
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

		vector<GLfloat> rowVertices =  lines(start, end, div);

		plane.insert(plane.end(),rowVertices.begin(),rowVertices.end());
		
	}
	return plane;
}