#pragma once

#include <SFML/Graphics/Font.hpp>

namespace FontLoader
{
bool load(sf::Font& font, const char* executablePath);
}
