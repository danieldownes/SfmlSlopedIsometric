#pragma once
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include<vector>

class Application
{
	public:
		Application();
		void run();

	private:
		void addQuad(int x, int y);	
		const int QUAD_SIZE;
		const int WIDTH;
		sf::RenderWindow m_window;
		sf::VertexArray m_pixels;





};

#endif




