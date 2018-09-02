#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player
{
public:
	void setName(const string&);
	//void setCountry(const string&);
	void setPosition(string);
	void setNumber(int);
	void addGoals(int=1);
	const string& name() const;
	//const string& country() const;
	const string& position() const;
	int number() const;
	int numberOfGoals() const;
private:
	string _name;
	string _country;
	int _goals = 0, _number;
	string _position;
};

#endif // PLAYER_H
