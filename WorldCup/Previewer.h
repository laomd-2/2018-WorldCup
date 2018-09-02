#pragma once
#include <ostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Schedule.h"
#include "Team.h"
using namespace std;

class Previewer 
{
	static void printResultTitle(ostream&);
	static void printTeamInformation(ostream&, Team*);
	static void printSchedule(ostream&, const Schedule&);
	static void show_live(ostream& fout,Team* teamA);
	static void randomPlay(ostream& fout,Team* teamA, Team* teamB);
public:
	static void print(ostream&, vector<vector<Team*>>, const Team*, string, char);
	static void printQualifiedTeams(ostream&, const map<string, vector<Team*>>&, const Team*);
	static void printSchedulesByStage(ostream&, map<char, vector<Schedule>>);
	static void printMatchResult(ostream&, const vector<vector<Team*>>&, int);
	static void printMatchResult(ostream&, const vector<Team*>&);
	static void printLive(ostream&,const map<Date,vector<Schedule>>,int);//直播比赛过程
	static void printQualified(ostream&, const vector<Team*>);//晋级的16支队伍
	static void printSchedulesByDate(ostream&, map<Date, vector<Schedule>>,int);//8分1决赛，即16进8的日程安排
	static void printScorerList(ostream&, vector<Player*>);
	static void printTopTen(ostream&, vector<Team*>);
	static void printLiveOnScreen(istream&);
};

