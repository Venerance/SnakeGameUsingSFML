// just some functions to turn pairs into single values

#pragma once

// packs two 16-bit values into one 32-bit value
// first 16 bits represent one number
// next 16 bits represent the other
// note that coordinates lie between 0 to 800
constexpr uint32_t pack_coords(sf::Vector2f coord)
{
	return (static_cast<uint32_t>(coord.x) << 16) |
		static_cast<uint32_t>(coord.y);
}

// undoes pack_coords() to retrive original pair
constexpr sf::Vector2f unpack_coords(uint32_t packed)
{
	return sf::Vector2f(static_cast<float>(packed >> 16),
		static_cast<float>(packed & 65535));
}
