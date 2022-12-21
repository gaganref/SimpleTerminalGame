#include "Game.h"

// -------------------- Object class ----------------------

Object::Object(string name, int value) {
	if(value < 0){
        throw std::invalid_argument("Value should be a positive integer");
    }
    name_ = name;
    value_ = value;
    owner_ = nullptr;
}

Object::~Object() {}

string Object::getName() const {
	return name_;
}

int Object::getValue() const {
	return value_;
}

string Object::print() const {
	string out_string_ = object_name_ + ", name: " + name_ + ", value: " + std::to_string(value_);
	return out_string_;
}

void Object::use() {
	// IMPLEMENT ME

}

std::ostream& operator<<(std::ostream& os, const Object& o) {
    os << o.print();
	return os;
}

// ------------------- Food class ----------------------

Food::Food(string name, int value) : Object(name, value){
    object_name_ = "Food";
}

Food::~Food() {}

// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) : Object(name, value) {
    object_name_ = "Weapon";
}

Weapon::~Weapon() {}


// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) : Object(name, value) {
    object_name_ = "Armour";
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
