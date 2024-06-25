#pragma once
#include "Scenery.h"
class Tree : public Scenery
{
   public:
	Tree(float initialPosX, float initialPosY) : Scenery(initialPosX, initialPosY, "Tree") {}
};
