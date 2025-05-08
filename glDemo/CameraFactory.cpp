#include "CameraFactory.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include <assert.h>

using std::string;

Camera* CameraFactory::makeNewCam(string _type)
{
	printf("CAM TYPE: %s \n", _type.c_str());
	if (_type == "CAMERA")
	{
		return new Camera();
	}
	else if (_type == "ORTHO")
	{
		return new OrthographicCamera();
	}
	else
	{
		printf("UNKNOWN CAMERA TYPE!");
		assert(0);
		return nullptr;
	}
}
