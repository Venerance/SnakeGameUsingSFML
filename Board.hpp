// main orchaestrator, handles the overall state of the board

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <iostream>
#include <array>
#include <utility>
#include <vector>
#include <queue>
#include <string>
#include "Snake.hpp"
#include "Utils.hpp"

enum class State {Active, Paused, GameOver};

constexpr std::array<std::pair<sf::Keyboard::Scancode, Direction>, 4> input_dir =
{ {
	{sf::Keyboard::Scancode::W, Direction::Up},
	{sf::Keyboard::Scancode::A, Direction::Left},
	{sf::Keyboard::Scancode::S, Direction::Down},
	{sf::Keyboard::Scancode::D, Direction::Right}
} };

class Board
{
private:
	std::unordered_map<uint32_t, sf::RectangleShape> occupied;
	Snake snek;
	Food food;
	State game_status;
	int score;
	int max_score;
	std::queue<Direction> input_queue;

	sf::Font font;
	sf::Text pause_text = sf::Text(font, "PAUSED\nSCORE: 0", 100);
	sf::Text gameover_text = sf::Text(font, "GAME OVER\nSCORE: 0\nHIGH SCORE: 0\nPRESS SPACEBAR\nTO RESTART", 100);

public:
	// Default constructor
	Board() : occupied(), snek(occupied), food(occupied), game_status(State::Active), score(0), max_score(0), input_queue()
	{
		if (!font.openFromFile("Pixellettersfull-BnJ5.ttf"))
			throw std::runtime_error("Font not found"); 

		center_text(pause_text);
		center_text(gameover_text);
	};

	// Registers input and changes snake direction if needed
	void handle_input(sf::RenderWindow& window, const sf::Keyboard::Scancode& input)
	{
		if (input == sf::Keyboard::Scancode::Escape)
			window.close();

		else if (input == sf::Keyboard::Scancode::Space)
		{
			if (game_status == State::GameOver)
			{
				std::cout << "Restarting game...\n";
				reset();
			}
			else if (game_status == State::Active)
			{
				game_status = State::Paused;
				std::cout << "Game paused!\n";
			}
			else
			{
				game_status = State::Active;
				std::cout << "Game un-paused!\n";
			}
		}

		else if (game_status == State::Active)
		{
			for (auto& p : input_dir)
			{
				if (input == p.first)
				{
					if (input_queue.size() == 2)
					{
						std::cout << "Input queue is full, input ignored\n";
						return;
					}
					Direction next_dir = p.second;
					Direction curr_dir = (input_queue.empty()) ? snek.get_dir() : input_queue.front();

					bool valid_input = snek.validate_rotation(next_dir, curr_dir);

					if (valid_input)
						input_queue.push(p.second);
				}
			}
		}
	}

	// Updates game state, checks bounds  
	void update()
	{
		if (game_status == State::Active)
		{
			Direction next_dir;

			if (!input_queue.empty())
			{
				next_dir = input_queue.front();
				input_queue.pop();
			}
			else
				next_dir = snek.get_dir();

			sf::Vector2f newhead = snek.get_snake_head() + offsets[static_cast<int>(next_dir)];

			if (newhead.x < 0.f || newhead.x >= 800.f ||
				newhead.y < 0.f || newhead.y >= 800.f ||
				occupied.find(pack_coords(newhead)) != occupied.end())
			{
				std::cout << "Game over!\n";
				game_status = State::GameOver;
			}
			else
				snek.move_snake(next_dir, occupied, food, score);
		}
	}	

	// Resets game to initial state
	void reset()
	{
		occupied.clear();
		snek = Snake(occupied);
		food = Food(occupied);
		score = 0;
		game_status = State::Active;
	}

	// Drawing the snake and the food item
	void render(sf::RenderWindow& window)
	{
		if (game_status == State::GameOver)
		{
			window.clear();
			max_score = (score > max_score) ? score : max_score;
			gameover_text.setString("GAME OVER\nSCORE: " + std::to_string(score) + "\nHIGH SCORE: " 
				+ std::to_string(max_score) + "\nPRESS SPACEBAR\nTO RESTART");
			window.draw(gameover_text);
			window.display();
		}
		else 
		{
			window.clear();

			for (const auto& coord_elem : occupied)
				window.draw(coord_elem.second);

			window.draw(food.get_food_item());

			if (game_status == State::Paused)
			{
				pause_text.setString("PAUSED\nSCORE: " + std::to_string(score));
				window.draw(pause_text);
			}

			window.display();
		}
	}

	// helper function to center a text object
	void center_text(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
		text.setPosition({ 400.f, 400.f });
	}

	// setter function to pause manually
	void pause() { game_status = State::Paused; }
};
