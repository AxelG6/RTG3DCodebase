#include "Monster.h"
#include "Scene.h"
#include "stringHelp.h"
#include <random>

Monster::Monster()
{
	m_type = "MONSTER"; // Set the render pass for the monster
}

void Monster::Load(std::ifstream& _file) {
    // Call the parent class's Load to load common attributes
    ExampleGO::Load(_file);

    // Additional loading specific to MonsterGO
	StringHelp::String(_file, "NORMAL", m_NormalName);
    StringHelp::Float(_file, "WANDER_RADIUS", m_WanderRadius);
    StringHelp::Float(_file, "SPEED", m_Speed);
    StringHelp::Float(_file, "CHANGE_INTERVAL", m_ChangeInterval);
	StringHelp::Float(_file, "RENDER_PASS", RP);

	m_RP = (RenderPass)RP; // Set the render pass for the monster
}

void Monster::Init(Scene* _scene) {
    // Call the parent class's Init to initialize common attributes
    ExampleGO::Init(_scene); // Set the render pass for the monster;

    // Initialize additional attributes specific to MonsterGO
    m_Direction = glm::normalize(glm::vec3(rand() % 3 - 1, 0.0f, rand() % 3 - 1)); // Random initial direction
	cout << "Monster Direction: " << m_pos.x << " " << m_pos.y << " " << m_pos.z << endl;
}

void Monster::Tick(float _dt) {
    // Call the parent class's Tick to update common behavior
    ExampleGO::Tick(_dt);

    // Update wandering behavior
    Wander(_dt);
}

void Monster::Wander(float _dt) {
    m_Timer += _dt;

    // Change direction after a set interval
    if (m_Timer >= m_ChangeInterval) {
        m_Timer = 0.0f;

        // Generate a random new direction
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

        m_Direction = glm::normalize(glm::vec3(distribution(gen), 0.0f, distribution(gen)));
    }

    // Update position based on direction and speed
    glm::vec3 newPosition = m_pos + m_Direction * m_Speed * _dt;

    // Keep the monster within the wandering radius
    if (glm::length(newPosition) > m_WanderRadius) {
        m_Direction = -m_Direction; // Reverse direction if out of bounds
    }
    else 
    {
		m_pos = newPosition; // Update position
    }
}

void Monster::Render() {
	// Call the parent class's PreRender to set up shader values
	ExampleGO::PreRender();
    if (m_normalMap) {
        glActiveTexture(GL_TEXTURE1); // Bind to texture unit 1
        glBindTexture(GL_TEXTURE_2D, m_normalMap);
        GLint normalMapLocation = glGetUniformLocation(m_ShaderProg, "normalMap");
        glUniform1i(normalMapLocation, 1); // Tell the shader that the normal map is in texture unit 1
    }
	// Render the monster
	ExampleGO::Render();
}