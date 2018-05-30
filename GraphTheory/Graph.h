#pragma once
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
class Graph
{
public:
     Graph();
	~Graph();
	bool DFS(int source, int destination);
	bool BFS(int source, int destination);
	bool addEdge(int id,  std::vector<int>&);
	bool removeEdge(int id);
	bool contains(int id);
	void printGraph();
	int size();

private: 
	//node class
	struct Node {
		int id;
		std::vector<Node*> adjacent;//adjacency list
		Node(int id) {
			this->id = id;
		}
	private: Node(){}

	};

	
	std::map<int, Node*> lookup;//store nodes
		 bool DFS(Node* source, Node* destination, std::set<int> & set);
		 bool BFS(Node* source, Node* destination, std::queue<Node*>& queue, std::set<int> & set);
		 Node* getNode(int id);
		 void removeDanglingNode(Node* child);
		 
};

