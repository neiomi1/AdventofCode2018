// Day_01.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include <functional>
#include <tuple>
// TODO: Reference additional headers your program requires here.


class Node {
public:
	Node() {};

	Node(const std::string& name);

	std::string name() { return name_; }

	void add_predecessor(Node* node);

	bool reachable(const std::vector<Node*>& nodes);

	bool operator > (const Node& node)const {
		return name_ > node.name_;
	}

	bool operator < (const Node& node) const {
		return name_ < node.name_;
	}

	bool operator == (const Node& node) const {
		return name_ == node.name_;
	}

	bool operator >= (const Node& node)const {
		return ! (*this < node);
	}

	bool operator <= (const Node& node) const {
		return !(*this > node);
	}

	void operator = (const Node& node) {
		this->name_ = node.name_;
		this->predecessors_ = node.predecessors_;
	}

private:
	std::string name_;
	std::vector<Node*> predecessors_;
};