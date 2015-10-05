#include <iostream>
#include <random>
#include <time.h>
#include "statelessAI.h"


using namespace std;

int main()
{
    firstAi test;
    std::default_random_engine engine(time(NULL));
    std::uniform_int_distribution<int> distributor(1,10);
    bool test_map[20][20];
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            int temp=distributor(engine);
            if (temp<3 )
            {
                test_map[i][j]=1;
            }
            else
            {
                test_map[i][j]=0;
            }
        }
    }


    while (true){
        for (int i=0;i<20;i++)
        {
            for (int j=0;j<20;j++)
            {
                bool nice=false;
                bool nicenice=false;
                if (test.position.x==i and test.position.y==j)
                {
                    std::cout << "@";
                    nice=true;
                }
                for (int h=0;h<test.aiPath.size();h++)
                {
                    if (test.aiPath[h].y==j and test.aiPath[h].x==i and nice==false)
                    {
                        std::cout << "*";
                        nicenice=true;
                    }
                }
                if (nice==false and nicenice==false)
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
            }
            std::cout << endl;
        }
        std::cout << endl;
        test.decide(test_map);
    }

}
