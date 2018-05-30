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
	bool DFS(int source, int destination) const;
	bool BFS(int source, int destination) const;
	bool addEdge(int id,  const std::vector<int>&);
	bool updateEdges(int id, const std::vector<int>&);
	bool removeEdge(int id);
	bool contains(int id) const;
	void printGraph() const;
	int size() const;

private: 
	//node class
	struct Node {
		int id;
		std::set<Node*> adjacent;//adjacency list
		Node(int id) {
			this->id = id;
		}
	private: Node(){}

	};

	
	std::map<int, Node*> lookup;//store nodes
		 bool DFS(Node* source, Node* destination, std::set<int> & set) const;
		 bool BFS(Node* source, Node* destination, std::queue<Node*>& queue, std::set<int> & set) const;
		 Node* getNode(int id) const;
		 void removeDanglingNode(Node* child);
		 
};

