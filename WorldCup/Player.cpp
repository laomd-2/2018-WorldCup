#include "stdafx.h"
#include "Player.h"
void Player::setName(const string& name) {
	_name = name;
}
void Player::setPosition(string position)
{
	_position = position;
}
void Player::setNumber(int number)
{
	_number = number;
}
void Player::addGoals(int goals) {
	_goals += goals;
}
const string& Player::name() const {
	return _name;
}
const string & Player::position() const
{
	return _position;
}
int Player::number() const
{
	return _number;
}
int Player::numberOfGoals() const {
	return _goals;
}
