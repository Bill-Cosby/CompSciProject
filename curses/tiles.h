#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "tile.h"
#include "actor.h"
#include "include/dungeon.h"
#include <noise/noise.h>
#include "noiseutils.h"
#include "generateCity.h"
#include "spring.h"

class tiles
{
public:
    std::vector<std::vector<std::vector<tile*> > > tileMap;
    std::vector<city*> cityList;
    std::vector<spring*> springList;
    int height;
    int width;
    int mesh;
    double zoomIn;
    int citiesNeeded;
    int springsNeeded;
    const double darkWaterBelow=-.4;
    const double waterBelow =-.2;
    const double sandBelow =-.15;
    const double grassBelow =.3;
    const double dirtBelow = .6;
    const double rockBelow = .9;
    noise::module::Perlin preLandTerrain1;
    noise::module::Perlin prelandTerrain1;
    noise::module::ScaleBias landTerrain1;
    noise::module::Perlin preLandTerrain2;
    noise::module::ScaleBias landTerrain2;
    noise::module::RidgedMulti preOceanTerrain;
    noise::module::ScaleBias oceanTerrain;
    noise::module::Select finalTerrain_;
    noise::module::Select finalTerrain;
bool occupiedByCity(int,int);
   void fillMap();
   void makeElevationMap();
    int mod(signed int, int);
 std::string findTileType(double elevation);
void updateTileMap(int,int);
void placeCitiesandSprings();

void makeSpring (spring *);


tiles();

~tiles();
};

//void fillInDungeon(std::vector<std::vector<std::vector<tile*>>> &_map)
//{
//    dungeon Dungeon;
//    _map.resize(2);
//    for (int i = 0; i < _map.size(); i++){
//        _map[i].resize(Dungeon.h);
//        for (int j = 0; j < _map[i].size(); j++){
//            _map[i][j].resize(Dungeon.w);
//        }
//    }
//    int numberOfEnemies = 0;
//    for (int y = 0; y < Dungeon.h; y++){
//        for (int x = 0; x < Dungeon.w; x++){
//            if (Dungeon.dungeon_grid[y][x] == true){
//                _map[0][y][x] = new  tile(stonefloor,0,"stone",x,y);
//                _map[0][y][x]->position = coordinate(x,y);
//                _map[1][y][x] = new  tile;
//                _map[1][y][x]->position = coordinate(x,y);
//            }
//            else{
//                _map[0][y][x] = new  tile(stonefloor,0,"stone",x,y);
//                _map[0][y][x]->position = coordinate(x,y);
//                _map[1][y][x] = new  tile(stonewall,-1,"stone",x,y);
//                _map[1][y][x]->position = coordinate(x,y);
//            }
//
//        }
//    }
//    for (int y = 0; y < 2000; y++){
//        for (int x = 0; x < 2000; x++){
//            if (rand()%1000 == 1 and _map[1][y][x]->movementCost != -1){
//                    if (rand()%2==0)_map[1][y][x]->occupied = new monster("bat");
//                    else _map[1][y][x]->occupied = new monster("snake");
//                }
//                else if (rand()%3000 == 1 and _map[1][y][x]->movementCost != -1){
//                    _map[1][y][x] = new socialTile(closeddoor,-1,"wood");
//                    _map[1][y][x]->position = coordinate(x,y);
//                    for (int yy = y-6;yy<y+6;yy++){
//                        for (int xx = x-6;xx<x+6;xx++){
//                            if (yy == y and xx == x or yy < 0  or xx < 0 or yy >=2000 or xx >=2000)continue;
//                            _map[1][yy][xx] = new tile;
//                            _map[1][yy][xx]->position = coordinate(xx,yy);
//                            if (rand()%40 == 1){
//                                    _map[1][yy][xx]->occupied = new monster("goblin");
//                                    _map[1][yy][xx]->occupied->pos(yy,xx);
//                                    numberOfEnemies++;
//                            }
//                            else if (rand()%80 == 5){
//                                    _map[1][yy][xx]->occupied = new monster("orc");
//                                    _map[1][yy][xx]->occupied->pos(yy,xx);
//                                    numberOfEnemies++;
//                            }
//                        }
//                    }
//                }
//        }
//        std::cout << y << std::endl;
//    }
//    std::cout << "Number of sentient enemies: " << numberOfEnemies << std::endl;
//    std::cout << "Done w dungeon\n";
//    return;
//}


#endif //TILES_H_INCLUDE
