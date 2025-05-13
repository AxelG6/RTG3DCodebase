#include "GameObjectFactory.h"
#include "GameObject.h"
#include "ExampleGO.h"
#include "Wall.h"
#include "Torch.h"
#include "Monster.h"
#include "Vortex.h"
#include <assert.h>

using std::string;

GameObject* GameObjectFactory::makeNewGO(string _type)
{
	printf("GAME OBJECT TYPE: %s \n", _type.c_str());
	if (_type == "GAME_OBJECT")
	{
		return new GameObject();
	}
	else if (_type == "EXAMPLE")
	{
		return new ExampleGO();
	}
	else if (_type == "TORCH")
	{
		return new Torch();
	}
	else if (_type == "MONSTER")
	{
		return new Monster();
	}
	else if (_type == "WALL")
	{
		return new Wall();
	}
	else if (_type == "VORTEX")
	{
		return new Vortex();
	}
	{
		printf("UNKNOWN GAME OBJECT TYPE: %s \n", _type.c_str());
		assert(0);
		return nullptr;
	}
}
