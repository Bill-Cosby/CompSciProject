#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <random>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <fstream>
#include "../window.h"
#include "../micropather.h"

class dungeon : public micropather::Graph
{
private:
    micropather::MicroPather* pather;
    coordinate directions[4]={coordinate(0,-1),coordinate(1,0),coordinate(0,1),coordinate(-1,0)};
    int w,h;
public:
    coordinate mazeBegin;
    std::vector<std::vector<bool> > dungeon_grid;
    dungeon();
    void hallwayMaker();
    int Passable(int,int);


    //=======MICROPATHER THINGS===========

    void NodeToXY( void* node, int* x, int* y )
	{
		intptr_t index = (intptr_t)node;
		*y = index / w;
		*x = index - *y * w;
	}

	void* XYToNode( int x, int y )
	{
		return (void*) ( y*w + x );
	}


	virtual float LeastCostEstimate( void* nodeStart, void* nodeEnd )
	{
		int xStart, yStart, xEnd, yEnd;
		NodeToXY( nodeStart, &xStart, &yStart );
		NodeToXY( nodeEnd, &xEnd, &yEnd );

		/* Compute the minimum path cost using distance measurement. It is possible
		   to compute the exact minimum path using the fact that you can move only
		   on a straight line or on a diagonal, and this will yield a better result.
		*/
		int dx = xStart - xEnd;
		int dy = yStart - yEnd;
		return (float) sqrt( (double)(dx*dx) + (double)(dy*dy) );
	}

	virtual void AdjacentCost( void* node, micropather::MPVector< micropather::StateCost > *neighbors )
	{
		int x, y;
		const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
		const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
		const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };

		NodeToXY( node, &x, &y );

		for( int i=0; i<8; ++i ) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			int pass = Passable( nx, ny );
			if ( pass > 0 ) {
				if ( pass == 1 )
				{
					// Normal floor
					micropather::StateCost nodeCost = { XYToNode( nx, ny ), cost[i] };
					neighbors->push_back( nodeCost );
				}
				else
				{
					// Normal floor
					micropather::StateCost nodeCost = { XYToNode( nx, ny ), FLT_MAX };
					neighbors->push_back( nodeCost );
				}
			}
		}
	}
};


#endif // DUNGEON_H_INCLUDED
