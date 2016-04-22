#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "tile.h"
#include <noise/noise.h>
#include "noiseutils.h"

class tiles
{
public:
    std::vector<std::vector<std::vector<tile*> > > tileMap;
    int height;
    int width;
    int mesh;
    double zoomOut;
    const double waterBelow =-.2;
    const double sandBelow =-.15;
    const double grassBelow =.3;
    const double dirtBelow = .6;
    const double rockBelow = .9;
    noise::module::Perlin preLandTerrain1;
    noise::module::ScaleBias landTerrain1;
    noise::module::Perlin preLandTerrain2;
    noise::module::ScaleBias landTerrain2;
    noise::module::RidgedMulti preOceanTerrain;
    noise::module::ScaleBias oceanTerrain;
    noise::module::Select finalTerrain_;
    noise::module::Select finalTerrain;

   void fillMap();
   void makeElevationMap();
    int mod(signed int, int);
 std::string findTileType(double elevation);
void updateTileMap(int,int,int,int);



tiles();

~tiles();
};


#endif //TILES_H_INCLUDE
