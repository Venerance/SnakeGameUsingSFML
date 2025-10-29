// handles snake generation, growth and movement

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <array>
#include <string>
#include "Utils.hpp"
#include "Food.hpp"

// note that the directions are ordered 
// in accordance to an anti-clockwise rotation
enum class Direction { Up, Left, Down, Right };

constexpr std::array<sf::Vector2f, 4> offsets =
{ {
	{0.f, -20.f},
	{-20.f, 0.f},
	{0.f, 20.f},
	{20.f, 0.f}
} };

constexpr sf::Vector2f get_offset(Direction dir) { return offsets[static_cast<int>(dir)]; }

class Snake 
{
private:
	std::deque<sf::Vector2f> snake;
	Direction dir;

public:
	// constructor
	Snake(std::unordered_map<uint32_t, sf::RectangleShape>& occupied) : 
		dir(Direction::Up)
	{
		for (int i = 0; i < 3; ++i)
		{
			sf::Vector2f coord(300.f, 300.f + 20.f * i);
			sf::RectangleShape rect({ 20.f, 20.f });
			rect.setFillColor(sf::Color::Blue);
			rect.setPosition(coord);

			occupied[pack_coords(coord)] = rect;
			snake.push_back(coord);
		}
		std::cout << "Snake generated, moving in direction: " << dir_to_str() << "\n";
	};

	// to... move the snake
	void move_snake(const Direction next_dir, 
					std::unordered_map<uint32_t, sf::RectangleShape>& occupied,
					Food& food,
					int& score)
	{
		// change snake direction
		dir = next_dir;

		sf::Vector2f newhead = snake.front() + offsets[static_cast<int>(next_dir)];

		sf::RectangleShape rect({ 20.f, 20.f });
		rect.setFillColor(sf::Color::Blue);

		snake.push_front(newhead);
		rect.setPosition(newhead);
		occupied[pack_coords(newhead)] = rect;

		if (newhead != food.get_food_item().getPosition())
		{
			sf::Vector2f tail = snake.back();
			snake.pop_back();
			occupied.erase(pack_coords(tail));
		}
		else
		{
			std::cout << "---Food eaten!---\n";
			food.generate_food(occupied);
			++score;
		}
		std::cout << "Position updated\n";
	}

	// allows the snake to rotate by right angles in the clockwise
	// and anticlockwise direction, ignores direction inputs in the 
	// opposite and same direction (constrained change of snake direction)
	bool validate_rotation(const Direction next_dir, const Direction curr_dir) const
	{		
		bool res;
		// when the snake turns clockwise
		if ((static_cast<int>(next_dir) + 3) % 4 == static_cast<int>(curr_dir))
		{
			std::cout << "Registered anti-clockwise turn\n";
			res = true;
		}
		// when the snake turns anti-clockwise
		else if ((static_cast<int>(next_dir) + 1) % 4 == static_cast<int>(curr_dir))
		{
			std::cout << "Registered clockwise turn\n";
			res = true;
		}
		else if (next_dir == dir)
		{
			std::cout << "No direction change, input ignored\n";
			res = false;
		}
		else
		{
			std::cout << "Immediate direction reversal, input ignored\n";
			res = false;
		}
		std::cout << "Snake moving in direction: " << dir_to_str() << "\n";
		return res;
	}

	// const getter for read-only access to the snake's direction
	Direction get_dir() const { return dir; }

	// just for convenience of printing logs
	std::string dir_to_str() const
	{
		if (dir == Direction::Up)
		{
			return "UP";
		}
		else if (dir == Direction::Left)
		{
			return "LEFT";
		}
		else if (dir == Direction::Down)
		{
			return "DOWN";
		}
		else
		{
			return "RIGHT";
		}
	}

	// const getter for the snake's head, for checking collisions
	sf::Vector2f get_snake_head() const { return snake.front(); }
};
