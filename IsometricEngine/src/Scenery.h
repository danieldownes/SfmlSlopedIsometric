#pragma once

#include "Agent.h"

class Scenery : public Agent
{
   public:
	Scenery(float initialPosX, float initialPosY, std::string sceneryType)
		: Agent(initialPosX, initialPosY, -1, -1, -1, -1, false, sceneryType){};

   private:
};
