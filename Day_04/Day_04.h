// Day_01.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include <functional>
#include <tuple>
// TODO: Reference additional headers your program requires here.



struct Date{
	int year = 0;
	int month = 0;
	int day = 0;


	Date nextDay() {
		Date temp = *this;
		temp.day++;
		switch (temp.month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
			temp.day = (temp.day > 31) ? 1 : temp.day;
			temp.month = (day == 1) ? temp.month + 1 : temp.month;
			break;
		case 2: temp.day = (temp.day > 28) ? 1 : temp.day;
			temp.month = (day == 1) ? temp.month + 1 : temp.month;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			temp.day = (temp.day > 30) ? 1 : temp.day;
			temp.month = (day == 1) ? temp.month + 1 : temp.month;
			break;
		case 12: temp.day = (temp.day > 31) ? 1 : temp.day;
			temp.month = (day == 1) ? 1 : temp.month;
			temp.year = (temp.month == 1) ? temp.year++ : temp.year;
			break;
		}
		return temp;
	}

	bool operator > (const Date& date)const {
		return std::tie(year, month, day) > std::tie(date.year, date.month, date.day);
	}

	bool operator < (const Date& date)const {
		return std::tie(year, month, day) < std::tie(date.year, date.month, date.day);
	}

	bool operator == (const Date& date)const {
		return !(*this > date || *this < date);
	}

	bool operator <= (const Date& date)const {
		return !(*this > date);
	}

	bool operator >= (const Date& date)const {
		return !(*this < date);
	}

	bool operator != (const Date& date)const {
		return !(*this == date);
	}
};

struct Time {
	int hours = 0;
	int minutes = 0;

	bool operator > (const Time& time)const {
		return std::tie(hours, minutes) > std::tie(time.hours, time.minutes);
	}

	bool operator < (const Time& time)const {
		return std::tie(hours, minutes) < std::tie(time.hours, time.minutes);
	}

	bool operator == (const Time& time) const {
		return !(*this > time || *this < time);
	
	}

	bool operator >= (const Time& time)const {
		return !(*this < time);
	}

	bool operator <= (const Time& time)const {
		return !(*this > time);
	}

	bool operator != (const Time& time)const {
		return !(*this == time);
	}

};

struct DateTime {
	Date date = Date{};
	Time time = Time{};

	bool operator > (const DateTime& datetime)const {
		return std::tie(date, time) > std::tie(datetime.date, datetime.time);
	}

	bool operator < (const DateTime& datetime)const {
		return std::tie(date, time) < std::tie(datetime.date, datetime.time);
	}

	bool operator == (const DateTime& datetime)const {
		return !(*this > datetime || *this < datetime);
	}

	bool operator >= (const DateTime& datetime)const {
		return !(*this < datetime);
	}

	bool operator <= (const DateTime& datetime)const {
		return !(*this > datetime);
	}

	bool operator != (const DateTime& datetime)const {
		return !(*this == datetime);
	}
};


namespace std {



	template<>
	struct hash<Date> {
		inline size_t operator()(const Date& date) const {
			int temp = date.year * 10000 + date.day + date.month * 100;
			size_t result = std::hash<int>{}(temp);
			//size_t result = std::hash<int>{}(date.year) ^ (std::hash<int>{}(date.month) << 1) ^ (std::hash<int>{}(date.Day) << 1);
			return result;
		}
	};

	template<>
	struct hash<Time> {
		inline size_t operator()(const Time& time) const {
			int temp = time.minutes + time.hours * 100;
			//size_t result = std::hash<int>{}(time.minutes) ^ (std::hash<int>{}(time.hours) << 1);
			size_t result = std::hash<int>{}(temp);
			return result;
		}
	};

	template<>
	struct hash<DateTime> {
		inline size_t operator()(const DateTime& datetime) const {
			std::size_t seed = 0UL;
			seed ^= std::hash<Date>{}(datetime.date) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= std::hash<Time>{}(datetime.time) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}


