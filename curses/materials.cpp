#include "materials.h"


sf::Texture giveTexture(char defaultChar)
{


    if (defaultChar == '0')return stonefloor;
    if (defaultChar == '1')return stonewall;
    if (defaultChar == '2')return closedDoor;
    if (defaultChar == '3')return openDoor;
    if (defaultChar == '4')return woodfloor;
    if (defaultChar == '5')return woodwall;
    if (defaultChar == '6')return grassGround;
    if (defaultChar == '7')return dirtGround;
}

sf::Color giveColor(std::string mat_name)
{
    if (mat_name == "iron") return ironColor;
     if (mat_name == "steel")return steelColor;
     if (mat_name == "wood") return woodColor;
    if (mat_name == "copper")return copperColor;
     if (mat_name == "stone")return stoneColor;

    if (mat_name == "white")return whiteSkinColor;
    if (mat_name == "brown")return brownSkinColor;
     if (mat_name == "tan") return tanSkinColor;
    if (mat_name == "green")return greenSkinColor;
    if (mat_name == "black")return blackSkinColor;
}
