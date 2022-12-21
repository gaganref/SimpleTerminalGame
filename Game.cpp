#include "Game.h"

// -------------------- Object class ----------------------

Object::Object() {} // REMOVE ME

Object::Object(string name, int value) {
	// IMPLEMENT ME
}

Object::~Object() {}

string Object::getName() const {
	// IMPLEMENT ME

	return ""; // dummy
}

int Object::getValue() const {
	// IMPLEMENT ME

	return -1; // dummy
}

string Object::print() const {
	// IMPLEMENT ME

	return ""; // dummy
}

void Object::use() {
	// IMPLEMENT ME

}

std::ostream& operator<<(std::ostream& os, const Object& o) {
	// IMPLEMENT ME

	return os;
}

// ------------------- Food class ----------------------

Food::Food(string name, int value) {
	// IMPLEMENT ME

}

Food::~Food() {}


// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) {
	// IMPLEMENT ME

}

Weapon::~Weapon() {}


// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) {
	// IMPLEMENT ME

}

Armour::~Armour() {}


// ------------------- Player class ----------------------

Player::Player() {} // REMOVE ME

Player::Player(string name) {
	// IMPLEMENT ME

}

Player::~Player() {}

string Player::getName() const {
	// IMPLEMENT ME

	return ""; // dummy
}

int Player::getHealth() const {
	// IMPLEMENT ME

	return -1; // dummy
}

int Player::getStamina() const {
	// IMPLEMENT ME

	return -1; // dummy
}

void Player::pickup(std::unique_ptr<Object> o) {
	// IMPLEMENT ME

}

string Player::getInventory() const {
	// IMPLEMENT ME

	return ""; // dummy
}

string Player::print() const {
	// IMPLEMENT ME

	return ""; // dummy
}

bool Player::use(string name) {
	// IMPLEMENT ME

	return false; // dummy
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	// IMPLEMENT ME

	return os;
}

// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) {
	// IMPLEMENT ME

}

Fighter::~Fighter() {}

bool Fighter::attack(Player& other) {
	// IMPLEMENT ME

	return false; // dummy

}

// ------------------- Healer class ----------------------

Healer::Healer(string name) {
	// IMPLEMENT ME

}

Healer::~Healer() {}

bool Healer::heal(Player& other) {
	// IMPLEMENT ME

	return false; // dummy
}
