#pragma once
#include "ExampleGO.h"

class Torch : public ExampleGO
{
public:
	Torch();

	void Load(ifstream& file);
	void Render();
	void Init(Scene* _scene);

private:
	
};