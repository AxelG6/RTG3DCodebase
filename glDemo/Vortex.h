#pragma once
#include "ExampleGO.h"

class Vortex : public ExampleGO
{
public:
	Vortex();

	void Load(ifstream& file);
	void Render();
	void Init(Scene* _scene);
	
private:
};