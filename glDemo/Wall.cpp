#include "Wall.h"
#include "Map.h"

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
    for (const auto& loc : location) 
	{
		m_worldMatrix = glm::translate(mat4(1.0), loc);
        m_worldMatrix = glm::scale(m_worldMatrix,glm::vec3(0.5, 2.0, 0.5));
		ExampleGO::PreRender();
		ExampleGO::Render();
    }
}

void Wall::Init(Scene* _scene)
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
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