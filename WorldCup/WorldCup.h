#ifndef WORLD_CUP_H
#define WORLD_CUP_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "Team.h"
#include "Schedule.h"
using namespace std;

class WorldCup
{
public:
	WorldCup(int, const vector<Team*>&);
	vector<Team*> getQualifiedTeams();
	vector<Team*> get32teams() const;
	void setHost(Team*);
	Team* getHost() const;
	void goToNextRound();
	int getRound() const;
	vector<vector<Team*>> getPots();
	vector<vector<Team*>> getGroups();
 	map<Date, vector<Schedule>> getSchedulesByDate();
	map<char, vector<Schedule>> getSchedulesByStage();
private:
	const int year;
	int round;
	Team* host;
	vector<Team*> qualifiedTeams;
	vector<vector<Team*>> pots, groups;
};

string trim(string);

#endif // WORLD_CUP_H
