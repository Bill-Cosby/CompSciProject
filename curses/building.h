#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>

class building
{
public:
    std::string name;
    std::vector<std::vector<int> > structure;
    void buildStructure();
};

#endif // BUILDING_H_INCLUDED
