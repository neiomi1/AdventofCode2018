#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>  
#include <string>
#include <sstream>
#include <chrono>
#include <future>
#include <thread>
#include <map>

#include "Day_07.h"


Node::Node(const std::string& name) : name_(name)
{
	predecessors_ = {};
}

void Node::add_predecessor(Node* node)
{
	predecessors_.push_back(node);
}

bool Node::reachable(const std::vector<Node*>& nodes)
{
	for (const auto& node : predecessors_) {
		if (std::find(nodes.begin(), nodes.end(), node) == nodes.end()) {
			return false;
		}
	}
	return true;
}


void read_entries(const std::string& filepath, std::map<std::string, Node>& node_map) {
	auto file = std::ifstream{ filepath };
	std::string lhs;
	std::string rhs;
	while (!file.eof()) {
		file >> lhs >> lhs;
		if (!node_map.contains(lhs)) {
			node_map[lhs] = Node{ lhs };
		}
		file >> rhs >> rhs >> rhs >> rhs >> rhs >> rhs;
		if (!node_map.contains(rhs)) {
			node_map[rhs] = Node{ rhs };
		}
		node_map[rhs].add_predecessor(&node_map[lhs]);
		file.ignore(99999, '\n');
	}

}

std::string part_one(std::map<std::string, Node>& node_map) {
	std::vector<Node*> path;
	std::unordered_map<Node*, bool> taken;
	auto it = node_map.begin();
	bool found = false;
	while (it != node_map.end()) {
		if ((*it).second.reachable(path) && !taken.contains(&(*it).second)) {
			taken[&(*it).second] = true;
			path.push_back(&(*it).second);
			found = true;
		}

		if (found) {
			it = node_map.begin();
			found = false;
		}
		else {
			it++;
		}
		if (it == node_map.end() && path.size() < node_map.size()) {
			
		}
		
	}
	std::string result{};
	std::for_each(path.begin(), path.end(), [&](const auto& node) {result += node->name(); });
	return result;
}



int main()
{
	std::map<std::string, Node> node_map;

	auto file_time = std::ofstream{ "../../../../Day_07/execution_times.txt" };
	//auto file_out = std::ofstream{ "../../../../Day_05/output.txt" };
	
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("../../../../Day_07/input.txt", node_map);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";
	
	std::cout << node_map.size() << "\n";
	
	
	start = std::chrono::high_resolution_clock::now();
	std::string result = part_one(node_map);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one in: " << duration.count() << " microseconds.\n";
	
	std::cout << result << "\n";
	
	std::unordered_map<char, std::future<int>> thread_results;
	//
	//
	//for (char c = 'a'; c < 'z'; c++) {
	//	read_lines("input.txt", input);
	//	auto future = std::async(reduce_with_removed_char, input, c);
	//	thread_results[c] = std::move(future);
	//	//std::cout << c << ": " << reduce_with_removed_char(input, c) << "\n";
	//}
	//int min = input.size();
	//char c;
	//for (auto&[character, length] : thread_results) {
	//	int temp = length.get();
	//	if (temp < min) {
	//		c = character;
	//		min = temp;
	//	}
	//}
	//std::cout << c << " with" << min;
}

