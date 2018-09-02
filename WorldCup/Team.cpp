#include "stdafx.h"
#include "Team.h"

Team::Team()
{
	_win = _lose = _draw = 0;
	total_win = total_lose = total_draw = 0;
	goal_scored = goal_against = 0;
	total_goal_scored = total_goal_against = 0;
}

void Team::setConfederation(const string& confederation) {
	_confederation = confederation;
}
void Team::setCountry(const string& country) {
	_country = country;
}
void Team::setRank(int r) {
	rank = r;
}
void Team::addPlayer(Player* player) {
	_players[player->position()].insert(player);
}
void Team::removePlayer(Player* player) {
	_players[player->position()].erase(player);
}
void Team::win() {
	++_win;
}
void Team::lose() {
	++_lose;
}
void Team::draw() {
	++_draw;
}
void Team::addGoalsScored(int goals) {
	goal_scored += goals;
}
void Team::addGoalsAgainst(int goals) {
	goal_against += goals;
}

const string& Team::confederation() const {
	return _confederation;
}
const string& Team::country() const {
	return _country;
}

void Team::addSpecialPositonPlayers(string position, int n, vector<Player*>& match_players) const
{
	const set<Player*> players_at_position = _players.at(position);
	auto it = players_at_position.begin();
	while (n-- && it != players_at_position.end())
	{
		match_players.push_back(*it);
		it++;
	}
}
vector<Player*> Team::players(int gk, int df, int mf, int fw) const {
	vector<Player*> match_players;
	map<string, int> number_of_players_in_position;
	number_of_players_in_position["GK"] = gk;
	number_of_players_in_position["DF"] = df;
	number_of_players_in_position["MF"] = mf;
	number_of_players_in_position["FW"] = fw;
	for (auto& item : number_of_players_in_position) {
		addSpecialPositonPlayers(item.first, item.second, match_players);
	}
	return match_players;
	
}
int Team::getWon() const {
	return _win;
}
int Team::getLost() const {
	return _lose;
}
int Team::getDraw() const {
	return _draw;
}
int Team::getGoalsScored() const {
	return goal_scored;
}
int Team::getGoalsAgainst() const {
	return goal_against;
}
int Team::getRank() const {
	return rank;
}

int Team::getTotalWon() const
{
	return total_win;
}

int Team::getTotalLost() const
{
	return total_lose;
}

int Team::getTotalDraw() const
{
	return total_draw;
}

int Team::getTotalGoalsScored() const
{
	return total_goal_scored;
}

int Team::getTotalGoalsAgainst() const
{
	return total_goal_against;
}

void Team::clear()
{
	total_win += _win;
	total_draw += _draw;
	total_lose += _lose;
	total_goal_scored += goal_scored;
	total_goal_against += goal_against;
	_win = _lose = _draw = goal_against = goal_scored = 0;
}
