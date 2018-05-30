#include "stdafx.h"
#include "Graph.h"
#include <iostream>

Graph::Graph()
{
	
}


Graph::~Graph()
{
	for (auto it = lookup.begin(); it != lookup.end(); it++) {
		delete it->second;
	}
}

int Graph::size() { return lookup.size(); }
//get a pointer to a node in the graph; nullptr otherwise
Graph::Node* Graph::getNode(int id) {
	auto it = lookup.find(id);

	return it != lookup.end() ? it->second : nullptr;
}
bool Graph::contains(int id) { return getNode(id) != nullptr; }

//Depth First Search on the graph
bool Graph::DFS(int source, int destination) {
	Node * s = getNode(source);
	Node * d = getNode(destination);

	if (s == nullptr || d == nullptr)return false;

	std::set<int> visit;
	return DFS(s, d, visit);
}
//helper function for DFS
bool Graph::DFS(Node* source, Node* destination, std::set<int>& visited) {

	if (visited.find(source->id) != visited.end())return false;

	visited.emplace(source->id);

	if (source == destination)return true;

	for (Node* n : source->adjacent) {
		if (DFS(n, destination, visited))return true;
	}

	return false;
}
//Breadth First Search
bool Graph::BFS(int source, int destination) {
	Node* s = getNode(source);
	Node * d = getNode(destination);

	if (s == nullptr || d == nullptr)return false;
	std::queue<Node*> next;
	std::set<int> visit;
	return BFS(s, d, next, visit);
}
//helper function for BFS
bool Graph::BFS(Node* source, Node * destination, std::queue<Node*>  & next, std::set<int> & visited) {
	next.push(source);
	
	while (!next.empty()) {
		Graph::Node* node = next.front();
		next.pop();
		
		if (node == destination)return true;

		if (visited.find(node->id) != visited.end())continue;

		visited.emplace(node->id);

		for (Node* child : node->adjacent)next.push(child);

	}
	return false;
}
//remove a node from the graph
bool Graph::removeEdge(int id) {
	auto node = lookup.find(id);//see if id in the map
	if (node == lookup.end())return false;

	for (Node * child : node->second->adjacent) {
		auto it = std::find(child->adjacent.begin(), child->adjacent.end(), node->second);
        child->adjacent.erase(it);

		//if (child->adjacent.empty())removeDanglingNode(child);//remove all the children that had only one connection
	}

	
	delete node->second;
	lookup.erase(node);

	return true;
}

//remove any node from the graph with no adjacent connections
void Graph::removeDanglingNode(Node* node) {

	lookup.erase(node->id);
	delete node;
}

//add a node to the graph
bool Graph::addEdge(int id, std::vector<int> & edges) {
	
	if (contains(id))return false;//cannot insert duplicates

	auto it = lookup.emplace(id, new Node(id));

	for (int i : edges) {
		auto node = getNode(i);

		if (node != nullptr) {
			it.first->second->adjacent.push_back(node);
			node->adjacent.push_back(it.first->second);
		}

	}

	
	return true;//added node to graph so return true

}

void Graph::printGraph() {
	for (auto it = lookup.begin(); it != lookup.end(); it++) {

		std::cout << "Node: " << it->first<<" Edges: ";
		for (auto child : it->second->adjacent) {
			std::cout << child->id << " ";
		}

	std:: cout << std::endl;
	}
	std::cout << std::endl;
}