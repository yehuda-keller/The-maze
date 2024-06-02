#include "Const.h"
#include <list>
#include "Graph.h"
#include <utility>
#include <iostream>
//-----------------costructor---------------
// Constructs a Graph object with the specified number of vertices.
 // v The number of vertices in the graph.
 
Graph::Graph(int v)
{
    m_v = v;
    m_adj.resize(v);
    m_visited.resize(v, false);
    m_dadAndSon.resize(m_adj.size());

}
//-----------------clearEdge---------------
// Clears all the edges in the graph.
void Graph::clearEdge() {

    m_adj.clear();
    m_adj.resize(m_v);
    m_visited.clear();
    m_visited.resize(m_v, false);


}
//-----------------resetGrph----------------
//Resets the graph by clearing the dadAndSon vector.
void Graph::resetGraph() {

    m_dadAndSon.clear();

}
//-----------------addEdge---------------
//Adds an edge between two vertices in the graph.
// v The source vertex.
// w The target vertex.
void Graph::addEdge(int v, int w){

    m_adj[v].push_back(w); // Add w to v’s list.
}
//---------------BFS------------------
//Performs Depth-First Search (DFS) on the graph starting from a given node.

void Graph::DFS(int currentNode, const int& target,bool & found){

    m_visited[currentNode] = true;// Marks the current node as visited

    for (auto it = m_adj[currentNode].begin(); it != m_adj[currentNode].end() && !found; it++) {
        if (!m_visited[*it]) {
            m_dadAndSon.push_back(make_pair(currentNode, *it));
            if (target == *it)
                found = true;
            else DFS(*it, target, found);
        }
    }
}
//---------------getTrack------------------
//Retrieves the track (path) from the DFS traversal
vector<int> Graph::getTrack() {
    
    vector<int> track;
    track.clear();

    int i = m_dadAndSon.size() - 1;

    while (true)
    {
        if (i == 0) {
            track.push_back(m_dadAndSon[i].second);
            return track;
        }
        
        else {
            //search for the father of current son 
            for (size_t cell = 0; cell < m_dadAndSon.size() - 1; cell++) 
                if (m_dadAndSon[i].first == m_dadAndSon[cell].second) {
                    track.push_back(m_dadAndSon[i].first);
                    i = cell;
                    break;
                }
        }
    }
    return track;
}