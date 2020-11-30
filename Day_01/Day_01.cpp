#include "Day_01.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>  
#include <unordered_map>

namespace fs = std::filesystem;

int final_frequency() {
	int result = 0;
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\input.txt" };
	//auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\test_input_02.txt" };
	//auto resultFile = std::ofstream{ "..\\..\\..\\..\\Day_01\\output.txt" };
	int current;
	while (file >> current) {
		result += current;
		//std::cout << result << "  " << current << "\n";
		//resultFile << result << "\n";
	}
	return result;
}

int first_frequency(){
	std::unordered_map<int, int> visited = {};
	int frequency = 0;

	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\input.txt" };
	//auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\test_input_04.txt" };
	auto resultFile = std::ofstream{ "..\\..\\..\\..\\Day_01\\output.txt" };
	int current;
	int loops = 0;
	while (visited.find(frequency) == visited.end()) {
		visited[frequency];
		resultFile << frequency << "\n";
		if (file.eof()) {
			loops++;
			resultFile << "looping\n";
			file.clear();
			file.seekg(0, std::ios::beg);
			
		}
		file >> current;
		frequency += current;
	}
	resultFile << "Result  : " << frequency << "\nNumber of Loops: " << loops;
	return frequency;
}


int main()
{
	std::cout << "Current path is " << fs::current_path() << '\n';
	std::cout << "Final Frequency: " << final_frequency() << "\n";
	std::cout << "First Duplicate: " << first_frequency() << "\n";


}
