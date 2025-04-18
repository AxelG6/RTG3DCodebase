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
	1.0f, -1.0f, -1.0f, 1.0f,//bottom back right 23
};

std::vector<float> procedArray;
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

std::vector<GLuint> procIndexArray;

Plane::Plane()
{
	
	div = 2;
	width = 2;
	m_numFaces = div*width * 2;
	PlaneGen(div, width);
	PlaneIndex(div);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, procedArray.size() * sizeof(float), procedArray.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	 //setup vbo for colour attribute
	glGenBuffers(1, &m_colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, procedArray.size() * sizeof(float), colourArray, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, procIndexArray.size() * sizeof(GLuint), procIndexArray.data(), GL_STATIC_DRAW);

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

void Plane::PlaneGen(int div, float width)
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	for (int i = 0; i <= width; i++)
	{
		
		for (int j = 0; j <= div; j++)
			{
				procedArray.push_back(x);
				procedArray.push_back(y);
				procedArray.push_back(z);
				procedArray.push_back(w);
				x += 1.0f;
			}
		z += 1.0;
		x = 0.0f;
	}
	
}

void Plane::PlaneIndex(int div)
{

	for (int row = 0; row < div; row++)
	{
		for (int col = 0; col < div; col++)
		{
			int index = row * (div + 1) + col;
			procIndexArray.push_back(index + (div + 1));//2
			procIndexArray.push_back(index + 1);//1
			procIndexArray.push_back(index);//0
			
			procIndexArray.push_back(index + 1);
			procIndexArray.push_back(index + (div + 1));
			procIndexArray.push_back(index + (div + 1) + 1);//3
			
			
		}
	}
}

void Plane::Render() {

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numFaces * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}


