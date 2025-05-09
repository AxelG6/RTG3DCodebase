#include "Wall.h"
#include "stringHelp.h"
#include "AIModel.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"

const int labyrinth[5][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}
};
std::vector<vec3> location;

Wall::Wall()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (labyrinth[i][j] == 1)
            {
                m_pos = glm::vec3(i * 1.0f, 0.0f, j * 1.0f); // Adjust position based on the labyrinth
                location.push_back(m_pos);
            }
        }
    }
}

void Wall::Load(ifstream& _file)
{
    ExampleGO::Load(_file);
}

void Wall::Render()
{       
    for (const auto& loc : location) {
		m_worldMatrix = glm::translate(mat4(1.0), loc);
        m_worldMatrix = glm::scale(m_worldMatrix,glm::vec3(0.5, 0.5, 0.5));
        ExampleGO::PreRender();
		ExampleGO::Render();
    }
}

void Wall::Init(Scene* _scene)
{
    ExampleGO::Init(_scene);
}