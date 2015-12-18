#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
class tiles
    {
        public:
        int height;
        int width;
        tiles();
        void makeTileMap();
        std::vector<std::vector<tile> > tileMap;
    };


#endif //TILES_H_INCLUDE
