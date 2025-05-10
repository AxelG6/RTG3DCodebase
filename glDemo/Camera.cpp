#include "Camera.h"
#include "helper.h"
#include <fstream>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "stringHelp.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
// constructor
/////////////////////////////////////////////////////////////////////////////////////
Camera::Camera()
{
	m_type = "CAMERA";
	m_theta = 0;
	m_phi = 0;
	calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// destructor
/////////////////////////////////////////////////////////////////////////////////////
Camera::~Camera()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// Init() - 
/////////////////////////////////////////////////////////////////////////////////////
void Camera::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{
	float aspect_ratio = _screenWidth / _screenHeight;

}

/////////////////////////////////////////////////////////////////////////////////////
// Update() - 
/////////////////////////////////////////////////////////////////////////////////////
void Camera::Tick(float _dt, float aspectRatio)
{
	float aspect_ratio = aspectRatio;

	m_viewMatrix = glm::lookAt(m_pos, m_lookAt, vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::radians(m_fovY), aspect_ratio, m_nearPlane, m_farPlane);
}

void Camera::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z);
	StringHelp::Float3(_file, "LOOKAT", m_lookAt.x, m_lookAt.y, m_lookAt.z);
	StringHelp::Float(_file, "FOV", m_fovY);
	StringHelp::Float(_file, "NEAR", m_nearPlane);
	StringHelp::Float(_file, "FAR", m_farPlane);
}

//set the base render values for this camera in the shaders
void Camera::SetRenderValues(unsigned int _prog)
{
	GLint loc;

	//matrix for the view transform
	if (Helper::SetUniformLocation(_prog, "viewMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetView()));

	//matrix for the projection transform
	if (Helper::SetUniformLocation(_prog, "projMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetProj()));

	//the current camera is at this position
	if (Helper::SetUniformLocation(_prog, "camPos", &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetPos()));
}


// return the pivot rotation around the x axis (theta) in degrees
float Camera::getTheta() {

	return m_theta;
}

// return the pivot rotation around the y axis (phi) in degrees
float Camera::getPhi() {

	return m_phi;
}

void Camera::rotateCamera(float _dTheta, float _dPhi) {

	m_theta += _dTheta*0.1;
	m_phi += _dPhi*0.1;

	const float theta_ = glm::radians<float>(m_theta);
	const float phi_= glm::radians<float>(m_phi);

	glm::vec3 direction;
	direction.x = sinf(phi_) * cosf(theta_);
	direction.y = sinf(theta_);
	direction.z = cosf(phi_) * cosf(theta_);
	m_lookAt = m_pos + direction;
	cout << "Camera::rotateCamera: m_lookAt = " << glm::to_string(m_lookAt) << endl;
	calculateDerivedValues();
	
}

float Camera::getRadius() {

	return m_radius;
}

void Camera::scaleRadius(float _s) {

	m_radius *= _s;
	calculateDerivedValues();
}

void Camera::incrementRadius(float _i) {

	m_radius = std::max<float>(m_radius + _i, 0.0f);
	calculateDerivedValues();
}

float Camera::getFovY() {

	return m_fovY;
}

void Camera::setFovY(float _fovY) {

	this->m_fovY = _fovY;
	calculateDerivedValues();
}

float Camera::getAspect() {

	return m_aspect;
}

void Camera::setAspect(float _aspect) {

	this->m_aspect = _aspect;
	calculateDerivedValues();
}

float Camera::getNearPlaneDistance() {

	return m_nearPlane;
}

void Camera::setNearPlaneDistance(float _nearPlaneDistance) {

	this->m_nearPlane = _nearPlaneDistance;
	calculateDerivedValues();
}

float Camera::getFarPlaneDistance() {

	return m_farPlane;
}

void Camera::setFarPlaneDistance(float _farPlaneDistance) {

	this->m_farPlane = _farPlaneDistance;
	calculateDerivedValues();
}

void Camera::calculateDerivedValues() {

	const float theta_ = glm::radians<float>(m_theta);
	const float phi_ = glm::radians<float>(m_phi);
	// calculate view and projection transform matrices
	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -m_radius)) * glm::eulerAngleX(-theta_) * glm::eulerAngleY(-phi_);
	m_projectionMatrix = glm::perspective(glm::radians<float>(m_fovY), m_aspect, m_nearPlane, m_farPlane);
}
#pragma endregion


#pragma region Accessor methods for derived values

// return a const reference to the view transform matrix for the camera
glm::mat4 Camera::viewTransform() {

	return m_viewMatrix;
}

// return a const reference the projection transform for the camera
glm::mat4 Camera::projectionTransform() {

	return m_projectionMatrix;
}
