#pragma once
#include "ExampleGO.h"

class Wall : public ExampleGO
{
public:
	Wall();
	
	void Load(ifstream& file);
	void Render();
	void Init(Scene* _scene);
private:

};