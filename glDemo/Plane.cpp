#include "Plane.h"
#include "stringHelp.h"
using namespace std;
using namespace glm;

std::vector<float> procedArray;

std::vector<GLuint> procIndexArray;

Plane::Plane()
{
	m_type = "PLANE";
	m_numFaces = 0;
	m_vao = 0;
	div = 0.0f;
	width = 0.0f;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

Plane::~Plane()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);

}

void Plane::PlaneGen(int div, float width)
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	float nx = 0.0f; // Normal in X direction
	float ny = -1.0f; // Normal in Y direction (pointing upward)
	float nz = 0.0f; // Normal in Z direction

	for (int i = 0; i <= width; i++)
	{
		
		for (int j = 0; j <= div; j++)
			{
				procedArray.push_back(x);
				procedArray.push_back(y);
				procedArray.push_back(z);
				procedArray.push_back(w);

				procedArray.push_back(nx);
				procedArray.push_back(ny);
				procedArray.push_back(nz);
				x += 0.05f;
			}
		z += 0.05;
		x = 0.0f;
	}
	
}

void Plane::PlaneIndex(int div)
{

	for (int row = 0; row < width; row++)
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

void Plane::Load(ifstream& _file)
{
	Model::Load(_file);
	StringHelp::Float(_file, "DIV", div);
	StringHelp::Float(_file, "WIDTH", width);
	PlaneGen(div, width);
	PlaneIndex(div);
	m_numFaces = div * width * 2;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, procedArray.size() * sizeof(float), procedArray.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)0); // Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(4 * sizeof(float))); // Normal
	glEnableVertexAttribArray(1);

	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, procIndexArray.size() * sizeof(GLuint), procIndexArray.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
