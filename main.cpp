#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Snek game");
	window.setFramerateLimit(10);

	Board game;

	while (window.isOpen())
	{
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				game.handle_input(window, keyPressed->scancode);
			}
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		if (!window.hasFocus())
			game.pause();

		game.update();
		game.render(window);
	}
}
