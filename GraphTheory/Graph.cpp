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
Graph::Node* Graph::getNode(const int & id) const{
	auto it = lookup.find(id);

	return it != lookup.end() ? it->second : nullptr;
}


bool Graph::contains(const int& id) const{ return getNode(id) != nullptr; }

//Depth First Search on the graph
bool Graph::DFS(const int& source, const int& destination) const{
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
bool Graph::BFS(const int& source, const int& destination) const{
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
bool Graph::removeEdge(const int& id) {
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
bool Graph::addEdge(const int& id, const std::vector<int> & edges) {
	
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
bool Graph::updateEdges(const int& id, const std::vector<int> & edges) {
	if (!contains(id))return false;

	this->removeEdge(id);


	return this->addEdge(id, edges);
}


std::map<int,int> Graph::shortestPathToEachNode(const int& source) const {
	auto start = getNode(source);
	

	std::map<int, int> distances;
	//if the node does not exist, return an empty set
	if (start != nullptr ) {

	std::queue<Node*> queue;//queue used in the algorithm 

	//map holding all the distances to each node

	for (auto it = lookup.begin(); it != lookup.end(); it++) {//fill the map with ids as keys and -1 as distances
		distances.emplace(it->first, -1);
	}
	distances[source] = 0;//the starting node always has a distance of 0 from itself
	

	queue.push(start);
	while (!queue.empty()) {
		auto node = queue.front();
		queue.pop();
		for (auto child : node->adjacent) {
			if (distances.find(child->id)->second== (-1)) {//if the node has not been visited
				distances.at(child->id) = distances.at(node->id) + 1;
				queue.push(child);
			}
		}
	}
}
    return distances;
}