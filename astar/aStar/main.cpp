#include <iostream>
#include <random>
#include <time.h>
#include "aStar.h"


using namespace std;

int main()
{

    std::default_random_engine engine(time(NULL));
    std::uniform_int_distribution<int> distributor(1,10);
    bool test_map[20][20];
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            int temp=distributor(engine);
            if (temp>10)
            {
                test_map[i][j]=1;
            }
            else
            {
                test_map[i][j]=0;
            }
        }
    }
    std::vector<coordinate> foundPath=pathFinder(test_map,coordinate(0,0),coordinate(19,19));
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            bool nice=false;
            for (int k=0;k<foundPath.size();k++)
            {
                //std::cout << foundPath[k].x << "," <<foundPath[k].y << std::endl;
                if (foundPath[k].x==i&&foundPath[k].y==j)
                {
                    nice=true;
                }
            }
            if (nice==false)
            {
                if (test_map[i][j]==true)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
                nice=false;
            }
            else
            {
                //std::cout << "p";
            }
        }
        std::cout << endl;
    }
}
