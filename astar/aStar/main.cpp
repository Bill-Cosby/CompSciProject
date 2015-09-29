#include <iostream>
#include "cat.h"

using namespace std;

int main()
{
    cat_ai cat;
    bool catSpot=false;
    bool test_map[20][20];
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            test_map[i][j]=0;
        }
    }
    while (true)
    {
        cat.decide(test_map);

//        for (int i=0;i<20;i++)
//        {
//            for (int j=0;j<20;j++)
//            {
//                if (cat.position.x==j and cat.position.x==i)
//                {
//                    std::cout << "C";
//                    catSpot=true;
//                }
//                else if (i==cat.bed.y && j==cat.bed.x)
//                {
//                    std::cout << "B";
//                }
//                else if (i==cat.food.y && j==cat.food.x)
//                {
//                    std::cout << "F";
//                }
//                else if (i==cat.litterBox.y && j==cat.litterBox.x)
//                {
//                    std::cout << "#";
//                }
//                else
//                {
//                    std::cout << ".";
//                }
//            }
//            catSpot=false;
//            std::cout << std::endl;
//        }
    }

}
