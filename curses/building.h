#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>
#include "tile.h"

class building
{
public:
    int height,width;
    std::string name;
    std::vector<std::vector<tile*> > structure;
    void buildStructure(std::string);
};

#endif // BUILDING_H_INCLUDED
