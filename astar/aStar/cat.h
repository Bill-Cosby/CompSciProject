#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED
#include "aStar.h"
#include <time.h>
#include <random>

class cat_ai
{
    std::vector<coordinate> path;
public:
    coordinate food = coordinate(0,15);
    coordinate litterBox= coordinate(2,6);
    coordinate bed = coordinate(19,19);
    int hungerLimit, poopLimit, sleepLimit;
    int hunger, poop, sleep;

    coordinate position;

    cat_ai();
    void decide(bool[][20]);
    void catMove();
};

#endif // CAT_H_INCLUDED
