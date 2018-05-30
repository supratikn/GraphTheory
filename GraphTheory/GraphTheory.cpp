// GraphTheory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <iostream>
#include <vector>

int main()
{
	Graph graph;

	std::vector<int> a = {};
	graph.addEdge(1, a);
	a = { 1 };
	graph.addEdge(3, a);
	a = { 1,3 };
	graph.addEdge(4,a );
	a = { 3 };
	graph.addEdge(5, a);
	a = { 4 };
	graph.addEdge(2, a);

	graph.printGraph();
	std::cout << graph.BFS(1, 5) << std::endl;
	std::cout << graph.DFS(1, 5) << std::endl;

	graph.removeEdge(3);

	graph.printGraph();

	std::cout << graph.BFS(1, 5) << std::endl;
	std::cout << graph.DFS(1, 5) << std::endl;
	




    return 0;
}

