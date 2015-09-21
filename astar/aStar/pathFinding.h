#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED
#include <vector>
#include "searchCell.h"
class Vector3
{
public:
    int x,y,z;
};

class pathFinding
{
public:
    pathFinding(void);
    ~pathFinding(void);

    void FindPath(Vector3 currentPos, Vector3 targetPos);
    Vector3 NextPathPos();
    void ClearOpenList() { m_openList.clear(); }
    void ClearVisitedList() { m_visitedList.clear(); }
    void ClearPathToGoal() { m_pathToGoal.clear(); }
    bool m_initializedStartGoal;
    bool m_foundGoal;

private:
    void SetStartAndGoal(searchCell start, searchCell goal);
    void pathOpened(int x, int y, float newCost, searchCell *parent);
    searchCell *getNextCell();
    void continuePath();

    searchCell *m_startCell;
    searchCell *m_goalCell;
    std::vector<searchCell*> m_openList;
    std::vector<searchCell*> m_visitedList;
    std::vector<Vector3*>m_pathToGoal;
};

#endif // PATHFINDING_H_INCLUDED
