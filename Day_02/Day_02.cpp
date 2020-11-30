#include "Day_02.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>  
#include <unordered_map>

namespace fs = std::filesystem;

int checksum() {
	int result = 0;
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\input.txt" };
	//auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\test_input_01.txt" };
	std::string current;
	std::unordered_map<char, int> appearance_map = {};
	bool twice = false;
	bool thrice = false;
	int num_twice = 0; 
	int num_thrice = 0;
	while (file >> current) {
		appearance_map.clear();
		//std::cout << current << "\n";
		for (const auto& c : current) {
			appearance_map[c]++;
		}
		for(const auto& pair : appearance_map) {
			//std::cout << pair.first << ":" << pair.second << "\n";
			switch (pair.second) {
			case 2: twice = true; break;
			case 3: thrice = true; break;
			}
		}
		if (twice) {
			num_twice++;
			twice = false;
		}
		if (thrice) {
			num_thrice++;
			thrice = false;
		}

	}
	return num_twice * num_thrice;
}

int compare_strings(const std::string& word1, const std::string& word2) {
	int position_diff = -1;
	for (int i = 0; i < word1.size(); i++) {
		//std::cout << i <<" " << word1.size() << " " << word2.size() << "\n";
		if (word1[i] != word2[i]) {
			if (position_diff == -1) {
				position_diff = i;
			}
			else { return -1; }
		}
	}
	//std::cout << "found it at:" << position_diff << " " << word1 << "\n";
	return position_diff;
}

void correct_pair(){
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\input.txt" };
	auto file_out = std::ofstream{ "..\\..\\..\\..\\Day_02\\output.txt" };
	std::vector<std::string> lines;
	std::string line;
	while (file >> line) {
		lines.push_back(line);
	}
	for (int i = 0; i < std::ssize(lines); i++) {
		for (int j = i + 1; j < std::size(lines); j++) {
			file_out << lines[i] << " " << lines[j] << "\n";
			switch (int pos = compare_strings(lines[i], lines[j])) {
			case -1: break;
			default: lines[i].erase(lines[i].begin() + pos); 
				std::cout << lines[i] << "\n"; 
				file_out << "Result: " << lines[i];
				return;
			}
		}
	}
}


int main()
{
	std::cout << "Current path is " << fs::current_path() << '\n';
	std::cout << "Checksum : " << checksum() << "\n";
	std::cout << "Matching characters: ";
	correct_pair();


}
