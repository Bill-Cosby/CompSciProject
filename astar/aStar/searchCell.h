#ifndef SEARCHCELL_H_INCLUDED
#define SEARCHCELL_H_INCLUDED

#include <math.h>

struct searchCell
{
public:
    int m_xcoord, m_ycoord;
    int m_id;
    searchCell *parent;
    float G;
    float H;

    searchCell() : parent(0) {}
    searchCell(int,int,searchCell *_parent = 0) : m_xcoord(x), m_ycoord(y),
    parent(_parent), m_id(y * WORLD_SIZE + x), G(0), H(0) {};

    float GetF() {return G+H;}
    float manhattanDistance(searchCell *nodeEnd)
    {
        float x = (float)(fabs(this->m_xcoord - nodeEnd->m_xcoord));
        float y = (float)(fabs(this->m_xcoord - nodeEnd->m_xcoord));
        return x + y;
    }
};

#endif // SEARCHCELL_H_INCLUDED
