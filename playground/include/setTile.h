#ifndef SETTILE_H_INCLUDED
#define SETTILE_H_INCLUDED
#include <vector>
#include "tile.h"
#include "materials.h"

void setTile(std::vector<std::vector<tile*> > &_map, std::string tileName,coordinate spawnPoint)
{
    if (tileName == "opendoor")_map[spawnPoint.y][spawnPoint.x] = new door(true,wood);
    if (tileName == "door")_map[spawnPoint.y][spawnPoint.x] = new door(false,wood);
    if (tileName == "wall") _map[spawnPoint.y][spawnPoint.x] = new tile('0',-1,stone);
    if (tileName == "floor") _map[spawnPoint.y][spawnPoint.x] = new tile('1',0,stone);

    _map[spawnPoint.y][spawnPoint.x]->position = spawnPoint;
    _map[spawnPoint.y][spawnPoint.x]->sprite.setPosition(spawnPoint.x*16,spawnPoint.y*16);
}

#endif // SETTILE_H_INCLUDED
