#include "dungeon.h"
#pragma once
#ifndef PERLINNOISE_H_INCLUDED
#define PERLINNOISE_H_INCLUDED
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
class perlinNoise
{

    vector<double> blank1;
    vector<vector<double> > shade;
    vector<vector<vector<double> > > blank3;
    vector<vector<double> > blank2;
    vector<double> coordinate;

    vector<vector<vector<vector<double> > > > gradients;

    double dot_product(vector<double>,vector<double>);
    double ease(double);
    double perlin_noise(vector<double>, vector<double>, vector<double>, vector<double>, vector<double>);

    public:
    void callPerlin();
    vector<vector<double> > perlin_noise_sum;
};



#endif // PERLINNOISE_H_INCLUDED
