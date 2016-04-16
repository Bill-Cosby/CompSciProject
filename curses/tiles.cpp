#include <iostream>
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace noise;
tiles::tiles()
{
    height=5000;
    width=5000;
    makeElevationMap();
    fillMap();
    updateTileMap(1,1,0,0);

}

int tiles::mod(signed int a, int b)
{
    if(a<0)
    {
        while(a<0)
        {
            a+=b;
        }
    }
    else if (a>=0)
    {
        while(a>=b)
        {
        a-=b;
        }
    }
    return a;
}

void tiles::fillMap()
{
    tileMap.resize(2);
    for(int a=0; a<2; a++)
    {
        tileMap[a].resize(height);
        for(int b=0; b<height; b++)
    {
        tileMap[a][b].resize(width);
        for(int c=0; c<tileMap[a][b].size(); c++)
        {
            tileMap[a][b][c]=NULL;
        }
    }
    }

    //fills tileMap with blanks
}



void tiles::makeElevationMap()
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
    finalTerrain_.SetBounds(-100.0,-.7);


    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    finalTerrain.SetBounds(-0.7,100);
    finalTerrain.SetEdgeFalloff(0.5);
    //generate ma
/*
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
  std::cout<<finalTerrain.GetValue(0,0,0.5);
    //sets elevations*/
}

tiles::~tiles()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap[a].size(); b++)
        {
            for(int c=0; c<tileMap[a][b].size(); c++)
            {
                delete tileMap[a][b][c];
            }

        }
    }
}

std::string tiles::findTileType(double elevation)
{
     if(elevation<-.2)
    {
       return "water";
    }
    else if(elevation<.2)
    {
        return "sand";
    }
    else if(elevation<.4)
    {
        return "grass";
    }
    else if(elevation<.6)
    {
        return "dirt";
    }
    else if(elevation<.8)
    {
        return "stone";
    }
    else
    {
        return "white";//snow
    }
}
void tiles::updateTileMap(signed int gridx,signed int gridy,signed int newGridx,signed int newGridy)
{
    int mesh=100;
gridx=mod(gridx,width);
gridy=mod(gridy,height);

signed int deltax=newGridx-gridx;
signed int deltay=newGridy-gridy;
signed int gridyDelete=gridy-deltay;

   //delete x stuff

  for(signed int c=-1; c<=1; c++)
  {
      for(int a=0; a<mesh; a++)
      {
          for(int b=0; b<mesh; b++)
      {
         if(deltax!=0)
         {
             tileMap[0][mod((gridy+c),height)*mesh+a][mod((gridx-deltax),width)*mesh+b]=NULL;

             double x=(newGridx+deltax)*mesh+b;
             double y=(newGridy+c)*mesh+a;//x/widthy/heightdouble elevation =
              std::cout<<finalTerrain.GetValue(1,1, 1);
              double elevation=0;
            tileMap[0][y][x]=new tile(grass,0,findTileType(elevation));
            tileMap[0][y][x]=new tile(grass,0,findTileType(elevation));
            tileMap[0][y][x]->elevation=elevation;
            tileMap[0][y][x]->position.x=x;
            tileMap[0][y][x]->position.y=y;



         }
         if(deltay!=0)
         {
             tileMap[0][mod((gridy-deltay),100)*100+a][(gridx+c)*100+b]=NULL;

             int x=mod((newGridy+c),width)*100+b;
             int y=mod((newGridy+deltay),height)*100+a;
             double elevation=finalTerrain.GetValue(x/width,y/height, 0.5);
             tileMap[0][y][x]=new tile(grass,0,findTileType(elevation));
             tileMap[0][y][x]->elevation=elevation;
             tileMap[0][y][x]->position.x=x;
             tileMap[0][y][x]->position.y=y;

         }
      }
      }


  }
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

