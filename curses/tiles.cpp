#include <iostream>
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
    makeTileMap();
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
            tileMap[a][b]= new tile('P',0, grass);
        }
    }
    //fills tileMap with blanks
}

void tiles::setPositions()
{
 for(int a=0; a<height; a++)
 {
     for(int b=0; b<width; b++)
     {
//        tileMap[a][b]->position.y=10*a/height;
//        tileMap[a][b]->position.x=10*b/width;
          tileMap[a][b]->position=coordinate(a,b);
     }
 }
}

void tiles::setColors()
{
     for(int a=0; a<height; a++)
 {
     for(int b=0; b<width; b++)
     {
        tileMap[a][b]->find_material();
     }
 }
}

void tiles::makeTileMap()
{
srand(time(NULL));
    module::Perlin preLandTerrain1;
    preLandTerrain1.SetFrequency(1);
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
    oceanTerrain.SetScale(1.2);
    oceanTerrain.SetBias(-0.2);
    //preTerrainType.SetFrequency();

    module::Select finalTerrain_;
    finalTerrain_.SetSourceModule(0,oceanTerrain);
    finalTerrain_.SetSourceModule(1,landTerrain1);
    finalTerrain_.SetControlModule(landTerrain2);
    //finalTerrain_.SetBounds(-100.0,-.7);

    finalTerrain_.SetBounds(0,1000);

    module::Select finalTerrain;
    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    //finalTerrain.SetBounds(-0.2,100);
    finalTerrain.SetBounds(0,1000);
    finalTerrain.SetEdgeFalloff(0.5);
    //generate ma


    double temp_height;
    for(int a=0; a<height; a++)
    {
        for(int b=0; b<width; b++)
        {
            tileMap[a][b]->elevation=finalTerrain.GetValue(tileMap[a][b]->position.x,tileMap[a][b]->position.y,.3);
        }
    }
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
  heightMapBuilder.SetSourceModule(finalTerrain);
  heightMapBuilder.SetDestNoiseMap(heightMap);
  heightMapBuilder.SetDestSize (100, 100);
  heightMapBuilder.SetBounds (0,1 , 0, 1);
   heightMapBuilder.Build ();
    utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
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
  std::cout << "Here\n";
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
