#include "pathFinding.h"

pathFinding::pathFinding(void)
{
    m_initializedStartGoal=false;
    m_foundGoal=false;
}
pathFinding::~pathFinding(void)
{
}
void pathFinding::FindPath(Vector3 currentPos, Vector3 targetPos)
{
    if (!m_initializedStartGoal)
    {
        for (int i=0;i<m_openList.size();i++)
        {
            delete m_openList[i];
        }
        m_openList.clear();

        for (int i=0;i<m_visitedList.size();i++)
        {
            delete m_visitedList[i];
        }
        m_visitedList.clear();
        for (int i=0;i<m_pathToGoal.size();i++)
        {
            delete m_pathToGoal[i];
        }
        m_pathToGoal.clear();

        //initialize start
        searchCell start;
        start.m_xcoord = currentPos.x;
        start.m_ycoord = currentPos.y;

        //initialize goal
        searchCell goal;
        goal.m_xcoord = targetPos.x;
        goal.m_ycoord = targetPos.y;

        SetStartAndGoal(start,goal);
        m_initializedStartGoal=true;
    }
    if (m_initializedStartGoal)
    {
        continuePath();
    }
}

void pathFinding::SetStartAndGoal(searchCell start, searchCell goal)
{
    m_startCell = new searchCell(start.m_xcoord, start.m_ycoord, 0);
    m_goalCell = new searchCell(goal.m_xcoord, goal.m_ycoord, &goal);

    m_startCell->G = 0;
    m_startCell->H = m_startCell->manhattanDistance(m_goalCell);
    m_startCell->parent = 0;

    m_openList.push_back(m_startCell);
}

searchCell* pathFinding::getNextCell()
{
    float bestF = 999999.0f;
    int cellIndex = -1;
    searchCell* nextCell = 0;

    for (int i=0;i<m_openList.size();i++)
    {
        if (m_openList[i]->GetF() < bestF)
        {
            bestF = m_openList[i]->GetF();
            cellIndex=i;
        }
    }

    if (cellIndex >= 0)
    {
        nextCell = m_openList[cellIndex];
        m_visitedList.push_back(nextCell);
        m_openList.erase(m_openlist.begin() + cellIndex);
    }

    return nextCell;
}

void pathFinding::pathOpened(int x, int y, float newCost, searchCell *parent)
{
//    if (CELL_BLOCKED)
//    {
//        return;
//    }

    int id = y * WORLD_SIZE + x;
    for (int i=0;i<m_visitedList.size();i++)
    {
        if (id==m_visitedList[i]->m_id)
        {
            return;
        }
    }

    searchCell* newChild = new searchCell(x,y, parent);
    newChild->G = newCost;
    newChild->H = parent->manhattanDistance(m_goalCell);

    for (int i = 0; i < m_openList.size(); i++)
    {
        if (id == m_openList[i]->m_id)
        {
            float newF = newChild->G + newCost + m_openList[i]->H;

            if (m_openList[i]->GetF() > newF)
            {
                m_openList[i]->G = newChild->G + newCost;
                m_openList[i]->parent = newChild;
            }
            else //if the f is not better
            {
                delete newChild;
                return;
            }
        }
    }

    m_openList.push_back(newChild);
}

void pathFinding::continuePath()
{
    if (m_openList.empty())
    {
        return;
    }

    searchCell* currentCell = getNextCell();

    if (currentCell->m_id == m_goalCell->m_id)
    {
        m_goalCell->parent = currentCell->parent;

        searchCell* getPath;

        for (getPath = m_goalCell; getPath != 0; getPath = getPath->parent)
        {
            m_pathToGoal.push_back(new Vector3(getPath->m_xcoord, getPath->m_ycoord, 0));
        }

        m_foundGoal = true;
        return;
    }

    else
    {
        //rightCell
        pathOpened(currentCell->m_xcoord + 1, currentCell->m_ycoord, currentCell->G+1, currentCell);
        //leftCell
        pathOpened(currentCell->m_xcoord - 1, currentCell->m_ycoord, currentCell->G+1, currentCell);
        pathOpened(currentCell->m_xcoord, currentCell->m_ycoord + 1, currentCell->G+1, currentCell);
        pathOpened(currentCell->m_xcoord, currentCell->m_ycoord - 1, currentCell->G+1, currentCell);

        for (int i=0;i<m_openList.size();i++)
        {
            if (currentCell->m_id == m_openList[i]->m_id)
            {
                m_openList.erase(m_openList.begin() + i);
            }
        }
    }
}

Vector3 pathFinding::NextPathPos()
{
    int index = 1;

    Vector3 nextPos;
    nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
    nextPos.y = m_pathToGoal[m_pathToGoal.size() - index]->y;

    Vector3 distance = nextPos - pos;

    if (index < m_pathToGoal.size())
    {
        if (distance.length() < radius)
        {
            m_pathToGoal.erase(m_pathToGoal.end()-index);
        }
    }

    return nextPos;
}
