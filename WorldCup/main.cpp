#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "WorldCup.h"
#include "Previewer.h"
#include "Reader.h"
using namespace std;

class Output : public ostream
{
public:
	Output(ostream& a, ostream& b) : fout1(a), fout2(b) {

	}
	template<typename T>
	ostream& operator<<(const T& t) {
		fout1 << t;
		fout2 << t;
		return *this;
	}
private:
	ostream& fout1;
	ostream& fout2;
};

int main(int argc, char const *argv[])
{
	const string host_country = "Russia";
	
	map<string, vector<Team*>> qualified_teams = Reader::readTeams();
	vector<Team*> teams32;
	Team* host = nullptr;
	for (auto& item : qualified_teams) {
		for (auto i : item.second) {
			teams32.push_back(i);
			if (i->country() == host_country) {
				host = i;
			}
		}
	}
	WorldCup w(2018, teams32);
	w.setHost(host);
	w.getHost()->setCountry(w.getHost()->country() + " (hosts)");

	ofstream fout;
	fout.open("result/team32.txt");
	if (!fout.is_open()) {
		system("mkdir result");
		fout.open("result/team32.txt");
	}
	Previewer::printQualifiedTeams(fout, qualified_teams, w.getHost());
	fout.close();

	fout.open("result/finalDraw.txt");
	fout << "First stage:" << endl;
	Previewer::print(fout, w.getPots(), w.getHost(), "pots", '1');

	fout << "The Final Draw:" << endl;
	auto g = w.getGroups();
	Previewer::print(fout, g, w.getHost(), "group ", 'A');
	fout.close();

	fout.open("schedule/schedule16.txt");
	
	map<Date, vector<Schedule>> schedules_by_date = w.getSchedulesByDate();
	map<char, vector<Schedule>> schedules_bt_stage = w.getSchedulesByStage();
	fout << "Matches by stage" << endl;
	Previewer::printSchedulesByStage(fout, schedules_bt_stage);
	fout << endl;
	fout.close();

	int round = w.getRound();
	vector<Team*> qualified;
	while (round>0)
	{
		string str_round = to_string(round)+ ".txt";
		fout.open("schedule/schedule"+ str_round);
		fout << "Matches by date" << endl;

		Previewer::printSchedulesByDate(fout, schedules_by_date,round);
		fout << endl;
		fout.close();

		fout.open("live/simulationLog"+ str_round );
		Output out(fout, cout);
		Previewer::printLive(out, schedules_by_date,round);
		fout.close();

		/*ifstream fin("live / simulationLog" + str_round);
		Previewer::printLiveOnScreen(fin);
		fin.close();*/

		fout.open("result/Result"+ str_round);
		if (round > 4) {
			Previewer::printMatchResult(fout, w.getGroups(), w.getRound());
		}
		else {
			if (round != 1)
			{
				qualified = w.getQualifiedTeams();
			}
			Previewer::printMatchResult(fout, qualified);
		}
		
		fout.close();
		w.goToNextRound();
		
		schedules_by_date = w.getSchedulesByDate();
		fout.open("result/team"+str_round);
		fout << "Qualified for round of "+ to_string(round) +":" << endl;
		Previewer::printQualified(fout, w.getQualifiedTeams());
		fout.close();
		round = w.getRound();


	}
	fout.open("result/finalStastics.txt");
	vector<Team*> all_teams = w.get32teams();
	Previewer::printTopTen(fout, all_teams);
	fout << endl << endl;
	vector<Player*> all_players;
	for (auto each_team : all_teams)
	{
		vector<Player*> v = each_team->players();
		std::copy(v.begin(), v.end(), std::back_inserter(all_players));
	}
	Previewer::printScorerList(fout,all_players);

	return 0;
}