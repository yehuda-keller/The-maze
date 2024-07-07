#pragma once
#include <list>
#include "Const.h"

class Graph
{
public:
    Graph                   (int);
    ~Graph                  () = default;
    void addEdge            (int v, int w);
    void resetGraph         ();
    void clearEdge          ();
    void DFS                (int currentNode, const int& target, bool& found);
    vector<int> getTrack    ();

private:
    //---------------------private members--------------------------

    vector < pair<int, int>>        m_dadAndSon;
    vector<int>                     m_visited;
    int                             m_v;
    vector<list<int>>               m_adj;

};


