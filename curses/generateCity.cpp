#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <random>
#include <vector>


void city:: setTileMap(std::vector<std::vector<tile*> > & tileMap)
{
    std::vector<tile*> blank1;
    blank1.resize(50);
    tileMap.resize(50);
  for(int a=0; a<50; a++)
    {
        tileMap[a]=blank1;
        for(int b=0; b<50; b++)
        {
            tileMap[a][b]=new tile('0',10,grass);
            tileMap[a][b]->position = coordinate(a,b);
            tileMap[a][b]->sprite.setPosition(a*16,b*16);
            tileMap[a][b]->isDoor = false;
        }
    }

}


void city:: deleteTileMap(std::vector<std::vector<tile*> > & tileMap)
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap.size(); b++)
        {
            delete tileMap[a][b];
        }
    }
}

void box::makeRoad(road* myRoad, std::vector<std::vector<tile*> > & tileMap)
{
 if(myRoad->vertical==true)
 {
  for(int a=0; a<=5; a++)//myRoad->Point2->y-myRoad->Point1->y
  {

   tileMap[5+a][10]=new tile('1',10,stone);//myRoad->Point1->y+a//myRoad->Point1->x
  }
 }

  if(myRoad->vertical==false)
  {
  for(int a=0; a<=5; a++)//myRoad->Point2->x-myRoad->Point1->x
   {
   tileMap[10][5+a]=new tile('1',10,stone);//myRoad->Point1->y//myRoad->Point1->x+a

   }
  }


}


void box::divideBox(int level, std::vector<std::vector<tile*> > & tileMap)
{
  if(level!=0)
  {
std::default_random_engine generator;
std::uniform_int_distribution<int> halfChance(0,1);
    if(halfChance(generator)==0) //if line vertical
    {
        double width=(right-left);
        std:: uniform_int_distribution<int> findSplitPoint(left+width/10, right-width/10);
        int splitPoint=findSplitPoint(generator);
        coordinate lowPoint(bottom, splitPoint);
        coordinate highPoint(top, splitPoint);
        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;
        makeRoad(&tempRoad, tileMap); //draws road on tile map

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
    {//line horizontal
        double height=top-bottom;
        std::uniform_real_distribution<double> findSplitPoint(bottom+height/10, top-height/10);
        int splitPoint=findSplitPoint(generator);
        coordinate leftPoint(splitPoint, left);
        coordinate rightPoint(splitPoint, right);

        road * tempRoad;
        tempRoad=new road;
        tempRoad->vertical=false;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        makeRoad(tempRoad, tileMap); //draws road on tileMap
        delete tempRoad;

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top;
        subBox1->bottom=splitPoint;
        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint;
        subBox1->bottom=bottom;  //forms 2 new boxes
    }

    level-=1;
    subBox1->divideBox(level, tileMap);
    subBox2->divideBox(level, tileMap);
    delete subBox1;
    delete subBox2;

  }

}

  void city::generateCity(std:: vector<actor*> & actors,std::vector<item*> & localItems, sf::RenderWindow & window, announcements & Announcements)
{

std::vector<std::vector<tile*> > tileMap;
setTileMap(tileMap);
divideBox(3,tileMap); //recursive box dividing and road drawing
while(window.isOpen())
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type==sf::Event::Closed)
        {
        window.close();
        }
    }
    window.clear();

 drawGameworld(tileMap,actors,localItems, window, Announcements);
}
deleteTileMap(tileMap);
}



