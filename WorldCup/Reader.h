#pragma once
#include <map>
#include <string>
#include <vector>
using namespace std;

class Player;
class Team;
class Reader
{
public:
	static std::map<string, int> readRank();
	static vector<Player*> readPlayers(const string&);
	static map<string, vector<Team*>> readTeams();
};

extern string trim(string);
