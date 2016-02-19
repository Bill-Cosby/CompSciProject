#ifndef SHADOWCASTING_H_INCLUDED
#define SHADOWCASTING_H_INCLUDED
#include "tile.h"
#include <vector>
#include <math.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "actor.h"

static int multipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*>& actors,  unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window);

void do_fov(std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, std::vector<actor*> &actors,  unsigned int x, unsigned int y, unsigned int radius, sf::RenderWindow &window);

#endif // SHADOWCASTING_H_INCLUDED
