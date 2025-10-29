// Handles food generation

#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "Utils.hpp"

class Food
{
private:
	sf::RectangleShape food_item;
	std::mt19937 rng;

public:	
	// Constructor
	Food(std::unordered_map<uint32_t, sf::RectangleShape>& occupied) : 
		rng(std::random_device{}())
	{
		generate_food(occupied);
	}

	// Generates food_item
	void generate_food(std::unordered_map<uint32_t, sf::RectangleShape>& occupied)
	{
		float food_x, food_y;
		do
		{
			food_x = static_cast<float>(rng() % 40) * 20;
			food_y = static_cast<float>(rng() % 40) * 20;
		} while ((occupied.find(pack_coords({ food_x, food_y }))) != occupied.end());

		sf::RectangleShape food({ 20.f, 20.f });
		food.setFillColor(sf::Color::Green);
		food.setPosition({ food_x, food_y });

		std::cout << "Food generated at coordinates: (" << food_x/20 << ", " << food_y/20 << ")\n";

		food_item = food;
	}

	// Returns const reference to food_item
	const sf::RectangleShape& get_food_item() const { return food_item; }
};
