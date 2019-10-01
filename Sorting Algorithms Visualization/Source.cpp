#include <SFML/Graphics.hpp>
#include "Main.h"
#include <iostream>

sf::RenderWindow* window;

int main() {

	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Application");
	window->setFramerateLimit(60);


	start();

	while (window->isOpen()) {
		sf::Event e;
		while (window->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window->close();
				break;

			// Add more events here!

			}
		}

		window->clear();
		draw();
		window->display();
	}

	end();

	return 0;
}