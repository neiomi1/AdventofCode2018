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
#include <chrono>

DateTime parse_logs(const std::string& line, std::unordered_map<DateTime, std::string>& logs) {
	DateTime parsedDateTime = DateTime{};
	auto stream = std::istringstream{ line };
	char c;
	stream >> c >> parsedDateTime.date.year;
	stream >> c >> parsedDateTime.date.month;
	stream >> c >> parsedDateTime.date.day;
	stream >> parsedDateTime.time.hours;
	stream >> c >> parsedDateTime.time.minutes >> c;
	std::string logentry;
	std::getline(stream, logentry);
	logs[parsedDateTime] = logentry;

	return parsedDateTime;
}

void read_lines(const std::string& filename, std::vector<DateTime>& entries, std::unordered_map<DateTime, std::string>& logs) {
	auto file = std::ifstream{ "../../../../Day_04/" + filename };
	std::string line;
	while (std::getline(file, line)) {
		//std::cout << line << "\n";
		auto temp = parse_logs(line, logs);
		entries.push_back(temp);
	}
	std::sort(entries.begin(), entries.end());
}

void parse_guards(std::vector<DateTime>& entries, std::unordered_map<DateTime, std::string>& logs, std::unordered_map<Date, int>& shift_logs, std::unordered_map<int, std::map<int, int>>& sleep_logs, std::unordered_map<int, int>& guard_sleep_minutes) {
	int guard_id;
	int sleep_minute;
	std::string str;
	char c;
	for (auto& entry : entries) {
		const auto& message = logs[entry];
		//std::cout << message+"\n";
		if (message.find("Guard") != std::string::npos) {
			auto stream = std::istringstream{ message };
			stream >> str >> c >> guard_id;
			if (entry.time.hours == 23) {
				shift_logs[entry.date.nextDay()] = guard_id;
			}
			else {
				shift_logs[entry.date] = guard_id;
			}
		}
		else if (message.find("asleep") != std::string::npos) {
			sleep_minute = entry.time.minutes;
		}
		else {
			for (sleep_minute; sleep_minute < entry.time.minutes; sleep_minute++) {
				sleep_logs[guard_id][sleep_minute]++;
				guard_sleep_minutes[guard_id]++;
			}
		}
	}
}

int part_one(std::unordered_map<int, int>& guard_sleep_minutes, std::unordered_map<int, std::map<int, int>>& sleep_logs) {
	int max = 0;
	int sleepy_guard_id;
	for (const auto& [guard_id, minutes] : guard_sleep_minutes) {
		//std::cout << "Guard #" << guard_id << " slept " << minutes << " minutes \n";
		if (minutes > max) {
			sleepy_guard_id = guard_id;
			max = minutes;
		}
	}
	int most_sleepy_minute = 0;
	max = 0;
	for (const auto& [minute, amount] : sleep_logs[sleepy_guard_id]) {
		//std::cout << minute << " : " << amount << "\n";
		if (amount > max) {
			max = amount;
			most_sleepy_minute = minute;
		}
	}
	//std::cout << "Guard #" << sleepy_guard_id << " slept the most at minute " << most_sleepy_minute << "\n";
	return most_sleepy_minute * sleepy_guard_id;
}


int part_two(std::unordered_map<int, std::map<int, int>>& sleep_logs) {
	int max = 0;
	int sleepy_guard = 0;
	int sleepy_minute = 0;
	for (const auto& [guard_id, sleep_map] : sleep_logs) {
		for (const auto& [minute, amount] : sleep_map) {
			if (amount > max) {
				max = amount;
				sleepy_minute = minute;
				sleepy_guard = guard_id;
			}
		}
	}
	std::cout << "Guard #" << sleepy_guard << " slept " << max << " times at minute " << sleepy_minute << "\n";
	return sleepy_guard * sleepy_minute;
}

int main()
{
	auto entries = std::vector<DateTime>{};
	auto logs = std::unordered_map<DateTime, std::string>{};
	auto sleep_logs = std::unordered_map<int, std::map<int, int>>{}; //Guard id - Minute - Nr.Asleep
	auto shift_logs = std::unordered_map<Date, int>{};
	auto guard_sleep_minutes = std::unordered_map<int, int>{};

	auto file_time = std::ofstream{ "../../../../Day_04/execution_times.txt" };
	auto file = std::ofstream{ "../../../../Day_04/parsed.txt" };
	auto file_sleep = std::ofstream{ "../../../../Day_04/guards_sleep.txt" };

	
	auto start = std::chrono::high_resolution_clock::now();
	read_lines("input.txt",entries, logs);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	parse_guards(entries, logs, shift_logs, sleep_logs, guard_sleep_minutes);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Guards parsed in: " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	int answer_part_one = part_one(guard_sleep_minutes, sleep_logs);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one done in: " << duration.count() << " microseconds.\n";

	std::cout << "Part one: " << answer_part_one << "\n";



	start = std::chrono::high_resolution_clock::now();
	int answer_part_two = part_two(sleep_logs);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two done in: " << duration.count() << " microseconds.\n";

	std::cout << "Part two: " << answer_part_two << "\n";

	for (const auto& [guard_id, m_map] : sleep_logs) {
		for (const auto& [minute, amount] : m_map) {
			file_sleep << guard_id << "  " << minute << "  " << amount << "\n";
		}
	}

	for (const auto& entry : entries) {
		auto message = logs[entry];
		file << "[" << entry.date.year << "-" << entry.date.month << "-" << entry.date.day << " "
			<< entry.time.hours << ":" << entry.time.minutes << "]" << "   " + message + "\n";
	}
}
