#ifndef TEAM_H
#define TEAM_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "Player.h"
using namespace std;

class Team
{
	void addSpecialPositonPlayers(string, int, vector<Player*>&) const;
public:
	Team();
	void setConfederation(const string&);
	void setCountry(const string&);
	void setRank(int);
	void addPlayer(Player*);
	void removePlayer(Player*);
	void win();
	void lose();
	void draw();
	void addGoalsScored(int=1);
	void addGoalsAgainst(int=1);

	const string& confederation() const;
	const string& country() const;
	vector<Player*> players(int=1,int=4,int=3,int=3) const;
	int getWon() const;
	int getLost() const;
	int getDraw() const;
	int getGoalsScored() const;
	int getGoalsAgainst() const;
	int getRank() const;
	int getTotalWon() const;
	int getTotalLost() const;
	int getTotalDraw() const;
	int getTotalGoalsScored() const;
	int getTotalGoalsAgainst() const;
	void clear();
private:
	string _confederation, _country;
	map<string, set<Player*>> _players;
	int rank;
	int _win, _lose, _draw;
	int total_win, total_lose, total_draw;
	int goal_scored, goal_against;
	int total_goal_scored, total_goal_against;
};
#endif // TEAM_H
