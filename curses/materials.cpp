#include "materials.h"

sf::Color giveColor(std::string mat_name)
{
    if (mat_name == "iron") return ironColor;
     if (mat_name == "steel")return steelColor;
    if (mat_name == "copper")return copperColor;
    if (mat_name == "cotton")return cottonColor;

     if (mat_name == "stone")return stoneColor;
     if (mat_name == "grass")return grassColor;
     if (mat_name == "dirt")return dirtColor;
     if (mat_name == "wood") return woodColor;

    if (mat_name == "white")return whiteSkinColor;
    if (mat_name == "brown")return brownSkinColor;
     if (mat_name == "tan") return tanSkinColor;
    if (mat_name == "green")return greenSkinColor;
    if (mat_name == "black")return blackSkinColor;
}
