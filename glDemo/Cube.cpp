#include "Cube.h"


using namespace std;
using namespace glm;


// Example data for cube model

// Packed vertex buffer for cube
static float positionArray[] = {

	//top
   -1.0f, 1.0f, 1.0f, 1.0f,    //top front left,0
   -1.0f, 1.0f, -1.0f, 1.0f,   //top back left,1
   1.0f, 1.0f, -1.0f, 1.0f,    //top back right,2
   1.0f, 1.0f, 1.0f, 1.0f,     //top front right,3

   //bottom
   -1.0f, -1.0f, 1.0f, 1.0f,    //bottom front left,4
   -1.0f, -1.0f, -1.0f, 1.0f,   //bottom back left,5
   1.0f, -1.0f, -1.0f, 1.0f,    //bottom back right,6
   1.0f, -1.0f, 1.0f, 1.0f,     //bottom front right,7

   //right
   1.0f, 1.0f, -1.0f, 1.0f,    //top front right,8
   1.0f, 1.0f, 1.0f, 1.0f,     //top back right,9
   1.0f, -1.0f, -1.0f, 1.0f,   //bottom front right,10
   1.0f, -1.0f, 1.0f, 1.0f,    //bottom back right,11

   //left
   -1.0f, 1.0f, 1.0f, 1.0f,    //top front left,12
   -1.0f, 1.0f, -1.0f, 1.0f,   //top back left,13
   -1.0f, -1.0f, 1.0f, 1.0f,   //bottom front left,14
   -1.0f, -1.0f, -1.0f, 1.0f,  //bottom back left,15

   //front
   -1.0f, 1.0f, 1.0f, 1.0f,    //top front left,16
   1.0f, 1.0f, 1.0f, 1.0f,        //top front right,17
   -1.0f, -1.0f, 1.0f, 1.0f,   //bottom front left,18
   1.0f, -1.0f, 1.0f, 1.0f,    //bottom front right,19

   //back
   -1.0f, 1.0f, -1.0f, 1.0f,    //top back left,20
   1.0f, 1.0f, -1.0f, 1.0f,     //top back right,21
   -1.0f, -1.0f, -1.0f, 1.0f,   //bottom back left,22
   1.0f, -1.0f, -1.0f, 1.0f,    //bottom back right,23
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

	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f
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
	11, 9, 8, 
	10, 11, 8,

	// Front face
	13, 14, 12,
	14, 15, 12,

	// Left face
	17, 18, 16,
	18, 19, 16,
	
	// Back face
	22, 21, 23,
	21, 20, 23
};



Cube::Cube() {

	m_numFaces = 6 * 2;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), positionArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup vbo for colour attribute
	glGenBuffers(1, &m_colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), colourArray, GL_STATIC_DRAW); 
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Cube::~Cube() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_colourBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}


void Cube::render() {
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numFaces * 3 , GL_UNSIGNED_INT, (const GLvoid*)0);
}
