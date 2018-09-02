#include "stdafx.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include "WorldCup.h"
using namespace std;


WorldCup::WorldCup(int y, const vector<Team*>& teams32) 
	: year(y), 
	round(16), 
	host(nullptr),
	qualifiedTeams(64) {
	std::copy_backward(teams32.begin(), teams32.end(), qualifiedTeams.end());
}

vector<Team*> WorldCup::getQualifiedTeams() {
	int b = round == 0 ? 1 : round * 2;
	return vector<Team*>(qualifiedTeams.begin() + b, qualifiedTeams.begin() + b * 2);
}

vector<Team*> WorldCup::get32teams() const
{
	return vector<Team*>(qualifiedTeams.rbegin(), qualifiedTeams.rbegin() + 32);
}

void WorldCup::setHost(Team * team)
{
	host = team;
}
Team* WorldCup::getHost() const {
	return host;
}

vector<pair<string, string>> readMatches() {
	fstream fin("schedule/scheduleRule8.txt");
	string tmp;
	string t1, t2;
	vector<pair<string, string>> res;
	while (fin >> tmp)
	{
		fin >> tmp >> t1 >> t2;
		getline(fin, tmp);
		res.push_back(std::make_pair(t1, t2));
	}
	return res;
}
void WorldCup::goToNextRound()
{
	if (round == 16)
	{
		for (auto& group : groups) {
			sort(group.begin(), group.end(), [](Team* a, Team* b) {
				int score_a = a->getWon() * 3 + a->getDraw();
				int score_b = b->getWon() * 3 + b->getDraw();
				return score_a > score_b ||
					(score_a == score_b && a->getRank() < b->getRank());
			});
		}
		//Ð¡×éÈü
		int i = round;
		vector<pair<string, string>> matches = readMatches();
		for (auto& two_teams : matches) {
			Team *a = groups[two_teams.first[0] - 'A'][two_teams.first[1] - '0' - 1];
			Team *b = groups[two_teams.second[0] - 'A'][two_teams.second[1] - '0' - 1];
			qualifiedTeams[i] = a;
			qualifiedTeams[i + 1] = b;
			i += 2;
		}
	}
	else {
		for (int i = round; i < round * 2; i++) {
			int winner = qualifiedTeams[i * 2]->getWon() ? i * 2 : (i * 2 + 1);
			qualifiedTeams[i] = qualifiedTeams[winner];
		}
	}
	for (int i = round * 2; i < round * 4; i++) {
		qualifiedTeams[i]->clear();
	}
	round /= 2;
}

int WorldCup::getRound() const
{
	return round;
}

vector<vector<Team*>> WorldCup::getPots() {
	if (pots.empty())
	{
		vector<Team*> tmp;
		tmp.reserve(32);
		tmp = getQualifiedTeams();
		sort(tmp.begin(), tmp.end(), [this](Team* a, Team* b) {
			return a == host || (b != host && a->getRank() < b->getRank());
		});

		for (auto cur = tmp.begin(); cur != tmp.end(); cur += 8)
		{
			pots.push_back(vector<Team*>(cur, cur + 8));
		}
	}
	return pots;
}

bool ok(const vector<vector<Team*>>& pots, int row, int j) {
	std::map<string, int> count;
	for (int i = 0; i <= row; ++i)
	{
		string s = pots[i][j]->confederation();
		int k = ++count[s];
		if(k > 1) {
			if(s == "UEFA") {
				if(k > 2) {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}
	return true;
}
vector<vector<Team*>> WorldCup::getGroups() {
	if (groups.empty())
	{
		vector<vector<Team*>> pots = getPots();
		groups = vector<vector<Team*>>(8, vector<Team*>(4));
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				int k = j;
				while (!ok(pots, i, j)) {
					k++;
					swap(pots[i][j], pots[i][k]);
				}
				groups[j][i] = pots[i][j];
			}
		}
	}
	return groups;
}

map<char, vector<Schedule>> WorldCup::getSchedulesByStage()
{
	map<Date, vector<Schedule>> schedule_by_date = getSchedulesByDate();
	vector<vector<Team*>> groups = getGroups();
	map<Team*, char> team_to_group;
	for (int i = 0; i < groups.size(); i++) {
		for (auto team : groups[i]) {
			team_to_group[team] = 'A' + i;
		}
	}
	map<char, vector<Schedule>> schedule_by_stage;
	for (const auto& item : schedule_by_date) {
		for (auto& schedule : item.second) {
			auto teams = schedule.getTeams();
			schedule_by_stage[team_to_group[teams.first]].push_back(schedule);
		}
	}
	return schedule_by_stage;
}

map<Date, vector<Schedule>> WorldCup::getSchedulesByDate() {
	map<Date, vector<Schedule>> schedules;
	Schedule schedule;
	int day, m;
	string month;
	string venue;
	ifstream fin("schedule/scheduleRule" + to_string(round) + ".txt");
	if (round > 4)
	{
		vector<vector<Team*>> groups = getGroups();
		string team1, team2;
		
		ifstream fin("schedule/scheduleRule" + to_string(round) + ".txt");

		while (fin >> day)
		{
			fin >> month >> team1 >> team2;
			getline(fin, venue);
			venue = trim(venue);
			if (month == "June")
			{
				m = 6;
			}
			else if (month == "July")
			{
				m = 7;
			}
			Date date(day, m, 2018);
			schedule.setDate(date);
			schedule.setTeams(groups[team1[0] - 'A'][team1[1] - '0' - 1],
				groups[team2[0] - 'A'][team2[1] - '0' - 1]);
			schedule.setVenue(venue);
			schedules[date].push_back(schedule);
		}

		fin.close();
	}
	else if (round != 0) {
		if (round == 1)
		{
			Team *first = qualifiedTeams[2];
			Team *second = qualifiedTeams[3]; 
			Team *third = qualifiedTeams[4] != first ? qualifiedTeams[4] : qualifiedTeams[5]; 
			Team *fourth = qualifiedTeams[6] != first ? qualifiedTeams[6] : qualifiedTeams[7];;
			bool flag = true;
			while (fin >> day) {
				fin >> month;
				getline(fin, venue);
				venue = trim(venue);
				if (month == "June")
				{
					m = 6;
				}
				else if (month == "July")
				{
					m = 7;
				}
				Date date(day, m, 2018);
				schedule.setDate(date);
				schedule.setVenue(venue);
				if (flag)
				{
					schedule.setTeams(third, fourth);
					flag = false;
				}
				else {
					schedule.setTeams(first, second);
					flag = true;
				}
				schedules[date].push_back(schedule);
			}
			
		}
		else
		{
			int t1, t2;
			while (fin >> day)
			{
				fin >> month >> t1 >> t2;
				getline(fin, venue);
				venue = trim(venue);
				if (month == "June")
				{
					m = 6;
				}
				else if (month == "July")
				{
					m = 7;
				}
				Date date(day, m, 2018);
				schedule.setDate(date);
				schedule.setVenue(venue);
				schedule.setTeams(qualifiedTeams[round * 2 + t1 - 1], 
					qualifiedTeams[round * 2 + t2 - 1]);
				schedules[date].push_back(schedule);
			}
		}
	}
	return schedules;
}

string trim(string s) {
	while (!s.empty() && isspace(s.front()))
	{
		s.erase(s.begin());
	}
	while (!s.empty() && isspace(s.back()))
	{
		s.pop_back();
	}
	return s;
}