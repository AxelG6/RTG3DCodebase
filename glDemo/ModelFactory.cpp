#include "ModelFactory.h"
#include <assert.h>
#include "AIModel.h"
#include "Plane.h"

Model* ModelFactory::makeNewModel(std::string _type)
{
	printf("TYPE: %s \n", _type.c_str());
	//There is no point in making one of the model base class 
	//as it doesn't do anything 
	if (_type == "AI")
	{
		return new AIModel();
	}
	else if (_type == "PLANE")
	{
		return new Plane();
	}
	else
	{
		printf("UNKNOWN MODEL TYPE: %s \n", _type.c_str());
		assert(0);
		return nullptr;
	}
}
