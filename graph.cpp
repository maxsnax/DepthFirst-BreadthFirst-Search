//============================================================================
// Name        : graph.cpp
// Author      : Max Schumacher
//============================================================================

#include "graph.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

struct Vertex {
	char name = ' ';
	int val = 0;
	bool visited = false;
	Vertex *previous = nullptr;
	int distance = 99999;
	int numUpdates = 0;
};

vector<vector<Vertex*>> graph;
vector<char> points;
vector<vector<char>> edgeOrder;
vector<Vertex*> vertexList;
char startingVertex = ' ';
bool directed = true;
int numVertices = 0;

// Constructor/Destructor for Graph.
Graph::Graph() {

}

// Loads the graph.
void Graph::LoadGraph(char *graphFileName) {

	FILE *inFile = fopen(graphFileName, "r");
	if (!inFile) return;

	char buffer[12];
	string line;
	bool addingVertices = true;
	while (fgets(buffer, 12, inFile)) {
		line = buffer;

		if (line.find("[Vertices]\n") != string::npos) {
			addingVertices = true;
			continue;
		} else if (line.find("[Edges]\n") != string::npos) {
			addingVertices = false;
			continue;
		} else if (line == "\n") continue;

		string weight = "";
		bool skip = false;
		if (!addingVertices) {
			for (int n = 4; n < 12; n++) {
				char c = buffer[n];
				if (c == '\n' || c == ' ') break;
				if (c < '0' || c > '9') {
					skip = true;
				}
				weight += c;
			}
		}
		if (skip) continue;

		addingVertices ? AddVertex(line[0]) : AddEdge(line[0], line[2], stoi(weight));

		for (int n = 0; n < 12; n++) {
			buffer[n] = ' ';
		}
	}

	fclose(inFile);

}

// Runs Dijkstra's algorithm, using the specified vertex as the starting vertex.
void Graph::RunDijkstra(char startVertex) {
	if (sizeof(vertexList) == 0 || sizeof(edgeOrder) == 0) return; 

	startingVertex = startVertex;
	// Get a clean slate of visited vertices and depths set to
	resetVisits();

	// Set the starting vertex's distance to 0
	int srcIndex = getIndex(startVertex);
	Vertex *sourceVertex = graph[srcIndex][srcIndex];
	sourceVertex->distance = 0;

	list<Vertex*> q;

	for (int n = 0; n < numVertices; n++) {
		Vertex* v = graph[srcIndex][n];
		if (n != srcIndex) {
			int currDist = graph[srcIndex][n]->val;
			if (currDist != 0) {
				v->distance = graph[srcIndex][n]->val;
				v->numUpdates++;
			}
			q.push_back(v);
		}
	}

	Vertex* smallest = q.front();  // Initialize smallest to the first vertex in q

	while (!q.empty()) {
		// This just get the index of the smallest distance vertex in the q
		int idx = 0;
		for (int n = 0; n < numVertices; n++) {
			Vertex* v = graph[srcIndex][n];
			if (v->val != 0 && smallest->val > v->val) {
				smallest = v;
				idx = n;
			}
		}

		// Use std::next() to advance the iterator to the idx-th element of q
		Vertex* u = *next(q.begin(), idx);
		q.erase(next(q.begin(), idx));

		// for each neighbor of the shortest path neighbor, traverse and see if that connection is closer than the current connection
		for (int n = 0; n < numVertices; n++) {
			int start = getIndex(u->name);
			if (graph[start][n]->val != 0) {
				int altDistance = u->distance + graph[start][n]->val;
				if (altDistance < graph[srcIndex][n]->distance) {
					graph[srcIndex][n]->val = altDistance;
					graph[srcIndex][n]->distance = altDistance;
					graph[srcIndex][n]->previous = u;
					graph[srcIndex][n]->numUpdates++;
				}
			}
		}

	}

}

// Returns the distance of the vertex with the specified name from the starting vertex.
int Graph::GetDistance(char vertex) {
	if (getIndex(vertex) == -1) return -1;
	int distance = graph[getIndex(startingVertex)][getIndex(vertex)]->distance;
	return distance != 99999 ? distance : -1;
}

// Returns the number of updates made to the vertex's distance during the last call of RunDijkstra.
int Graph::GetNumberOfUpdates(char vertex) {
	int idx = getIndex(vertex);
	if (idx == -1) return -1;
	return graph[getIndex(startingVertex)][idx]->numUpdates;
}

/*
 * 	Assignment 5 Functions
 */

/*	==================================================================
		Constructor and Destructor for graph
 	================================================================== */

// Clears the graph and sets if the graph is directed now.
void Graph::ClearGraph(bool isDirected) {
	graph.clear();
	points.clear();
	edgeOrder.clear();
	directed = isDirected;
	numVertices = 0;
}

Graph::~Graph() {
    for (auto row : graph) {
        for (auto vertex : row) {
            delete vertex;
        }
    }
}



/*	==================================================================
		Print Functions
 	================================================================== */
// Prints the list of vertices in the order they were added.
void Graph::PrintVertexList() {
	if (points.size() == 0) {
		printf("No vertices");
	}
	int count = 0;
	for (const char& c : points) {
		cout << c;
		if (++count < numVertices) {
			cout << " ";
		}
	}
}

// Prints the list of edges in the order they were added.
void Graph::PrintEdgeList() {
	if (edgeOrder.size() == 0) {
		printf("No edges");
	}

	for (auto & array : edgeOrder) {
		printf("[ %c %c ]\n", array[0], array[1]);
	}
}

void Graph::PrintGraph() {
	cout << "\nPrinting Graph\n   ";
	for (int n = 0; n < numVertices; n++) {
		printf("[%c]", points[n]);
	}
	cout << endl;
	for (int i = 0; i < numVertices; i++) {
		printf("[%c]", points[i]);
		for (int j = 0; j < numVertices; j++) {
			printf("[%d]", graph[i][j]->val);
		}
		cout << endl;
	}
	cout << "numVertices = " << numVertices << endl << endl;
}


void Graph::PrintNames() {
	cout << "Printing Names:\n   "   ;
	for (int i = 0; i < numVertices; i++) {
		printf("[%c]", points[i]);
	}
	cout << endl;
	for (int i = 0; i < numVertices; i++) {
		printf("[%c]", points[i]);
		for (int j = 0; j < numVertices; j++) {
			printf("[%c]", graph[i][j]->name);
		}
		cout << endl;
	}
}

/*	==================================================================
		Graph Add/Remove Functions
 	================================================================== */
// Adds a vertex with the specified name to the graph.
void Graph::AddVertex(char name) {
	// Checks if its a valid name
	if (!((name >= 48 && name <= 57) || (name >= 65 && name <= 90) || (name >= 97 && name <= 122))) {
		return;
	}

	// Creates a new row at the bottom of the 2D array
	points.push_back(name);
	vector<Vertex*> row;
	graph.push_back(row);

	for (int n = 0; n <= numVertices; n++) {	// Fill the new row with new vertices
		Vertex *newVertex = new Vertex;
		graph[numVertices].push_back(newVertex);
	}

	// Adds the new column for each row at the end of the row
	for (int n = 0; n <= numVertices; n++) {
		Vertex *newVertex = new Vertex;
		graph[n].push_back(newVertex);
	}

	// Fills in all of the vertices columns properly so that rows and columns are named right
	for (int i = 0; i <= numVertices; i++) {
		for (int j = 0; j <= numVertices; j++) {
			graph[i][j]->name = points[j];
		}
	}
	++numVertices;
}

// Removes the vertex with the specified name from the graph.
void Graph::RemoveVertex(char name) {
	// Earse the vertex in the points vector
	int index = getIndex(name);
	if (index == -1) return;
	points.erase(points.begin() + index);	// Erase from the points list

	// In every row, delete the column for that vertex
	for (auto & row : graph) {
		row.erase(row.begin() + index);
	}

	// Delete the entire row for that vertex
	graph.erase(graph.begin() + index);

	// For every edge in edgeOrder, if it has the name of the vertex then erase it
	for (int n = 0; n < (int)edgeOrder.size(); n++) {
		if (edgeOrder[n][0] == name || edgeOrder[n][1] == name) {
			edgeOrder.erase(edgeOrder.begin() + n);
			--n;
		}
	}

	--numVertices;
}

// Adds an edge between the two vertices to the graph.
void Graph::AddEdge(char name1, char name2, int weight) {
	if (name1 == name2) return;
	// if the vertices are not in the vertex list, then dont add the edge
	int index1 = getIndex(name1);
	int index2 = getIndex(name2);
	if (index1 == -1 || index2 == -1 || weight < 0) {
		return;
	}

	// if the edge already exists then dont add the edge
	if (edgeExists(name1, name2)) return;

	edgeOrder.push_back({name1, name2});	// add the edge to the edge list

	graph[index1][index2]->val = weight;			// add the connection on the graph
	if (!directed) {
		graph[index2][index1]->val = weight;		// if not a directed graph, add it both ways
	}
}

/*	==================================================================
		Search functions
 	================================================================== */


/*	==================================================================
		Helper functions
 	================================================================== */

int Graph::getIndex(char name) {
	int count = 0;
	bool found = false;
	for (const char& vertex : points) {
		if (name == vertex) {
			found = true;
			break;
		}
		count++;
	}

	return found == true ? count : -1;
}

void Graph::resetVisits() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
        	graph[i][j]->distance = 99999;
            graph[i][j]->visited = false;
            graph[i][j]->previous = nullptr;
        }
    }
}

bool Graph::edgeExists(char name1, char name2) {
	if (directed) {
		for (auto & edge : edgeOrder) {	// check if the exact edge exists
			if (edge[0] == name1 && edge[1] == name2) return true;
		}
	} else {
		for (auto & edge : edgeOrder) {	// check if the edge exists in either direction
			if (edge[0] == name1 && edge[1] == name2) return true;
			if (edge[0] == name2 && edge[1] == name1) return true;
		}
	}

	return false;
}
