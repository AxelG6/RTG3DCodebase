#include "Scene.h"
#include "GameObject.h"
#include "CameraFactory.h"
#include "Camera.h"
#include "orthoCamera.h"
#include "FPCamera.h"
#include "LightFactory.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "ModelFactory.h"
#include "model.h"
#include "helper.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObjectFactory.h"
#include <assert.h>

Scene::Scene()
{
}

Scene::~Scene()
{
		// Delete all cameras
		for (Camera* camera : m_Cameras) {
			delete camera;
		}
		m_Cameras.clear();

		// Delete all lights
		for (Light* light : m_Lights) {
			delete light;
		}
		m_Lights.clear();

		// Delete all game objects
		for (GameObject* gameObject : m_GameObjects) {
			delete gameObject;
		}
		m_GameObjects.clear();

		// Delete all textures
		for (Texture* texture : m_Textures) {
			delete texture;
		}
		m_Textures.clear();

		// Delete all models
		for (Model* model : m_Models) {
			delete model;
		}
		m_Models.clear();

		// Delete all shaders
		for (Shader* shader : m_Shaders) {
			delete shader;
		}
		m_Shaders.clear();

		// Reset the active camera
		m_useCamera = nullptr;
	}

//tick all my Game Objects, lights and cameras
void Scene::Update(float _dt,float aspectRatio)
{
	
	//update all lights
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{
		(*it)->Tick(_dt);
	}

	//update all cameras
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); it++)
	{
		(*it)->Tick(_dt, aspectRatio);
	}

	//update all GameObjects
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(_dt);
	}
}

void Scene::AddGameObject(GameObject* _new)
{
	m_GameObjects.push_back(_new);
}

//I want THAT Game Object by name
GameObject* Scene::GetGameObject(string _GOName)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetName() == _GOName)
		{
			return (*it);
		}
	}
	printf("Unknown Game Object NAME : %s \n", _GOName.c_str());
	assert(0);
	return nullptr;
}

Camera* Scene::GetUseCamera()
{
	return m_useCamera;
}

Camera* Scene::GetCamera(string _camName)
{
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); it++)
	{
		if ((*it)->GetName() == _camName)
		{
			return (*it);
		}
	}
	printf("Unknown Camera NAME : %s \n", _camName.c_str());
	assert(0);
	return nullptr;
}

Light* Scene::GetLight(string _lightName)
{
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{
		if ((*it)->GetName() == _lightName)
		{
			return (*it);
		}
	}
	printf("Unknown Light NAME : %s \n", _lightName.c_str());
	assert(0);
	return nullptr;
}

Texture* Scene::GetTexture(string _texName)
{
	for (list<Texture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		if ((*it)->GetName() == _texName)
		{
			return (*it);
		}
	}
	printf("Unknown Texture NAME : %s \n", _texName.c_str());
	assert(0);
	return nullptr;
}

Model* Scene::GetModel(string _modelName)
{
	for (list<Model*>::iterator it = m_Models.begin(); it != m_Models.end(); it++)
	{
		if ((*it)->GetName() == _modelName)
		{
			return (*it);
		}
	}
	printf("Unknown Model NAME : %s \n", _modelName.c_str());
	assert(0);
	return nullptr;
}

Shader* Scene::GetShader(string _shaderName)
{
	for (list<Shader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++)
	{
		if ((*it)->GetName() == _shaderName)
		{
			return (*it);
		}
	}
	printf("Unknown Shader NAME : %s \n", _shaderName.c_str());
	assert(0);
	return nullptr;
}

//Render Everything
void Scene::Render()
{

	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetRP() & RP_OPAQUE)
		{
			//set shader program using
			GLuint SP = (*it)->GetShaderProg();

			GLint timeLocation = glGetUniformLocation(SP, "time");
			GLint numPointLightsLocation = glGetUniformLocation(SP, "numPointLights");
			GLint numSpotLightsLocation = glGetUniformLocation(SP, "numSpotLights");

			int activePointLights=8;

			int activeSpotLights=1;


			float currentTime = (float)glfwGetTime(); // or use SDL_GetTicks() / 1000.0f for SDL


			glUseProgram(SP);
			glUniform1f(timeLocation, currentTime);
			glUniform1i(numPointLightsLocation, activePointLights);
			glUniform1i(numSpotLightsLocation, activeSpotLights);
			//set up for uniform shader values for current camera
			m_useCamera->SetRenderValues(SP);

			SetShaderUniforms(SP);

			//set any uniform shader values for the actual model
			(*it)->PreRender();

			//actually render the GameObject
			(*it)->Render();
		}
	}
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetRP() & RP_TRANSPARENT)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			//set shader program using
			GLuint SP = (*it)->GetShaderProg();

			GLint timeLocation = glGetUniformLocation(SP, "time");
			GLint numPointLightsLocation = glGetUniformLocation(SP, "numPointLights");
			GLint numSpotLightsLocation = glGetUniformLocation(SP, "numSpotLights");

			GLint alphaLocation = glGetUniformLocation(SP, "alphaValue");
			glUseProgram(SP);
			glUniform1f(alphaLocation, 0.5f);
			int activePointLights = 2;

			int activeSpotLights = 1;

			float currentTime = (float)glfwGetTime(); // or use SDL_GetTicks() / 1000.0f for SDL


			glUseProgram(SP);
			glUniform1f(timeLocation, currentTime);
			glUniform1i(numPointLightsLocation, activePointLights);
			glUniform1i(numSpotLightsLocation, activeSpotLights);
			//set up for uniform shader values for current camera
			m_useCamera->SetRenderValues(SP);
			
			SetShaderUniforms(SP);
			//set any uniform shader values for the actual model
			(*it)->PreRender();
			//actually render the GameObject
			(*it)->Render();
			glDepthMask(GL_TRUE); // Re-enable depth writing
			glDisable(GL_BLEND);
		}
	}
}

void Scene::SetShaderUniforms(GLuint _shaderprog)
{
	//everything needs to know about all the lights
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{	
		if ((*it)->GetType() == "POINT")
		{
			PointLight* pointLight = dynamic_cast<PointLight*>(*it);
			if (pointLight)
			{
				pointLight->SetAllRenderValues(_shaderprog);// Pass the index of the light
			}
		}
		else if ((*it)->GetType() == "SPOT")
		{
			SpotLight* spotLight = dynamic_cast<SpotLight*>(*it);
			if (spotLight)
			{
				spotLight->SetAllRenderValues(_shaderprog);// Pass the index of the light
			}
		}
		else if ((*it)->GetType() == "DIRECTION")
		{
			(*it)->SetRenderValues(_shaderprog);
		}
		else 
		{
			(*it)->SetRenderValues(_shaderprog);
		}
	}
}

void Scene::Load(ifstream& _file)
{
	string dummy;

	//load Cameras
	_file >> dummy >> m_numCameras; _file.ignore(256, '\n');
	cout << "CAMERAS : " << m_numCameras << endl;
	for (int i = 0; i < m_numCameras; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Camera* newCam = CameraFactory::makeNewCam(type);
		newCam->Load(_file);

		m_Cameras.push_back(newCam);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Lights
	_file >> dummy >> m_numLights; _file.ignore(256, '\n');
	cout << "LIGHTS : " << m_numLights << endl;
	for (int i = 0; i < m_numLights; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Light* newLight = LightFactory::makeNewLight(type);
		newLight->Load(_file);

		m_Lights.push_back(newLight);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Models
	_file >> dummy >> m_numModels; _file.ignore(256, '\n');
	cout << "MODELS : " << m_numModels << endl;
	for (int i = 0; i < m_numModels; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Model* newModel = ModelFactory::makeNewModel(type);
		newModel->Load(_file);

		m_Models.push_back(newModel);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Textures
	_file >> dummy >> m_numTextures; _file.ignore(256, '\n');
	cout << "TEXTURES : " << m_numTextures << endl;
	for (int i = 0; i < m_numTextures; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		m_Textures.push_back(new Texture(_file));

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Shaders
	_file >> dummy >> m_numShaders; _file.ignore(256, '\n');
	cout << "SHADERS : " << m_numShaders << endl;
	for (int i = 0; i < m_numShaders; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		m_Shaders.push_back(new Shader(_file));

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load GameObjects
	_file >> dummy >> m_numGameObjects; _file.ignore(256, '\n');
	cout << "GAMEOBJECTS : " << m_numGameObjects << endl;
	for (int i = 0; i < m_numGameObjects; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		GameObject* newGO = GameObjectFactory::makeNewGO(type);
		newGO->Load(_file);

		m_GameObjects.push_back(newGO);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}


}

void Scene::Init()
{
	//initialise all cameras
	//scene is passed down here to allow for linking of cameras to game objects
	int count = 0;
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); ++it)
	{
		(*it)->Init(1048, 1048, this);// TODO: set correct screen sizes here

		//if a camera is called MAIN
		//this will be the starting camera used
		if ((*it)->GetName() == "MAIN")
		{
			m_useCamera = (*it);
			m_useCameraIndex = count;
		}
		count++;
	}

	//if no MAIN camera just use the first one
	if (!m_useCamera)
	{
		m_useCamera = (*m_Cameras.begin());
		m_useCameraIndex = 0;
	}

	//set up links between everything and GameObjects
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Init(this);
	}
}
//change name
void Scene::SwitchCamera()
{
	m_useCameraIndex++;
	m_useCameraIndex = m_useCameraIndex % m_numCameras;

	auto it = m_Cameras.begin();
	std::advance(it, m_useCameraIndex);
	m_useCamera = (*it);
}

void Scene::mouseMoveHandlerC(double _xpos, double _ypos)
{

	if (m_useCamera) {
		FirstPersonCamera* cam = dynamic_cast<FirstPersonCamera*>(m_useCamera);

		if (cam)
		{
			cam->ProcessMouseMovement(_xpos, _ypos);
		}
		else
		{
			// Handle the case where m_useCamera is not of type Camera
			cout << "Camera is not of type Camera" << endl;
		}
	}
}

void Scene::mouseScrollHandlerC(double _xoffset, double _yoffset) {

	if (m_useCamera)
	{
		OrthographicCamera* cam = dynamic_cast<OrthographicCamera*>(m_useCamera);
		if (cam)
		{
			cam->Zoom(_yoffset); // Use the zoom function of the orthographic camera
		}
		else
		{
			cout << "Camera is not of type OrthographicCamera" << endl;
		}
	}
	else
	{

	}
}


void Scene::CameraMovement(vec3 direction, float speed)
{
	if (m_useCamera)
	{
		OrthographicCamera* cam = dynamic_cast<OrthographicCamera*>(m_useCamera);
		FirstPersonCamera* cam2 = dynamic_cast<FirstPersonCamera*>(m_useCamera);
		if (cam)
		{
			cam->move(direction, speed); 

		}
		else if (cam2)
		{
			
			cam2->ProcessKeyboardInput(direction, speed); 
		}
		else
		{
			 // Move left along the x-axis
		}
	}
}