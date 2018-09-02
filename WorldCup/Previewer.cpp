#include "stdafx.h"
#include "Previewer.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
using namespace std;

void Previewer::print(ostream& fout, vector<vector<Team*>> v, const Team* host, string s, char first) {
	for (int i = 0; i < v.size(); ++i)
	{
		fout << s << char(first + i) << endl;
		sort(v[i].begin(), v[i].end(), [host](const Team* a, const Team* b) {
			return a == host || (b != host && a->country() < b->country());
		});
		for (auto&& team : v[i]) {
			fout << "  " << team->country() << endl;
		}
	}
	fout << endl;
}

void Previewer::printQualifiedTeams(ostream& fout, const map<string, vector<Team*>>& qualifiedTeams, const Team* host) {
	for (auto&& item : qualifiedTeams) {
		fout << item.first << '(' << item.second.size() << ')' << endl;
		vector<Team*> teams = item.second;
		sort(teams.begin(), teams.end(), [](const Team* a, const Team* b) {
			return a->country() < b->country();
		});
		for (auto&& i : teams) {
			fout << "  " << i->country() << " (" << i->getRank() << ')' << endl;
		}
	}
}

void Previewer::printResultTitle(ostream &fout)
{
	fout << left << setw(15) << "Team"
		<< setw(3) << 'W' << setw(3) << 'D' << setw(3) << 'L'
		<< setw(4) << "GF" << setw(4) << "GA" << setw(4) << "GD"
		<< setw(5) << "Pts" << endl;
}

void Previewer::printTeamInformation(ostream &fout, Team *team)
{
	int win = team->getWon();
	int lost = team->getLost();
	int draw = team->getDraw();
	int gf = team->getGoalsScored();
	int ga = team->getGoalsAgainst();
	fout << setw(15) << team->country()
		<< setw(3) << win << setw(3) << draw << setw(3) << lost
		<< setw(4) << gf << setw(4) << ga << setw(4) << gf - ga
		<< setw(5) << win * 3 + draw << endl;
}

void Previewer::printSchedule(ostream& fout, const Schedule& schedule) {
	auto teams = schedule.getTeams();
	fout << ' ' << teams.first->country() << " vs " << teams.second->country() << ", "
		<< schedule.getVenue();
}



void Previewer::printSchedulesByStage(ostream & fout, map<char, vector<Schedule>> schedules)
{
	for (auto& item : schedules) {
		fout << "Group " << ' ' << item.first << endl;
		for (auto& schedule : item.second) {
			printSchedule(fout, schedule);
			fout << ", " << /*schedule->getDate().month()*/"June" << ' ' 
				<< schedule.getDate().day() << endl;
		}
		fout << endl;
	}
}

void Previewer::printMatchResult(ostream& fout, const vector<vector<Team*>>& groups_of_teams, int round)
{
	for (int i = 0; i < groups_of_teams.size(); i++)
	{
		fout << "Final result for group " << char('A' + i) << endl;
		printResultTitle(fout);
		for (int j = 0; j < round / 4; j++) {
			Team* team = groups_of_teams[i][j];
			printTeamInformation(fout, team);
		}
		fout << endl;
	}
}

void Previewer::printMatchResult(ostream& fout, const vector<Team*>& teams) {
	printResultTitle(fout);
	for (auto team : teams) {
		printTeamInformation(fout, team);
	}
}

void Previewer::printLive(ostream& fout,const map<Date,vector<Schedule>> matches_by_date,int round)
{ 
	srand(time(NULL));
	fout<< endl;
	bool is_final = false;
	for (auto schedule : matches_by_date)
	{
		if (round == 1)
		{
			if (is_final)
			{
				fout << "This is the final match!" << endl;
			}
			else
			{
				fout << "This is the Play-off game." << endl;
				is_final = true;
			}
		}
		fout << (schedule.first.month() == 6?"June":"July")<< " " << schedule.first.day() << "-----------------------------------------" << endl;//题目没要求，我自己加的方便检查


			for (auto each_match : schedule.second)//每场比赛的详细内容
			{
				fout << "Group stage:" << endl;
				Team* teamA = each_match.getTeams().first;
				Team* teamB = each_match.getTeams().second;
				fout << teamA->country() << " vs " << teamB->country() << endl;
				fout << teamA->country() << endl;
				for (auto players : teamA->players())//vector<Player*>，打印teamA队员信息
				{
					fout << "#"<<players->number() << "," <<" " << players->name() << "," << players->position() << endl;
				}
				fout << teamB->country() << endl;
				for (auto players : teamB->players())//vector<Player*>，打印teamB队员信息
				{
					fout <<"#"<< players->number() << "," << " " << players->name() << "," << players->position() << endl;
				}
				randomPlay(fout,teamA, teamB);
			}


	}
}
void Previewer::printQualified(ostream &fout, const vector<Team*> qualified_teams)
{
	for (auto team : qualified_teams)
	{
		fout << team->country() << endl;
	}
}
void Previewer::printSchedulesByDate(ostream &fout, map<Date, vector<Schedule>> schedules,int round)
{
	bool is_final = false;
	for (auto each_day : schedules)
	{
		if (round == 1) {
			if (is_final) {
				fout << "This is the final match!" << endl;
			}
			else {
				is_final = true;
			}
		}
		fout << (each_day.first.month() == 6 ? "June" : "July");
		fout << " " << each_day.first.day() << endl;
		vector<Schedule> v = each_day.second;
		for (auto each_schedule : v)
		{
			fout << each_schedule.getTeams().first->country() << " vs " << each_schedule.getTeams().second->country() << " at " << each_schedule.getVenue() << endl;
		}
		fout << endl;
	}
}
void Previewer::printScorerList(ostream &fout, vector<Player*> all_players)
{
	stable_sort(all_players.begin(), all_players.end(), [](Player* a, Player* b)
	{
		return a->numberOfGoals() > b->numberOfGoals();
	}
	);
	fout << "Goalscores" << endl;
	int last = -1;
	for (auto player : all_players) {
		int goals = player->numberOfGoals();
		if (goals != last)
		{
			last = goals;
			if (last == 0)
			{
				break;
			}
			fout <<endl<< last << " goal";
			if (last > 1)
			{
				fout << 's';
			} 
			fout << endl;
		}
		fout << player->name() << ", " << player->position() << endl;
	}
}
void Previewer::printTopTen(ostream &fout, vector<Team*> all_teams)
{
	sort(all_teams.begin(), all_teams.end(), [](Team* a,Team* b)
	{
		int scoresA = a->getTotalDraw() + a->getTotalWon() * 3;
		int scoresB = b->getTotalDraw() + b->getTotalWon() * 3;
		return scoresA > scoresB || scoresA == scoresB&&a->getRank() < b->getRank();
	}
	);
	fout << "Top ten teams:" << endl;
	fout << left << setw(4) << ' ';
	printResultTitle(fout);
	for (int i = 0; i < 10; i++)
	{
		Team* team = all_teams[i];
		fout << setw(4) << (to_string(i+1) + ".");
		int win = team->getTotalWon();
		int lost = team->getTotalLost();
		int draw = team->getTotalDraw();
		int gf = team->getTotalGoalsScored();
		int ga = team->getTotalGoalsAgainst();
		fout << setw(15) << team->country()
			<< setw(3) << win << setw(3) << draw << setw(3) << lost
			<< setw(4) << gf << setw(4) << ga << setw(4) << gf - ga
			<< setw(5) << win * 3 + draw << endl;
		
	}
}
void Previewer::printLiveOnScreen(istream &fin)
{
	/*string content;
	getline(fin, content);
	cout << content << endl;
	while (!fin.eof())
	{

	}*/
}
void Previewer::randomPlay(ostream &fout,Team* teamA, Team* teamB)
{
	fout << "Playing..." << endl;
	int A_score = rand() % 8;//A队得分
	int B_score = rand() % 8;//B队得分
	teamA->addGoalsScored(A_score);
	teamA->addGoalsAgainst(B_score);
	teamB->addGoalsScored(B_score);
	teamB->addGoalsAgainst(A_score);
	int term;//得分轮流
	int a = 0, b = 0;
	while (a < A_score || b < B_score)
	{
		term = rand() % 2;
		if (a == A_score)//如果A队得分够了，剩下都让B队进
			term = 1;
		else if (b == B_score)//同理
			term = 0;
		if (term == 0)
		{
			show_live(fout,teamA);
			a++;
		}
		else
		{
			show_live(fout,teamB);
			b++;
		}
		fout << "Now it is " << a << ":" << b << endl;
	}
	fout << "It is a draw with " << A_score << ":" << B_score << endl << endl;
	if (A_score > B_score)
	{
		teamA->win();
		teamB->lose();
	}
	else if (A_score < B_score)
	{
		teamA->lose();
		teamB->win();
	}
	else
	{
		teamA->draw();
		teamB->draw();
	}
}

void Previewer::show_live(ostream& fout,Team * team)
{
	int player = rand() % 11;
	vector<Player*> players = team->players();
	fout << team->country() << " did a goal, and it was #" << players[player]->number() << ", ";
	fout << players[player]->name() << " did the goal." << endl;
	players[player]->addGoals();

}
 