#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <vector>

#define NUMBER_OF_COLORS 13

#define stonewall 0
#define stonefloor 1
#define opendoor 2
#define closeddoor 3
#define woodwall 4
#define woodfloor 5
#define grass 6
#define dirt 7
#define woodchair 8
#define bed 9
#define chair 10
#define bigchair 11
#define chest 12

#include "RSL.h"
#include <SFML/Graphics.hpp>

const sf::Texture textures[13] = {   RSL::getTextureData("data/textures/tiles.raw","stonewall.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","stonefloor.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","opendoor.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","door.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","woodwall.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","woodfloor.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","grass.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","dirt.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","woodchair.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","bed.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","chair.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","bigchair.texture"),
                                    RSL::getTextureData("data/textures/tiles.raw","chest.texture")
                                };

const sf::Color  ironColor  = sf::Color(sf::Color(197,103,41));
const sf::Color steelColor  = sf::Color(sf::Color(180,184,187));
const sf::Color copperColor = sf::Color(sf::Color(188,84,31));
const sf::Color cottonColor = sf::Color(sf::Color(221,219,220));

const sf::Color stoneColor  = sf::Color (sf::Color(128,128,128));
const sf::Color grassColor  = sf::Color(sf::Color(49,99,0));
const sf::Color  dirtColor  = sf::Color(sf::Color(155,118,83));
const sf::Color  woodColor  = sf::Color(sf::Color(156,94,47));
const sf::Color  waterColor  = sf::Color(sf::Color(0,0,100));

const sf::Color whiteSkinColor = sf::Color(sf::Color(242,221,220));
const sf::Color brownSkinColor = sf::Color(sf::Color(109,70,0));
const sf::Color  tanSkinColor  = sf::Color(sf::Color(173,109,0));
const sf::Color greenSkinColor = sf::Color(sf::Color(51,109,0));
const sf::Color blackSkinColor = sf::Color(sf::Color(0,0,0));

const sf::Color redEye = sf::Color(sf::Color(255,0,0));
const sf::Color blueEye = sf::Color(sf::Color(73,85,165));
const sf::Color greenEye = sf::Color(sf::Color(39,125,61));
const sf::Color greyEye = sf::Color(sf::Color(127,129,130));
const sf::Color blackEye = sf::Color(sf::Color(1,4,7));
const sf::Color brownEye = sf::Color(sf::Color(90,60,40));
const sf::Color hazelEye = sf::Color(sf::Color(133,113,64));
const sf::Color yellowEye = sf::Color(sf::Color(180,132,3));


class material
{
public:
    int weight;

};

sf::Color giveColor(std::string mat_name);



#endif // MATERIALS_H_INCLUDED
