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
#include <unordered_map>


void read_lines(const std::string& filename, std::string& input) {
	auto file = std::ifstream{ "../../../../Day_05/" + filename };
	file >> input;
}


void reduce(std::string& input) {
	bool erased = true;
	while (erased) {
		erased = false;
		for (auto iter = input.begin(); iter != input.end() && iter+1 != input.end(); iter++) {
			if (*iter != *(iter+1) && tolower(*iter) == tolower(*(iter + 1))) {
				erased = true;
				input.erase(iter, iter + 2);
			}
			if (iter == input.end()) {
				iter--;
			}
		}
	}
}

int reduce_with_removed_char(std::string input, char to_remove) {
	std::erase_if(input, [&](const auto& c)->bool {return tolower(c) == tolower(to_remove); });
	reduce(input);
	return input.size();
}

int main()
{
	std::string input;
	
	auto file_time = std::ofstream{ "../../../../Day_05/execution_times.txt" };
	auto file_out = std::ofstream{ "../../../../Day_05/output.txt" };

	auto start = std::chrono::high_resolution_clock::now();
	read_lines("input.txt", input);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	std::cout << input.size() << "\n";

	start = std::chrono::high_resolution_clock::now();
	reduce(input);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Reduced in: " << duration.count() << " microseconds.\n";

	std::cout << input.size() << "\n";

	file_out << input;

	std::unordered_map<char, std::future<int>> thread_results;


	for (char c = 'a'; c < 'z'; c++) {
		read_lines("input.txt", input);
		auto future = std::async(reduce_with_removed_char, input, c);
		thread_results[c] = std::move(future);
		//std::cout << c << ": " << reduce_with_removed_char(input, c) << "\n";
	}
	int min = input.size();
	char c;
	for (auto&[character, length] : thread_results) {
		int temp = length.get();
		if (temp < min) {
			c = character;
			min = temp;
		}
	}
	std::cout << c << " with" << min;
}