#include "cat.h"
cat_ai::cat_ai()
{
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> statFiller(20,100);
    std::uniform_int_distribution<int> statLimiter(20,50);
    hunger=statFiller(generator);
    sleep=statFiller(generator);
    poop=statFiller(generator);
    hungerLimit=statLimiter(generator);
    sleepLimit=statLimiter(generator);
    poopLimit=statLimiter(generator);
    position=coordinate(10,10);
}

void cat_ai::decide(bool test_map[20][20])
{
    if (hunger<hungerLimit)
    {
        path=pathFinder(test_map, position, food);
    }
    else if (sleep<sleepLimit)
    {
        path=pathFinder(test_map, position, bed);
    }
    else if (poop < poopLimit)
    {
        path=pathFinder(test_map,position,litterBox);
    }
    else
    {
        path.clear();
        hunger--;
        sleep--;
        poop--;
    }
    catMove();
}

void cat_ai::catMove()
{
    if (path.size()>0)
    {
        position=path[0];
    }
}
