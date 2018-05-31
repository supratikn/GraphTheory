#pragma once
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
class Graph
{

private:
	//node class
	struct Node {
		int id;
		std::string data;
		std::set<Node*> adjacent;//adjacency list
		Node(int id,std::string data) {
			this->id = id;
			this->data = data;
		}
	private: Node() {}

	};


	std::map<int, Node*> lookup;//store nodes
	bool DFS(Node* source, Node* destination, std::set<int> & set) const;
	bool BFS(Node* source, Node* destination, std::queue<Node*>& queue, std::set<int> & set) const;
	Node* getNode(const int& id) const;//O(log n)
	void removeDanglingNode(Node* child);


public:
	Graph();
	~Graph();
	bool DFS(const int& source, const int& destination) const;
	bool BFS(const int& source, const int& destination) const;
	bool addEdge(const int& id, const std::string data, std::vector<int>&);
	bool updateEdges(const int& id, const std::string data, std::vector<int>&);
	bool removeEdge(const int& id);
	bool contains(const int& id) const;//O(log n)
	void printGraph() const;//O (n *m)
	int size() const;
	std::map<int, int> shortestPathToEachNode(const int& source) const;//O (n^2)

};
