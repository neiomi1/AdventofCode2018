#include "Day_03.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>  
#include <unordered_map>

namespace fs = std::filesystem;

std::unordered_map<int, std::unordered_map<int, int>> fabric = {};
std::vector<Claim> claims = {};
int num_multiple_claimed_tiles = 0;
void readLines(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_03\\"+filename };
	// lines are: #ID @ X,Y: widthxheight
	char c;
	int ID, x, y, width, height;
	while (file >> c >> ID >> c >> x >> c >> y >> c >> width >> c >> height) {
		std::cout << "#" << ID << " @ " << x << "," << y << ": " << width << "x" << height << "\n";
		claims.push_back(Claim{ ID,x,y,width,height });
	}
}

void process_claims(){
	for (const auto& claim : claims) {
		for (int i = claim.x; i < claim.x + claim.width; i++) {
			for (int j = claim.y; j < claim.y + claim.height; j++) {
				auto it = fabric.find(i);
				if ( it == fabric.end() || it->second.find(j) == it->second.end()) {
					fabric[i][j] = claim.ID;
				}
				else {
					if (fabric[i][j] != -1) {
						num_multiple_claimed_tiles++;
						fabric[i][j] = -1;
					}
 				}
			}
		}
	}
}


void print_to_file(const std::string& filename) {
	auto file_out = std::ofstream{ "..\\..\\..\\..\\Day_03\\output.txt" };
	for (int x = 0; x < 1000; x++) {
		for (int y = 0; y < 1000; y++) {
			auto it = fabric.find(x);
			if (it != fabric.end() && it->second.find(y) != it->second.end()) {
				switch (fabric[x][y]) {
				case -1: file_out << "X"; break;
				default: file_out << "O";
				}
			}
			else {
				file_out << ".";
			}
		}
		file_out << "\n";
	}
}

const Claim& non_overlap_claim(){
	bool found;
	for (const auto& claim : claims) {
		found = true;
		for (int x = claim.x; x < claim.x + claim.width; x++) {
			for (int y = claim.y; y < claim.y + claim.height; y++) {
				if (fabric[x][y] == -1) {
					found = false;
				}
			}
		}
		if (found) {
			return claim;
		}
	}
}


int main()
{
	//std::cout << "Current path is " << fs::current_path() << '\n';
	readLines("input.txt");
	process_claims();
	std::cout << "num multiple tiles: " << num_multiple_claimed_tiles << "\n";
	print_to_file("output.txt");
	std::cout << "untouched claim ID: " << non_overlap_claim().ID;
}
