# DepthFirst-BreadthFirst-Search
**Graph Algorithms Implementation**
This repository contains an implementation of a graph data structure in C++ with support for common graph operations and algorithms. The project includes a Makefile to simplify the build process.

**Key Features**
Graph Operations: Add and remove vertices and edges, print graph structure, and reset graph states.
Dijkstra's Algorithm: Compute shortest paths from a starting vertex to all other vertices, with tracking of distance updates.
File-Based Input: Load graph data from a file containing vertices and weighted edges.
Debugging Support: Print the adjacency matrix, edge list, and vertex list for visualization.

**File Descriptions**
graph.cpp / graph.h: Core implementation of the graph data structure and related algorithms.
infinity.h: Utility header file for infinite values.
test6.cpp: Driver program for testing graph functionality with sample input.
Sample Input.txt: Example graph data file for testing.
Makefile: Build automation script for compiling the program.


# Program Setup and Execution

**Setup**
- Install mingw from SourceForge
- Add C:\MinGW\bin to your System Environment Variables
- To verify installation in admin powershell run:
*g++ --version*

**Usage**
Compile: We need to compile the build to get the .exe and .o files for test6, and the .o file for graph
- Run the following command in the terminal from your project directory
*mingw32-make*

or simply just

*make*

Run: Use the name of the test file, or create separate test files and update the makefile to reflect it.
*./test6*

Clean: To remove the files created during the compilation process, use the clean command
*mingw32-make clean*

**Testing**
Sample Input
The graph is loaded from a text file with the following structure:

[Vertices]  
a  
b  
c  
d  
e  
f  
g  


[Edges]  
a b 4  
a c 5  
b c 10  
g a 15  
d a 10  
e a 3  
b f 4  
c g 5  


Sample Output:
Printing Graph  
....[a][b][c][d][e][f][g]  
[a][0][4][5][0][0][0][0]  
[b][0][0][10][0][0][4][0]  
[c][0][0][0][0][0][0][5]  
[d][10][0][0][0][0][0][0]  
[e][3][0][0][0][0][0][0]  
[f][0][0][0][0][0][0][0]  
[g][15][0][0][0][0][0][0]  
numVertices = 7  


Printing Graph  
....[a][b][c][d][e][f][g]  
[a][0][4][5][0][0][8][10]  
[b][0][0][10][0][0][4][0]  
[c][0][0][0][0][0][0][5]  
[d][10][0][0][0][0][0][0]  
[e][3][0][0][0][0][0][0]  
[f][0][0][0][0][0][0][0]  
[g][15][0][0][0][0][0][0]  
numVertices = 7  

-1045-1-1810
