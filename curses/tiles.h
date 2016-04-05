#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "tile.h"
#include <noise/noise.h>
#include "noiseutils.h"

class tiles
    {
        public:
        std::vector<std::vector<tile*> > tileMap;
        int height;
        int width;
        tiles();

        void fillMap();
        void makeTileMap();
        std::string findTileType(double elevation);
    };


#endif //TILES_H_INCLUDE
