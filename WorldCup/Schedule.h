#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include "Team.h"
using namespace std;

class Date
{
public:
	Date() = default;
	Date(int, int, int);
	int year() const;
	int month() const;
	int day() const;

private:
	int _day, _year;
	int _month;
};

bool operator<(const Date&, const Date&);

class Schedule
{
public:
	Schedule();
	void setDate(const Date&);
	void setVenue(const string&);
	void setTeams(Team*, Team*);
	const Date& getDate() const;
	const string& getVenue() const;
	std::pair<Team*, Team*> getTeams() const;
private:
	Date date;
	string venue;
	Team *team1, *team2;
};



#endif // SCHEDULE_H
