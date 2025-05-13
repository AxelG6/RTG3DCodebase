#include "Wall.h"
#include "ExampleGO.h"
#include "stringHelp.h"

const int WIDHT = 15;
const int labyrinth[WIDHT][WIDHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//2
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//3
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},//4
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},//5
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//6
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//7
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},//8
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//9
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//10
	{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},//11
	{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},//12
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//13
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//14
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}//15
  // 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
};

std::vector<vec3> location;

Wall::Wall()
{
	m_type = "WALL";
}

void Wall::Load(ifstream& _file)
{
    ExampleGO::Load(_file);
}

void Wall::Render()
{       
    for (const auto& loc : location) {
		m_worldMatrix = glm::translate(mat4(1.0), loc);
        m_worldMatrix = glm::scale(m_worldMatrix,glm::vec3(0.5, 2.0, 0.5));
        ExampleGO::PreRender();
		ExampleGO::Render();
    }
}

void Wall::Init(Scene* _scene)
{
    for (int i = 0; i < WIDHT; ++i)
    {
        for (int j = 0; j < WIDHT; ++j)
        {
            if (labyrinth[i][j] == 1)
            {
                m_pos = glm::vec3(i * 1.0f, 0.0f, j * 1.0f); // Adjust position based on the labyrinth
                location.push_back(m_pos);
            }
        }
    }
    ExampleGO::Init(_scene);
}