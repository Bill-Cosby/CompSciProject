class city: box
{
vector <road *> roads;

city(){left=0; bottom=0; right=50; top=50; }
makeCity();
drawCity();
}

void city::makeCity()
 {
      for(int a=0; a<roads.size(); a++)
      {
          road[a]->drawRoad();
      }
  }

void city::createCity()
{
divideBox(3);
drawGameWorld();
}

class box
{
box{blank.resize(2)};
box * subBox1;
box * subBox2;
double right;
double left;
double bottom;
double top;
vector<coordinate *> blank;
divideBox();
};

void divideBox(int level)
{
  if(level!=0)
  {

    if(uniform_int_distribution(0,1)==0) //if line vertical
    {
        width=right-left;
        uniform_real_distribution<double>(left+width/10, right+width/10) splitPoint;
        coordinate lowPoint(bottom, splitPoint);
        coordinate highPoint(top, splitPoint);
       tempRoad=new road;
        tempRoad->vertical=true;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete bottomPoint;
        delete topPoint;

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint;
        subBox1->top=top;
        subBox1->bottom;
        subBox2->left=splitPoint;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

    }

    else
    {
        height=top-bottom;
        uniform_real_distribution<double>(bottom+height/10, top-height/10) splitPoint;
        coordinate leftPoint(splitPoint, left);
        coordinate rightPoint(splitPoint, right);

        tempRoad=new road;
        tempRoad->vertical=false;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete leftPoint
        delete rightPoint;


        box1=new box;
        box2=new box;

        box1->left=left;
        box1->right=right;
        box1->top=top;
        box1->splitPoint;
        box2->left=left;
        box2->right=right;
        box2->top=splitPoint;
        box2->bottom=bottom;  //forms
    }

    box1->myCity=myCity;
    box2->myCity=myCity
    level-=1;
    box1->divideBox(level);
    box2->divideBox(level);
    delete box1;
    delete box2;

  }
}



class road
{
coordinate * Point1;
coordinate * Point2;
int size;
bool vertical;
makeRoad();
};

makeRoad()
{
 if(vertical==true)
 {
  for(int a=0; a<=Point2->y-Point1->y; a++)
  {
   tileMap(Point1->x,Point2->y+a)
  }
  }
  
  if(vertical==false)
 {
  for(int a=0; a<Point2->x-Point1->; a++)
  {
   changeat(Point1->x+a,Point2->y);
  }
  }
 
 
}





#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>

class city
{
    city();

    void generateCity();
    void makeRoad();
    void drawLine();

    vector<box>;



};

city()
{
    vector<new box;
}

void city:makeRoad()
{
    bool vertical;
    if(uniform_real_distribution<double> coinToss(0,1)<.5)
    {
        vertical=true;
    }
    else
    {
        vertical=false;
    }
    if(vertical==true)
    {uniform_real_distribution<double> (boxx.left, boxx.right);
    }
    else
        {

        }
}

void city::drawLine()
{

}

class box
{
public:
    coordinate topRightCorner;
    coordinate bottomRightCorner;
    coordinate bottomLeftCorner;
    coordinate topLeftCorner;

};

void generateCity(std::vector<std::vector<tile*> > *_map, bool vertical, int numberOfRoads, coordinate startingPosition, int numberOfIterations)
{


    int beginning,goTo;
    std::mt19937 generator(time(NULL));
    std::uniform_real_distribution<int> locationOnMap(1,_map->size());
    std::uniform_real_distribution<int> numberOfRoadsToMake(1,5);
    std::uniform_real_distribution<int> coinToss(0,100);

    if (numberOfIterations==0){
        return;
    }


        generateCity(_map,false, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations);
    }
    for (int * R = new int(0); *R < numberOfRoads; *R++){
        if (vertical==false){
        if (coinToss(generator)<50){
            std::uniform_int_distribution<int> positionOfNewRoad(1,startingPosition.y);
            startingPosition.y=positionOfNewRoad(generator);
            for (int i=startingPosition.x;i>0;i--){
                (*_map)[startingPosition.y][i] = new tile('.',0,stone);
            }
        }
        else{
            std::uniform_int_distribution<int> positionOfNewRoad(startingPosition.y,_map->size());
            startingPosition.y=positionOfNewRoad(generator);
            for (int i=startingPosition.x;i<_map->size();i++){
                (*_map)[startingPosition.y][i] = new tile('.',0,stone);
            }
        }
        generateCity(_map,1-verticle, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations-1);
    }
    else{
        if (coinToss(generator)<50){
            std::uniform_int_distribution<int> positionOfNewRoad(1,startingPosition.x);
            startingPosition.x=positionOfNewRoad(generator);
            for (int i=startingPosition.y;i>0;i--){
                (*_map)[i][startingPosition.x] = new tile('.',0,stone);
            }
        }
        else{
            std::uniform_int_distribution<int> positionOfNewRoad(startingPosition.x,_map->size());
            startingPosition.x=positionOfNewRoad(generator);
            for (int i=startingPosition.y;i<_map->size();i++){
                (*_map)[i][startingPosition.x] = new tile('.',0,stone);
            }
        }
        generateCity(_map,1-verticle, numberOfRoadsToMake(generator), false,startingPosition,numberOfIterations-1);
    }
    }
*/
    return;
}

#endif // GENERATECITY_H_INCLUDED
