#ifndef STATELESSAI_H_INCLUDED
#define STATELESSAI_H_INCLUDED
#include "aStar.h"

class firstAi
{
public:
    std::vector<coordinate> aiPath;
    coordinate position;
    coordinate food;
    coordinate shit;
    coordinate goal;
    int hunger,pooper;
    int placeInPath;
    firstAi();
    void decide(bool[][20]);
};

#endif // STATELESSAI_H_INCLUDED
