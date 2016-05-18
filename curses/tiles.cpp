#include <iostream>
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
#include "generateCity.h"

using namespace noise;
tiles::tiles()
{
    zoomOut=1;
    height=10;
    width=10;
    mesh=30;
    citiesNeeded=5;
    makeElevationMap();
    fillMap();
    placeCities();


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

        tileMap[0].resize(3*mesh);
        tileMap[1].resize(3*mesh);
        for(double b=0; b<tileMap[0].size(); b++)
    {
        tileMap[0][b].resize(3*mesh);
        tileMap[1][b].resize(3*mesh);
        for(double c=0; c<tileMap[0][b].size(); c++)
        {
            double x=c-mesh;
            double y=b-mesh;
            double elevation=finalTerrain.GetValue(x*zoomOut/(width*mesh), y*zoomOut/(height*mesh), 0.5);
            tileMap[0][b][c]=new tile(grass,0,findTileType(elevation),x,y);
            tileMap[0][b][c]->elevation=elevation;
            tileMap[0][b][c]->position.y=b-mesh;
            tileMap[0][b][c]->position.x=c-mesh;
            tileMap[1][b][c]=new tile;
            tileMap[1][b][c]->position.y=b-mesh;
            tileMap[1][b][c]->position.x=c-mesh;
        }
    }
}



void tiles::makeElevationMap()
{
srand(time(NULL));

    preLandTerrain1.SetFrequency(1);
    preLandTerrain1.SetSeed(rand());


    landTerrain1.SetSourceModule(0,preLandTerrain1);
    landTerrain1.SetBias(-0.1);


    preLandTerrain2.SetFrequency(2);
    preLandTerrain2.SetSeed(rand());


    landTerrain2.SetSourceModule(0,preLandTerrain2);
    landTerrain2.SetScale(1.2);
    landTerrain2.SetBias(-0.2);


    preOceanTerrain.SetFrequency(32);


    oceanTerrain.SetSourceModule(0,preOceanTerrain);
    oceanTerrain.SetScale(1.2);
    oceanTerrain.SetBias(-0.2);


    finalTerrain_.SetSourceModule(0,oceanTerrain);
    finalTerrain_.SetSourceModule(1,landTerrain1);
    finalTerrain_.SetControlModule(landTerrain2);
    finalTerrain_.SetBounds(-100.0,-.7);


    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    finalTerrain.SetBounds(-0.7,100);
    finalTerrain.SetEdgeFalloff(0.5);
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
    sets elevations*/
}


std::string tiles::findTileType(double elevation)
{
    if(elevation<darkWaterBelow)
    {
        return "darkWater";
    }
    else if(elevation<waterBelow)
    {
      return "water";

    }
    else if(elevation<sandBelow)
    {
        return "sand";
    }
    else if(elevation<grassBelow)
    {
        return "grass";
    }
    else if(elevation<dirtBelow)
    {
        return "dirt";
    }
    else if(elevation<rockBelow)
    {
        return "stone";
    }
    else
    {
        return "white";//snow
    }
}
void tiles::updateTileMap(int centergridx, int centergridy)
{

  for(signed int a=0; a<3; a++)
  {
    for(int b=0; b<3; b++)
      {
      for(int c=0; c<mesh; c++)
      {
        for(int d=0; d<mesh; d++)
          {
double p=a*mesh+c;
double q=b*mesh+d;

            double x=mesh*(centergridx-1+a)+c;
            double y=mesh*(centergridy-1+b)+d;

            double elevation=finalTerrain.GetValue(x*zoomOut/(width*mesh), y*zoomOut/(height*mesh), 0.5);
            tileMap[0][q][p]=new tile(grass,0,findTileType(elevation),x,y);
            tileMap[0][q][p]->elevation=elevation;
            tileMap[0][q][p]->position.x=x;
            tileMap[0][q][p]->position.y=y;

            tileMap[1][q][p]=new tile;
            tileMap[1][q][p]->position.x=x;
            tileMap[1][q][p]->position.y=y;
         }

      }
      }
      }

      bool leftCheck;
      bool bottomCheck;
      bool rightCheck;
      bool topCheck;
      for(int z=0; z<cityList.size(); z++)
      {
            leftCheck=false;
            bottomCheck=false;
            rightCheck=false;
            topCheck=false;
            int Left=cityList[z]->left+cityList[z]->x0;
            int Right=cityList[z]->right+cityList[z]->x0;
            int Bottom=cityList[z]->bottom+cityList[z]->y0;
            int Top=cityList[z]->top+cityList[z]->y0;

          if(mesh*(centergridx-1)<=Left and Left<mesh*(centergridx+1))
            {
                leftCheck=true;
            }
          else if (mesh*(centergridx-1)<=Right and Right<mesh*(centergridx+1))
            {
              rightCheck=true;
            }
          if(mesh*(centergridy-1)<=Bottom and Bottom<mesh*(centergridy+1))
            {
              bottomCheck=true;
            }
          else if(mesh*(centergridy-1)<=Top and Top<mesh*(centergridy+1))
             {
                topCheck=true;
             }


             if((topCheck==true and leftCheck==true) or(topCheck==true and rightCheck==true) or (bottomCheck==true and leftCheck==true) or (bottomCheck and rightCheck==true))
             {
std::cout<<"DDDDDDDDD \n";
                 for(int w=Bottom; w<=Top; w++)
                 {
                     if(mesh*(centergridy-1)<=w and w<mesh*(centergridy+1))
                     {
                         for(int v=Left; v<=Right;v++)
                        {
                         if(mesh*(centergridx-1)<=v and v<mesh*(centergridx+1))
                         {
                             tileMap[0][w-(centergridy-1)*mesh][v-(centergridx-1)*mesh]=cityList[z]->tileMap[0][w-Bottom][v-Left];
                             tileMap[0][w-(centergridy-1)*mesh][v-(centergridx-1)*mesh]->position=coordinate(v,w);
                             tileMap[1][w-(centergridy-1)*mesh][v-(centergridx-1)*mesh]=cityList[z]->tileMap[1][w-Bottom][v-Left];
                             tileMap[1][w-(centergridy-1)*mesh][v-(centergridx-1)*mesh]->position=coordinate(v,w);
                         }
                        }
                     }

                 }
             }
      }
  }




void tiles::placeCities()
{
int cityWidth=50;
int cityHeight=50;
    unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
     std::mt19937 generator(seed);
     std::uniform_int_distribution<int> chooseTestx(0,mesh*width-cityWidth);
     std::uniform_int_distribution<int> chooseTesty(0,mesh*height-cityHeight);
 int x;
 int y;
 bool goodSpot;
 city* A;
 double elevationHere;
 int counter=0;
    for(int a=0; a<citiesNeeded and counter<50000*citiesNeeded;counter++)
    {
    x=chooseTestx(generator);
    y=chooseTesty(generator);
    goodSpot=true;
    for(double b=0; b<cityHeight; b++)
    {
        for(double c=0; c<cityWidth; c++)
        {
            elevationHere=finalTerrain.GetValue(zoomOut*(x+c)/(mesh*width),zoomOut*(y+b)/(mesh*height), 0.5);
           if(false)//sandBelow>=elevationHere or dirtBelow<=elevationHere or tileMap[0][b][c]->isCity==true
           {
               goodSpot=false;
               break;
           }
        }
        if(goodSpot==false)
        {
            break;
        }
    }
              if(goodSpot==true)
              {
                  a++;
                  std::cout<<"City Made On "<<x<<", "<<y<<"\n";
                  A=new city(cityWidth, cityHeight,x,y);
                  cityList.push_back(A);


              }
    }
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


   /* module::Turbulence turbulence;
    turbulence.SetSourceModule(0,turbulence);
    turbulence.SetFrequency(4.0);
    turbulence.SetPower(0.125);
*/






