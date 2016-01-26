#include <iostream>
#include "noise/noise.h"
#include "tile.h"
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace noise;
tiles::tiles()
{
    height=100;
    width=100;
    double temp_height;
    fillMap();
    setPositions();
    MakeTileMap();
    setColors();


}

void tiles::fillMap()
{
    tileMap.resize(height);
    for(int a=0; a<height; a++)
    {
        tileMap[a].resize(width);

        for(int b=0; b<width; b++)
        {
            tileMap[a][b]=tile('P','E',10);
        }
    }
    //fills tileMap with blanks
}

void tiles::setPositions
{
 for(int a=0; a<mapp.height; a++)
 {
     for(int b=0; b<mapp.width; b++)
     {
        mapp.tileMap[a][b].y=10*a/mapp.height;
        mapp.tileMap[a][b].x=10*b/mapp.width;
     }
 }
}

void tiles::setColors
{
     for(int a=0; a<mapp.height; a++)
 {
     for(int b=0; b<mapp.width; b++)
     {
        mapp.tileMap[a][b].findColor();
     }
 }
}

void tiles::makeTileMap()
{
srand(time(NULL));
    module::Perlin preLandTerrain1;
    preLandTerrain1.SetFrequency(16);
    preLandTerrain1.SetSeed(rand());
    module::ScaleBias landTerrain1;
    landTerrain1.SetSourceModule(0,preLandTerrain1);
    landTerrain1.SetBias(-0.1);

    module::Perlin preLandTerrain2;
    preLandTerrain2.SetFrequency(2);
    preLandTerrain2.SetSeed(rand());
    module::ScaleBias landTerrain2;
    landTerrain2.SetSourceModule(0,preLandTerrain2);
    landTerrain2.SetScale(1.2);
    landTerrain2.SetBias(-0.2);

    module::RidgedMulti preOceanTerrain;
    preOceanTerrain.SetFrequency(32);
    module::ScaleBias oceanTerrain;
    oceanTerrain.SetSourceModule(0,preOceanTerrain);
    oceanTerrain.SetScale(0.1);
    oceanTerrain.SetBias(-0.2);
    //preTerrainType.SetFrequency();

    module::Select finalTerrain_;
    finalTerrain_.SetSourceModule(0,oceanTerrain);
    finalTerrain_.SetSourceModule(1,landTerrain1);
    finalTerrain_.SetControlModule(landTerrain2);
    finalTerrain_.SetBounds(-100.0,-.7);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    finalTerrain.SetBounds(-0.2,100);
    finalTerrain.SetEdgeFalloff(0.5);
    //generate map

    double temp_height;
    for(int a=0; a<height; a++)
    {
        for(int b=0; b<width; b++)
        {
            tileMap[a][b].elevation=finalTerrain.GetValue(tileMap[a][b].x,tileMap[a][b].y,.3);
        }
    }
    //sets elevations
}
   /* module::Turbulence turbulence;
    turbulence.SetSourceModule(0,turbulence);
    turbulence.SetFrequency(4.0);
    turbulence.SetPower(0.125);
*/




   // myModule.SetSeed(rand()%time(NULL));

   // module::Perlin terrainType;
   //e.SetSourceModule(0, myModule);
   // inverter.SetSourceModule(myModule);

// double perlin_map_width=2;
// double perlin_map_height=2;
/*
     utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
  heightMapBuilder.SetSourceModule(finalTerrain2);
  heightMapBuilder.SetDestNoiseMap(heightMap);
  heightMapBuilder.SetDestSize (1000, 1000);
  heightMapBuilder.SetBounds (-perlin_map_width/2,perlin_map_width/2 , -double perlin_map_height, double perlin_map_height/2);
   heightMapBuilder.Build ();
    utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);
  renderer.ClearGradient ();
 // renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
  renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  renderer.AddGradientPoint ( 1.200, utils::Color (255,255,255,255));
  renderer.EnableLight();
  renderer.SetLightContrast(3.0);
  renderer.SetLightBrightness(2.0);
  renderer.Render ();
   utils::WriterBMP writer;
  writer.SetSourceImage (image);
  writer.SetDestFilename ("tutorial.bmp");
  writer.WriteDestFile ();

class Tile
{
public:
    double elevation;
    coordinate position;

    char defaultchar;
    int movementCost;
    void SetColor();
    vector<double> color;
};

Tile(char dc,int mc)
{
    defaultchar=dc;movementCost=mc;elevation=finalTerrain2.GetValue(p.x,p.y);
    corner=false;
}
findPerlin(coordinate position)
class grass:Tile
{
*/
