#pragma once
#include "ExampleGO.h"

class Floor: public ExampleGO
{
public:
	Floor();
	void Load(ifstream& file);
	void Render();
	void Init(Scene* _scene);
private:

};