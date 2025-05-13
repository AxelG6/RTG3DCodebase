#include "Vortex.h"
#include "Map.h"

std::vector<vec3> locationV;
Vortex::Vortex()
{
	m_type = "VORTEX";
	
}

void Vortex::Load(ifstream& _file)
{
	ExampleGO::Load(_file);
}
void Vortex::Render()
{
	for (const auto& loc : locationV)
	{
		m_worldMatrix = glm::translate(mat4(1.0), loc);
		m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(0.5, 2.0, 0.5));
		
		ExampleGO::PreRender();
		ExampleGO::Render();
	}
}
void Vortex::Init(Scene* _scene)
{

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (labyrinth[i][j] == 2)
			{
				m_pos = glm::vec3(i * 1.0f, 0.0f, j * 1.0f);
				locationV.push_back(m_pos);
			}
		}
	}
	ExampleGO::Init(_scene);
}
