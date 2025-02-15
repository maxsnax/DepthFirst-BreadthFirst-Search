//============================================================================
// Name        : test6.cpp
// Author      : Max Schumacher
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "graph.h"
#include "infinity.h"
using namespace std;

// Returns the value of INFINITY.
int GetINFINITY() {
	return -1;
}

int main(int argv, char **argc) {
	Graph mainGraph;	// Graph to use for testing

	mainGraph.LoadGraph("Sample Input.txt");

	mainGraph.PrintGraph();

	mainGraph.RunDijkstra('a');

	mainGraph.PrintGraph();

	cout << mainGraph.GetDistance('A');
	cout << mainGraph.GetDistance('a');
	cout << mainGraph.GetDistance('b');
	cout << mainGraph.GetDistance('c');
	cout << mainGraph.GetDistance('d');
	cout << mainGraph.GetDistance('e');
	cout << mainGraph.GetDistance('f');
	cout << mainGraph.GetDistance('g');

	mainGraph.GetNumberOfUpdates('b');
}
