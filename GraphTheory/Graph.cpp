#include "stdafx.h"
#include "Graph.h"
#include <iostream>

Graph::Graph()
{
	
}


Graph::~Graph()
{
	//clean up the graph
	while (!lookup.empty()) {
		auto it = lookup.begin();
		delete it->second;
		lookup.erase(it);
	}
}

int Graph::size() const{ return lookup.size(); }


//get a pointer to a node in the graph; nullptr otherwise
Graph::Node* Graph::getNode(int id) const{
	auto it = lookup.find(id);

	return it != lookup.end() ? it->second : nullptr;
}


bool Graph::contains(int id) const{ return getNode(id) != nullptr; }

//Depth First Search on the graph
bool Graph::DFS(int source, int destination) const{
	Node * s = getNode(source);
	Node * d = getNode(destination);

	if (s == nullptr || d == nullptr)return false;

	std::set<int> visit;
	return DFS(s, d, visit);
}
//helper function for DFS
bool Graph::DFS(Node* source, Node* destination, std::set<int>& visited) const{

	if (!(visited.emplace(source->id).second))return false;


	if (source == destination)return true;

	for (Node* n : source->adjacent) {
		if (DFS(n, destination, visited))return true;
	}

	return false;
}
//Breadth First Search
bool Graph::BFS(int source, int destination) const{
	Node* s = getNode(source);
	Node * d = getNode(destination);

	if (s == nullptr || d == nullptr)return false;

	std::queue<Node*> next;
	std::set<int> visit;
	return BFS(s, d, next, visit);
}
//helper function for BFS
bool Graph::BFS(Node* source, Node * destination, std::queue<Node*>  & next, std::set<int> & visited) const{
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
		auto it = child->adjacent.find(node->second);
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
bool Graph::addEdge(int id, const std::vector<int> & edges) {
	
	if (contains(id))return false; // cannot insert duplicates

	auto it = lookup.emplace(id, new Node(id));

	for (int i : edges) {
		auto node = getNode(i);

		if (node != nullptr) {
			it.first->second->adjacent.emplace(node);
			node->adjacent.emplace(it.first->second);
		}

	}

	
	return true;//added node to graph so return true

}

void Graph::printGraph() const{
	for (auto it = lookup.begin(); it != lookup.end(); it++) {

		std::cout << "Node: " << it->first<<" Edges: ";
		for (auto child : it->second->adjacent) {
			std::cout << child->id << " ";
		}

	std:: cout << std::endl;
	}
	std::cout << std::endl;
}

//change any connections in the graph
bool Graph::updateEdges(int id, const std::vector<int> & edges) {
	Node* node = getNode(id);
	if (!node)return false;

	this->removeEdge(id);


	return this->addEdge(id, edges);
}