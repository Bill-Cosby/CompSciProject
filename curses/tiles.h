#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "tile.h"
#include <noise.h>
#include "noiseutils.h"

class tiles
    {
        public:
        std::vector<std::vector<tile*> > tileMap;
        int height;
        int width;
        tiles();

        void fillMap();
        void setPositions();
        void makeTileMap();
        void setColors();


    };


#endif //TILES_H_INCLUDE
