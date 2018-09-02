#include "stdafx.h"
#include <fstream>
#include "Reader.h"
#include "Team.h"
#include "Player.h"

std::map<string, int> Reader::readRank() {
	map<string, int> top_teams;
	string country;
	ifstream fin("fifaRanking/ranking.txt");
	int i = 1;
	while (getline(fin, country)) {
		top_teams[country] = i++;
	}
	fin.close();
	return top_teams;
}

vector<Player*> Reader::readPlayers(const string& country) {
	vector<Player*> players;
	ifstream fin("players/" + country + ".txt");
	int number;
	string position, name;
	while (fin >> number)
	{
		fin >> position;
		getline(fin, name);
		name = trim(name);
		Player* player = new Player;
		player->setName(name);
		player->setNumber(number);
		player->setPosition(position);
		players.push_back(player);
	}
	return players;
}
map<string, vector<Team*>> Reader::readTeams() {
	static const vector<string> confederations = { "AFC", "CAF", "UEFA", "OFC",
		"CONCACAF", "CONMEBOL" };

	static map<string, vector<Team*>> qualifiedTeams;
	static map<string, int> rank = readRank();

	if (qualifiedTeams.empty()) {
		for (const string& confederation : confederations) {
			ifstream fin("qualifiedTeams/" + confederation + ".txt");
			string country;
			while (getline(fin, country)) {
				Team* team = new Team;
				vector<Player*> players = readPlayers(country);
				team->setConfederation(confederation);
				team->setCountry(country);
				team->setRank(rank[country]);
				for (auto player : players) {
					team->addPlayer(player);
				}
				qualifiedTeams[confederation].push_back(team);
			}
			fin.close();
		}
	}
	return qualifiedTeams;
}