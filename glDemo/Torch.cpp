#include "Torch.h"
#include "ExampleGO.h"
#include "stringHelp.h"
#include "PointLight.h"
#include "Map.h"
std::vector<vec3> location1;

Torch::Torch()
{
    m_type = "TORCH";

}

void Torch::Load(ifstream& _file)
{
    ExampleGO::Load(_file);

}

void Torch::Render()
{
    for (const auto& loc : location1) {
        m_worldMatrix = glm::translate(mat4(1.0), loc);
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(0.02, 0.02, 0.02));
		m_worldMatrix = glm::rotate(m_worldMatrix, 0.0f, vec3(90.0f, 0.0f, 0.0f));
        ExampleGO::PreRender();
        ExampleGO::Render();
    }
}

void Torch::Init(Scene* _scene)
{
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (labyrinth[i][j] == 3)
            {
                m_pos = glm::vec3(i * 1.0f, 0.0f, j * 1.0f); // Adjust position based on the labyrinth
                location1.push_back(m_pos);
				cout << "Torch position: " << m_pos.x << ", " << m_pos.y << ", " << m_pos.z << endl;
            }
        }
    }
    ExampleGO::Init(_scene);
}