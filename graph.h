#ifndef GRAPH_H
#define GRAPH_H
#define GRAPH 1
#define POINTS 2
#define SRC_VERTEX 0
#define DST_VERTEX 2
#include <stdio.h>

// Defines a graph.
class Graph {
public:
	// Constructors/Destructor for Graph.
	Graph();
	~Graph();

	// Loads the graph.
	void LoadGraph(char *graphFileName);

	// Runs Dijkstra's algorithm, using the specified vertex as the starting vertex.
	void RunDijkstra(char startVertex);

	// Returns the distance of the vertex with the specified name from the starting vertex.
	int GetDistance(char vertex);

	// Returns the number of updates made to the vertex's distance during the last call of RunDijkstra.
	int GetNumberOfUpdates(char vertex);

	/*
	 * 	Assignment 5
	 */

	/*	==================================================================
			Required functions
	 	================================================================== */
	// Clears the graph and sets if the graph is directed now.
	void ClearGraph(bool isDirected);

	// Searches for the path between two names.  Returns the length of the first path found.
	int SearchForPath(char name1, char name2, bool useBFS);

	// Prints the list of vertices in the order they were added.
	void PrintVertexList();

	// Prints the list of edges in the order they were added.
	void PrintEdgeList();

	// Adds a vertex with the specified name to the graph.
	void AddVertex(char name);

	// Removes the vertex with the specified name from the graph.
	void RemoveVertex(char name);

	// Adds an edge between the two vertices to the graph.
	void AddEdge(char name1, char name2, int weight);

	/*	==================================================================
			Helper functions
	 	================================================================== */
	int BFS(char name1, char name2);

	int DFS(char name1, char name2);

	void DFSVisit(char name1, char name2, int steps);

	int getIndex(char name);

	void PrintGraph();

	void resetVisits();

	bool edgeExists(char name1, char name2);

	void PrintNames();

};

#endif
