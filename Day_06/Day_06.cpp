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


using field = std::unordered_map<int, std::unordered_map<int, char>>;
using size = std::unordered_map<char, int>;

void read_lines(const std::string& filename,field& coordinates, int& max_x, int& max_y) {
	auto file = std::ifstream{ "../../../../Day_06/" + filename };
	char c = 'A';
	char temp;
	int x, y;
	max_x = 0;
	max_y = 0;
	while (!file.eof()) {
		file >> x >> temp >> y;
		max_x = (x > max_x) ? x : max_x;
		max_y = (y > max_y) ? y : max_y;
		coordinates[x][y] = c;
		std::cout << c << " :" << x << "," << y << "\n";
		c++;
	}
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void parse_distances(const field& coords, field& distance_field, size& sizes, int max_x, int max_y) {
	for (int x = 0; x <= max_y; x++) {
		for (int y = 0; y <= max_x; y++) {
			int min = max_x + max_y;
			for (const auto& [x_char, pair] : coords) {
				for (const auto& [y_char, c] : pair) {
					auto distance = manhattan_distance(x, y, x_char, y_char);
					if (distance == min ) {
						if (distance_field[x][y]) {
							sizes[distance_field[x][y]]--;
						}
						distance_field[x][y] = '.';
					}
					else if (distance < min) {
						if (distance_field[x][y]) {
							sizes[distance_field[x][y]]--;
						}
						min = distance;
						distance_field[x][y] = c;
						sizes[c]++;
						//std::cout << x << " " << y << " :" << c << "\n";
					}
				}
			}
		}
	}
}

void remove_infinite(field& distance_field, size& sizes, int max_x , int max_y) {
	for (const auto& [x, pair] : distance_field) {
		for (const auto& [y, c] : pair) {
			if (x == 0 || y == 0 || y == max_x || y == max_y) {
				sizes[distance_field[y][x]] = -1;
			}
		}
	}
}

int find_largest(size& sizes) {
	int max = 0;
	for (const auto& [c, size] : sizes) {
		std::cout << c << " " << size << "\n";
		max = size > max ? size : max;
	}
	return max;
}

void print(field& distance_field, int max_x, int max_y) {
	auto file = std::ofstream{ "../../../../output.txt" };
	for (int x = 0; x <= max_y; x++) {
		for (int y = 0; y <= max_x; y++) {
			file << (char)std::tolower(distance_field[y][x]);
		}
		file << "\n";
	}
}

int sum_max_distance(field& coordinates, int max_sum, int max_x,int max_y) {
	int result = 0;
	for (int x = 0; x <= max_y; x++) {
		for (int y = 0; y <= max_x; y++) {
			int distance = 0;
			for (const auto& [x_char, pair] : coordinates) {
				for (const auto& [y_char, c] : pair) {
					distance += manhattan_distance(x, y, x_char, y_char);
				}
			}
			result += distance <= max_sum ? 1 : 0;
		}
	}
	return result;
}

int main()
{
	field distances;
	field coordinates;
	size sizes;
	int max_x, max_y;
	read_lines("input.txt", coordinates, max_x, max_y);



	std::cout << "field size: " << max_x << " * " << max_y << "\n";

	parse_distances(coordinates, distances, sizes, max_x, max_y);

	remove_infinite(distances, sizes, max_x, max_y);

	auto part_one = find_largest(sizes);

	std::cout << "Part one: " << part_one << "\n";

	print(distances, max_x, max_y);

	auto part_two = sum_max_distance(coordinates, 10000, max_x, max_y);

	std::cout << "Part two: " << part_two << "\n";

	//auto file_time = std::ofstream{ "../../../../Day_05/execution_times.txt" };
	//auto file_out = std::ofstream{ "../../../../Day_05/output.txt" };
	//
	//auto start = std::chrono::high_resolution_clock::now();
	//read_lines("input.txt", input);
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//file_time << "Input read in " << duration.count() << " microseconds.\n";
	//
	//std::cout << input.size() << "\n";
	//
	//start = std::chrono::high_resolution_clock::now();
	//reduce(input);
	//stop = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//file_time << "Reduced in: " << duration.count() << " microseconds.\n";
	//
	//std::cout << input.size() << "\n";
	//
	//file_out << input;
	//
	//std::unordered_map<char, std::future<int>> thread_results;
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