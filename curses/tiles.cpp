#include <iostream>
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
#include "generateCity.h"
#include "spring.h"

using namespace noise;
tiles::tiles()
{
    zoomIn=10;
    height=50;
    width=50;
    mesh=30;
    citiesNeeded=1;
    springsNeeded=200;
    srand(time(NULL));
    makeElevationMap();
    placeCitiesandSprings();
    fillMap();




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
    }
    updateTileMap(0,0);
}



void tiles::makeElevationMap()
{

    preLandTerrain1.SetFrequency(1);
    preLandTerrain1.SetSeed(rand());
    preLandTerrain1.SetOctaveCount(9);
    preLandTerrain1.SetPersistence(0.7);

    //preLandterrain1.SetFrequency(16);

    landTerrain1.SetSourceModule(0,preLandTerrain1);
    landTerrain1.SetBias(-0.1);


    preLandTerrain2.SetFrequency(2);
    preLandTerrain2.SetSeed(rand());


    landTerrain2.SetSourceModule(0,preLandTerrain2);
    landTerrain2.SetScale(1.2);
    landTerrain2.SetBias(-0.2);


    preOceanTerrain.SetFrequency(10);


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

int xstart=mesh*(centergridx-1);
int ystart=mesh*(centergridy-1);
int xend=mesh*(centergridx+2);
int yend=mesh*(centergridy+2);
  for(int a=0; a<3; a++)
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

            double elevation=finalTerrain.GetValue(x/(mesh*zoomIn), y/(mesh*zoomIn), 0.5);
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
      std::vector<spring*> someWhatLocalSprings;
      for(int z=0; z<springList.size(); z++)
      {
          if(xstart-100<springList[z]->x0 and ystart-100<springList[z]->y0 and xend+100>springList[z]->x0 and yend+100>springList[z]->y0)
          {
              someWhatLocalSprings.push_back(springList[z]);
          }
      }
     // std::cout<<"Somewhat local spring size "<<someWhatLocalSprings.size()<<" \n";
      for(int z=0; z<someWhatLocalSprings.size(); z++)
      {
            for(int m=0; m<someWhatLocalSprings[z]->wetTiles.size(); m++)
            {
                double x=someWhatLocalSprings[z]->wetTiles[m].x;
                double y=someWhatLocalSprings[z]->wetTiles[m].y;
                if(xstart<=x and ystart<=y and xend>x and yend>y)
                {
                    tileMap[0][y-ystart][x-xstart]=new tile(grass,0,"lightblue",x,y);

                }
            }
      }

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

          if(mesh*(centergridx-1)<=Left and Left<mesh*(centergridx+2))
            {
                leftCheck=true;
            }
          else if (mesh*(centergridx-1)<=Right and Right<mesh*(centergridx+2))
            {
              rightCheck=true;
            }
          if(mesh*(centergridy-1)<=Bottom and Bottom<mesh*(centergridy+2))
            {
              bottomCheck=true;
            }
          else if(mesh*(centergridy-1)<=Top and Top<mesh*(centergridy+2))
             {
                topCheck=true;
             }


             if((topCheck==true or bottomCheck==true) and (leftCheck==true or rightCheck==true))
             {
                 for(int w=Bottom; w<=Top; w++)
                 {
                     if(mesh*(centergridy-1)<=w and w<mesh*(centergridy+2))
                     {
                         for(int v=Left; v<=Right;v++)
                        {
                         if(mesh*(centergridx-1)<=v and v<mesh*(centergridx+2))
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

      /*for(int m=0; m<localItems.size(); m++)
      {
          if(mesh*(centrgridx-1)<=localItem[m].x and localItem[m].x<mesh*(centergridx+2) and mesh*(centrgridy-1)<=localItem[m].y and localItem[m].y<mesh*(centergridy+2))
          {
              tileMap[1][localItem[m].y-mesh*(centergridy-1)][localItem[m].x-mesh*(centergridx-1)]
          }
      }*/
  }




void tiles::placeCitiesandSprings()
{
int cityWidth=50;
int cityHeight=50;
    unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
     std::mt19937 generator(seed);
     std::uniform_int_distribution<int> chooseTestx(0,mesh*zoomIn-cityWidth);
     std::uniform_int_distribution<int> chooseTesty(0,mesh*zoomIn-cityHeight);
 int x;
 int y;
 bool goodSpotforCity;
 bool goodSpotforSpring;
 city* A;
 double elevationHere;
 int counter=0;
    for(int a=0, b=0; (a<citiesNeeded or b<springsNeeded) and counter<20000; counter++)
    {//
    x=chooseTestx(generator);
    y=chooseTesty(generator);
   // std::cout<<"X "<<x<<" Y "<<y<<" \n";
    goodSpotforCity=true;
    goodSpotforSpring=true;

elevationHere=finalTerrain.GetValue((x)/(mesh*zoomIn),(y)/(mesh*zoomIn), 0.5);
//std::cout<<"GrassBelow "<<grassBelow<< " elevationHere "<<elevationHere<<" \n" ;

      if(sandBelow-.02<elevationHere and b<springsNeeded)
      {
          goodSpotforSpring=true;
          b++;
          spring * S=new spring(x,y);
          makeSpring(S);
          springList.push_back(S);
      }

    else if(!occupiedByCity(x,y))
    {
     if(a<citiesNeeded)
      {
        for(double b=0; b<cityHeight; b++)
     {
        for(double c=0; c<cityWidth; c++)
        {
            elevationHere=finalTerrain.GetValue((x+c)/(mesh*zoomIn),(y+b)/(mesh*zoomIn), 0.5);

            if(sandBelow>=elevationHere or dirtBelow<=elevationHere)
             {
               goodSpotforCity=false;
               break;
             }
        }
        if(goodSpotforCity==false)
         {
            break;
         }
       }
     }

                if(goodSpotforCity==true)
                {
                  a++;
                  std::cout<<"City Made On "<<x<<", "<<y<<"\n";
                  A=new city(cityWidth,cityHeight,x,y);
                  cityList.push_back(A);
                }
    }
  }
}

bool tiles::occupiedByCity(int x,int y)
{
    for(int z=0; z<cityList.size(); z++)
    { //std::cout<<"X "<<cityList[z]->left<<" Y "<<cityList[z]->bottom<<" Z "<<z<<"\n";
        if(2*cityList[z]->x0-(cityList[z]->x0+cityList[z]->right)<=x and x<=cityList[z]->right+cityList[z]->x0 and 2*cityList[z]->y0-(cityList[z]->y0+cityList[z]->top)<=y and y<=cityList[z]->top+cityList[z]->y0)
        {
            return true;
        }
    }
    return false;
}

void tiles::makeSpring(spring * Spring)
{
    int x=Spring->x0;
    int y=Spring->y0;

std::cout<<"Spring made \n";

     std::vector<double> surroundingElevations;
    bool riverFlowing=true;
    for(int d=0;  d<50 and riverFlowing; d++)//
    {

    coordinate D0(x,y);
    coordinate D1(x+1,y);
    coordinate D2(x,y+1);
    coordinate D3(x-1,y);
    coordinate D4(x,y+1);
        surroundingElevations.push_back(finalTerrain.GetValue((D0.x)/(mesh*zoomIn),(D0.y)/(mesh*zoomIn), 0.5)+Spring->findHeight(D0));
        surroundingElevations.push_back(finalTerrain.GetValue((D1.x)/(mesh*zoomIn),(D1.y)/(mesh*zoomIn), 0.5)+Spring->findHeight(D1));
        surroundingElevations.push_back(finalTerrain.GetValue((D2.x)/(mesh*zoomIn),(D2.y)/(mesh*zoomIn), 0.5)+Spring->findHeight(D2));
        surroundingElevations.push_back(finalTerrain.GetValue((D3.x)/(mesh*zoomIn),(D3.y)/(mesh*zoomIn), 0.5)+Spring->findHeight(D3));
        surroundingElevations.push_back(finalTerrain.GetValue((D4.x)/(mesh*zoomIn),(D4.y)/(mesh*zoomIn), 0.5)+Spring->findHeight(D4));

        int temp;
        int k=0;
        int R;
        std::vector<int> tileOrder;
        bool H=true;
        for(int e=0; e<5; e++)
        {
           tileOrder.push_back(e);
        }

        for(int f=0; f<4; f++)
        {
            H=false;
        for(int b=0; b<tileOrder.size()-1-f; b++)
          {
            if(surroundingElevations[tileOrder[b]]>surroundingElevations[tileOrder[b+1]])
            {
                temp=tileOrder[b];
                tileOrder[b]=tileOrder[b+1];
                tileOrder[b+1]=temp;
                H=true;
            }

          }

        }

        R=rand()%1000;
        if(R<=800)
        {
            k=tileOrder[0];
        }
        else if (R<=940)
        {
            k=tileOrder[1];
        }
         else
        {
            k=tileOrder[2];
        }


        if(k==0) { x=D0.x; y=D0.y; Spring->wetTileHeights.push_back(Spring->findHeight(D0)+.01); Spring->wetTiles.push_back(D0);}
        if(k==1) { x=D1.x; y=D1.y; Spring->wetTileHeights.push_back(Spring->findHeight(D1)+.01); Spring->wetTiles.push_back(D1);}
        if(k==2) { x=D2.x; y=D2.y; Spring->wetTileHeights.push_back(Spring->findHeight(D2)+.01); Spring->wetTiles.push_back(D2);}
        if(k==3) { x=D3.x; y=D3.y; Spring->wetTileHeights.push_back(Spring->findHeight(D3)+.01); Spring->wetTiles.push_back(D3);}
        if(k==4) { x=D4.x; y=D4.y; Spring->wetTileHeights.push_back(Spring->findHeight(D4)+.01); Spring->wetTiles.push_back(D4);}

        if(surroundingElevations[k]<waterBelow)//or(0==tileOrder[0] and 1==tileOrder[1])
        {
           riverFlowing=false;
        }

surroundingElevations.clear();
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






