#include "Day_04.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>  
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>


void parse_logs(const std::string& line, DateTime& datetime, std::unordered_map<DateTime, std::string>& logs) {
	auto stream = std::istringstream{ line };
	char c;
	int n;
	stream >> c >> n;
	datetime.date.year = n;
	stream >> c >> n;
	datetime.date.month = n;
	stream >> c >> n;
	datetime.date.Day = n;
	stream >> n;
	datetime.time.hours = n;
	stream >> c >> n >> c;
	datetime.time.minutes = n;
	std::string logentry;
	std::getline(stream, logentry);
	logs[datetime] = logentry;
}

void readLines(const std::string& filename, std::vector<DateTime>& entries, std::unordered_map<DateTime, std::string>& logs) {
	auto file = std::ifstream{ "../../../../Day_04/" + filename };
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << "\n";
		auto temp = DateTime{};
		parse_logs(line, temp, logs);
		entries.push_back(temp);
	}

}


int main()
{
	auto entries = std::vector<DateTime>{};
	auto logs = std::unordered_map<DateTime, std::string>{};
	auto sleep_logs = std::unordered_map<Date, std::map<Time, bool>>{};
	auto shift_logs = std::unordered_map<Date, int>{};

	readLines("input.txt", entries, logs);
	std::cout << entries.size() << " " << logs.size();

	auto file = std::ofstream{ "../../../../Day_04/parsed.txt" };
	for (const auto& pair : logs) {
		file <<"[" <<pair.first.date.year << "-" << pair.first.date.month << "-" << pair.first.date.Day << " " 
					<< pair.first.time.hours << ":" << pair.first.time.minutes << "] " << pair.second +"\n";
	}
}
