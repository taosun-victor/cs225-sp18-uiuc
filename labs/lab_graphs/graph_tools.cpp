/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <iostream>
#include <functional>
#include "graph.h"
#include "graph_tools.h"
#include "dsets.h"

using namespace std;

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> Vertices = graph.getVertices();
    vector<Edge> Edges = graph.getEdges();
    Vertex tmp_v;
    Edge tmp_e;

    for (unsigned i=0; i<Vertices.size(); i++)
        tmp_v = graph.setVertexLabel(Vertices[i], "UNEXPLORED");
    for (unsigned i=0; i<Edges.size(); i++)
        tmp_e = graph.setEdgeLabel(Edges[i].source, Edges[i].dest, "UNEXPLORED");

    int min_weight = 1000000000;
    Vertex min_source;
    Vertex min_dest;

    for (unsigned i=0; i<Vertices.size(); i++){
       if (graph.getVertexLabel(Vertices[i]) == "UNEXPLORED"){
           queue<Vertex> q;
           tmp_v = graph.setVertexLabel(Vertices[i], "VISITED");
           q.push(Vertices[i]);

           while(!q.empty()){
               Vertex v = q.front();
               q.pop();
               
               vector<Vertex> v_adjacent = graph.getAdjacent(v);
               for (unsigned j=0; j<v_adjacent.size(); j++){
                   if (graph.getEdgeWeight(v, v_adjacent[j]) < min_weight){
                       min_weight = graph.getEdgeWeight(v, v_adjacent[j]);
                       min_source = v;
                       min_dest = v_adjacent[j];
                   }

                   if (graph.getVertexLabel(v_adjacent[j]) == "UNEXPLORED"){
                       tmp_e = graph.setEdgeLabel(v, v_adjacent[j], "DISCOVERY");
                       tmp_v = graph.setVertexLabel(v_adjacent[j], "VISITED");
                       q.push(v_adjacent[j]);
                   }
                   else if (graph.getEdgeLabel(v, v_adjacent[j]) == "UNEXPLORED"){
                       tmp_e = graph.setEdgeLabel(v, v_adjacent[j], "CROSS");
                   }
                   else {}
               }
           }
        }
    }

    tmp_e = graph.setEdgeLabel(min_source, min_dest, "MIN");

    return min_weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> Vertices = graph.getVertices();
    vector<Edge> Edges = graph.getEdges();
    Vertex tmp_v;
    Edge tmp_e;

    for (unsigned i=0; i<Vertices.size(); i++)
        tmp_v = graph.setVertexLabel(Vertices[i], "UNEXPLORED");
    for (unsigned i=0; i<Edges.size(); i++)
        tmp_e = graph.setEdgeLabel(Edges[i].source, Edges[i].dest, "UNEXPLORED");

    //vector<Edge> Shortest_path;
    map<Vertex, Vertex> Predecessor;
    map<Vertex, int> Distance;

    queue<Vertex> q;
    tmp_v = graph.setVertexLabel(start, "VISITED");
    q.push(start);

    Predecessor.insert(pair<Vertex, Vertex>(start, start));
    Distance.insert(pair<Vertex, int>(start, 0));


    while(!q.empty()){
        Vertex v = q.front();
        q.pop();
        
        vector<Vertex> v_adjacent = graph.getAdjacent(v);
        for (unsigned j=0; j<v_adjacent.size(); j++){
            if (graph.getVertexLabel(v_adjacent[j]) == "UNEXPLORED"){
                tmp_e = graph.setEdgeLabel(v, v_adjacent[j], "DISCOVERY");
                tmp_v = graph.setVertexLabel(v_adjacent[j], "VISITED");
                q.push(v_adjacent[j]);

                Predecessor.insert(pair<Vertex, Vertex>(v_adjacent[j], v));
                Distance.insert(pair<Vertex, int>(v_adjacent[j], Distance[v]+1));

            }
            else if (graph.getEdgeLabel(v, v_adjacent[j]) == "UNEXPLORED"){
                tmp_e = graph.setEdgeLabel(v, v_adjacent[j], "CROSS");
            }
            else {}
        }
    }

    int dist = 0;
    Vertex curr = end;
    while(dist < Distance[end]){
        tmp_e = graph.setEdgeLabel(Predecessor[curr], curr, "MINPATH");
        dist += 1;
        curr = Predecessor[curr];
    }

    return Distance[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    
    vector<Vertex> Vertices = graph.getVertices();
    vector<Edge> Edges = graph.getEdges();
    sort(Edges.begin(), Edges.end());  // problem here?
   
    Edge tmp_e;
    vector<Edge> MST_Edges;

    map<Vertex, int> vertex_map;
    for (unsigned i=0; i<Vertices.size(); i++)
        vertex_map.insert(pair<Vertex, int>(Vertices[i], i));

    DisjointSets disjSets;
    disjSets.addelements(Vertices.size());
  
    int i=0;
    while(MST_Edges.size() < (Vertices.size()-1)){
        Edge tmp_e = Edges[i];
        int source_id = vertex_map[tmp_e.source];
        int dest_id = vertex_map[tmp_e.dest];
 
        if (disjSets.find(source_id) != disjSets.find(dest_id)){
            MST_Edges.push_back(tmp_e);
            disjSets.setunion(source_id, dest_id);        
        }

        i += 1;
    }

    for (unsigned i=0; i<MST_Edges.size(); i++){    
        tmp_e = graph.setEdgeLabel(MST_Edges[i].source, MST_Edges[i].dest, "MST");
    }
}

