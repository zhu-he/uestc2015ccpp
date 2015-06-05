#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SFML/Graphics/RenderWindow.hpp>

class Window : public sf::RenderWindow
{
	public:
		Window();
		void onResize();
	private:
		sf::View m_view;
};

#endif // __WINDOW_HPP__
