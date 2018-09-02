#include "stdafx.h"
#include "Schedule.h"
Schedule::Schedule()
{
	team1 = team2 = nullptr;
}
void Schedule::setDate(const Date& date) {
	this->date = date;
}	
void Schedule::setVenue(const string& venue) {
	this->venue = venue;
}
void Schedule::setTeams(Team* team1, Team* team2) {
	this->team1 = team1;
	this->team2 = team2;
}
const Date& Schedule::getDate() const {
	return date;
}
const string& Schedule::getVenue() const {
	return venue;
}
std::pair<Team*, Team*> Schedule::getTeams() const {
	return std::make_pair(team1, team2);
}

Date::Date(int d, int m, int y) : _day(d), _month(m), _year(y) {
	
}
int Date::year() const {
	return _year;
}
int Date::month() const {
	return _month;
}
int Date::day() const {
	return _day;
}

bool operator<(const Date &a, const Date &b)
{
	return a.year() < b.year() ||
		(a.year() == b.year() && a.month() < b.month()) ||
		(a.month() == b.month() && a.day() < b.day());
}
