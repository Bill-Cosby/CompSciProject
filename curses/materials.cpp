#include "materials.h"


material::material(std::string mat_name)
{
    if (mat_name == "iron")color = ironColor;
    if (mat_name == "steel")color = steelColor;
    if (mat_name == "wood")color = woodColor;
    if (mat_name == "copper")color = copperColor;
    if (mat_name == "stone")color = stoneColor;

    if (mat_name == "white")color = whiteSkinColor;
    if (mat_name == "brown")color = brownSkinColor;
    if (mat_name == "tan")color = tanSkinColor;
    if (mat_name == "green")color = greenSkinColor;
    if (mat_name == "black")color = blackSkinColor;
}
