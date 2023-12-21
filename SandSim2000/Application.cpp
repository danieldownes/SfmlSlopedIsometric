#include "Application.h"

Application::Application()
: QUAD_SIZE	(4)
,m_window			({ 640, 480 }, "Conway's Game of Life")
/*
,m_pixels			((m_window.getSize().x / QUAD_SIZE) * 
					(m_window.getSize().y / QUAD_SIZE))
*/
,WIDTH			(m_window.getSize().x / QUAD_SIZE)
{
	auto addQuad = [&](int x, int y)
		{
			sf::Vertex topRight;
			sf::Vertex topLeft;
			sf::Vertex bottomRight;
			sf::Vertex bottomLeft;



			float pixelX = x * QUAD_SIZE;
			float pixelY = y * QUAD_SIZE;
			int index = y * WIDTH + x;

			topRight		.position = { pixelX,				pixelY };
			topLeft		.position = { pixelX + WIDTH,	pixelY };
			bottomRight	.position = { pixelX,				pixelY + WIDTH };
			bottomLeft	.position = { pixelX + WIDTH,	pixelY + WIDTH };

			sf::Vertex* v = &m_pixels[index];

		};
}

void Application::run()
{

}