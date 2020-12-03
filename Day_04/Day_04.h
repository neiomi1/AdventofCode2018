// Day_01.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include <functional>
// TODO: Reference additional headers your program requires here.



struct Date{
	int year = 0;
	int month = 0;
	int Day = 0;

	inline bool operator > (const Date& date)const {
		if (this->year == date.year) {
			if (this->month == date.month) {
				return this->Day > date.Day;
			}
			return this->month > date.month;
		}
		return this->year > date.year;
	}

	inline bool operator < (const Date& date)const {
		if (this->year == date.year) {
			if (this->month == date.month) {
				return this->Day < date.Day;
			}
			return this->month < date.month;
		}
		return this->year < date.year;
	}

	inline bool operator == (const Date& date)const {
		return (*this > date || *this < date);
	}

	inline bool operator <= (const Date& date)const {
		return !(*this > date);
	}

	inline bool operator >= (const Date& date)const {
		return !(*this < date);
	}

	inline bool operator != (const Date& date)const {
		return !(*this == date);
	}
};

struct Time {
	int hours = 0;
	int minutes = 0;

	inline bool operator > (const Time& time)const {
		if (this->hours == time.hours) {
			return this->minutes > time.minutes;
		}
		return this->hours > time.hours;
	}

	inline bool operator < (const Time& time)const {
		if (this->hours == time.hours) {
			return this->minutes < time.minutes;
		}
		return this->hours < time.hours;
	}

	inline bool operator == (const Time& time) const {
		return (*this > time || *this < time);
	
	}

	inline bool operator >= (const Time& time)const {
		return !(*this < time);
	}

	inline bool operator <= (const Time& time)const {
		return !(*this > time);
	}

	inline bool operator != (const Time& time)const {
		return !(*this == time);
	}

};

struct DateTime {
	Date date = Date{};
	Time time = Time{};

	inline bool operator > (const DateTime& datetime)const {
		if (this->date == datetime.date) {
			return this->time > datetime.time;
		}
		return this->date > datetime.date;
	}

	inline bool operator < (const DateTime& datetime)const {
		if (this->date == datetime.date) {
			return this->time < datetime.time;
		}
		return this->date < datetime.date;
	}

	inline bool operator == (const DateTime& datetime)const {
		return (*this > datetime || *this < datetime);
	}

	inline bool operator >= (const DateTime& datetime)const {
		return !(*this < datetime);
	}

	inline bool operator <= (const DateTime& datetime)const {
		return !(*this > datetime);
	}

	inline bool operator != (const DateTime& datetime)const {
		return !(*this == datetime);
	}
};


namespace std {



	template<>
	struct hash<Date> {
		inline size_t operator()(const Date& date) const {
			int temp = date.year * 10000 + date.Day + date.month * 100;
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


