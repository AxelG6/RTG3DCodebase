#pragma once
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"
#include "core.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

using namespace glm;

class cTransform;
class Light;
class Scene;

//base class for a camera

class Camera
{
public:
	Camera();
	virtual ~Camera();

	//initialise the camera _width _height
	//scene maybe needed for more involved cameras to connect to relvant GOs and lights/shaders etc
	//TODO move _w and _h to tick for cameras so apsect ratio can be updated if we change the size of the window
	virtual void Init(float _w, float _h, Scene* _scene);

	//tick this camera
	//TODO: possibly pass keyboard / mouse stuff down here for player controls?
	virtual void Tick(float _dt,float aspectRatio);

	//load camera info from the mainfest
	virtual void Load(ifstream& _file);

	//getters
	string GetType() { return m_type; }

	glm::mat4 GetProj() { return m_projectionMatrix; }
	glm::mat4 GetView() { return m_viewMatrix; }

	glm::vec3 GetPos() { return m_pos; }

	float GetFOV() { return m_fovY; }
	float GetNear() { return m_nearPlane; }
	float GetFar() { return m_farPlane; }

	string GetName() { return m_name; }
	void SetName(string _name) { m_name = _name; }

	void Move(glm::vec3 _d) { m_pos += _d; }

	//where am I looking at
	vec3 GetLookAt() { return m_lookAt; }
	void SetLookAt(vec3 _pos) { m_lookAt = _pos; }

	//set up shader values for when using this camera
	virtual void SetRenderValues(unsigned int _prog);


	// return the pivot rotation around the x axis (theta) in degrees
	float getTheta();

	// return the pivot rotation around the y axis (phi) in degrees
	float getPhi();

	// rotate by angles dTheta, dPhi given in degrees
	void rotateCamera(float _dTheta, float _dPhi);

	// return the camera radius (distance from origin)
	float getRadius();

	// scale camera radius by s.  s is assumed to lie in the interval (0, +inf].  s < 1.0 reduces the radius while s > 1.0 increases the radius
	void scaleRadius(float _s);

	// increment camera radius by i.  The camera radius cannot have a value < 0.0 so the resulting radius lies in the interval [0, +inf].
	void incrementRadius(float _i);

	float getFovY();

	void setFovY(float _fovY);

	float getAspect();

	void setAspect(float _aspect);

	float getNearPlaneDistance();

	void setNearPlaneDistance(float _nearPlaneDistance);

	float getFarPlaneDistance();

	void setFarPlaneDistance(float _farPlaneDistance);


	// Accessor methods for derived values

	//glm::vec4 getPosition(); // return the camera location in world coordinate space.  The radius of the camera's position in spherical coordinates is the l2 norm of the returned position vector

	//glm::mat4 getOrientationBasis(); // return a const reference to the camera's orientation matrix in world coordinate space

	glm::mat4 viewTransform(); // return a const reference to the view transform matrix for the camera

	glm::mat4 projectionTransform();
	virtual void calculateDerivedValues();


protected:

	//standard transforms needed to render with this a basic camera
	glm::mat4 m_projectionMatrix;		// projection matrix
	glm::mat4 m_viewMatrix;			// view matrix

	//my camera is here
	glm::vec3 m_pos;

	//Location this camera is looking at
	glm::vec3 m_lookAt;

	float				m_theta, m_phi; // spherical coordinates theta (rotation around the x axis) and phi (rotation around the y axis).  <theta, phi> are stored in degrees.  Zero degree rotation on <theta, phi> places the camera on the +z axis.  A positive phi represents counter-clockwise rotation around the y axis in a right-hand coordinate system.  A positive theta represents a counter-clockwise rotation around the x axis in a right-handed coordinate system
	float				m_radius; // radius of the camera's spherical coordinate model.  This lies in the interval [0, +inf]

	// Projection / frustum values
	float				m_fovY, m_aspect, m_nearPlane, m_farPlane;
	string m_name;
	string m_type;
};

