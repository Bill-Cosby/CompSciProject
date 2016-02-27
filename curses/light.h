#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#include "shadowcasting.h"

class lightSource : public tile
{
public:
    float intensity;
    float decreaseBy;

    void renderLight(){
        intensity = rand()%21;
        intensity+=80;
        intensity/=100;
    }
};

#endif // LIGHT_H_INCLUDED
