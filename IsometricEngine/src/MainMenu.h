#pragma once

#include <SFML/Graphics.hpp>

enum class MenuOption
{
	MapEditor,
	Skirmish,
	Option3,
	Option4,
	Exit
};

MenuOption displayMenu();
