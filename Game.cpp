#include "Game.h"

#include <utility>

// -------------------- Object class ----------------------

Object::Object(string name, int value) {
	if(value < 0){
        throw std::invalid_argument("Value should be a positive integer");
    }
    name_ = std::move(name);
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
	return (getObjectType() + ", name: " + name_ + ", value: " + std::to_string(value_));
}

std::ostream& operator<<(std::ostream& os, const Object& o) {
    os << o.print();
	return os;
}

// ------------------- Food class ----------------------

Food::Food(string name, int value) : Object(std::move(name), value){
}

Food::~Food() {}

void Food::use() {
    if(owner_ == nullptr){
        return;
    }

    int target_stamina = owner_->getStamina() + value_;
    if(target_stamina > 100){
        target_stamina = 100;
    }

    owner_->setStamina(target_stamina);
    owner_->removeInventoryItem(this);
}

string Food::getObjectType() const {
    return "Food";
}

// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) : Object(std::move(name), value) {
}

Weapon::~Weapon() {}

void Weapon::use() {
    if(owner_ == nullptr){
        return;
    }

    owner_->setWeaponInUse(this);
}

string Weapon::getObjectType() const {
    return "Weapon";
}


// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) : Object(std::move(name), value) {
}

Armour::~Armour() {}

void Armour::use() {
    if(owner_ == nullptr){
        return;
    }

    owner_->addArmourInUse(this);
}

string Armour::getObjectType() const {
    return "Armour";
}

// ------------------- Player class ----------------------

Player::Player(string name) {
	name_ = std::move(name);
    health_ = 100;
    stamina_ = 100;
    weapon_in_use_ = nullptr;
}

Player::~Player() {}

string Player::getName() const {
	return name_;
}

int Player::getHealth() const {
	return health_;
}

int Player::getStamina() const {
    return stamina_;
}

void Player::setHealth(const int health) {
    if(health <= 0){
        health_ = 0;
        return;
    }
    if(health >= 100){
        health_ = 100;
        return;
    }

    health_ = health;
}

void Player::setStamina(const int stamina) {
    stamina_ = stamina;
}

void Player::setWeaponInUse(Weapon* weapon) {
    weapon_in_use_ = weapon;
}

void Player::addArmourInUse(Armour *armour) {
    armour_in_use_.push_back(armour);
}

void Player::pickup(std::unique_ptr<Object> o) {
    if(health_ <= 0){
        throw std::logic_error("Player is already dead!");
    }
    o->owner_ = this;
    inventory_.push_back(std::move(o));
}

string Player::getInventory() const {

    string out_string = "List of items:";

    if(inventory_.empty()){
        out_string += " none";
    }
    else{
        out_string += "\n";
        int itr = 0;
        for(auto& element : inventory_){
            out_string += " " + element->print();
            if(itr < inventory_.size() - 1){
                out_string += "\n";
            }
            itr++;
        }
    }

	return out_string;
}

string Player::print() const {
    string out_string = "Name: " + name_ + "\nType: " + getPlayerType();
    out_string += "\nHealth: " + std::to_string(health_);
    out_string += "\nStamina: " + std::to_string(stamina_);
    out_string += "\n" + getInventory();

	return out_string;
}

bool Player::use(string name) {
    if(health_ <= 0){
        throw std::logic_error("Player is already dead!");
    }

    for(auto& element : inventory_){
        if(element->getName() == name){
            element->use();
            return true;
        }
    }

	return false;
}

void Player::removeInventoryItem(Object *obj) {
    for(auto itr = inventory_.begin(); itr != inventory_.end(); ++itr )
    {
        if(itr->get() == obj )
        {
            inventory_.erase(itr);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.print();
	return os;
}

string Player::getArmourInfo() const {
    string out_string = "Armour in use: ";

    if(armour_in_use_.empty()){
        out_string += "none";
    }
    else{
        int itr = 0;
        for(auto& element : armour_in_use_){
            out_string += element->getName();
            if(itr < armour_in_use_.size() - 1){
                out_string += ", ";
            }
            itr++;
        }
    }

    return out_string;
}

int Player::getDefendingStrength() {
    int defending_strength = 0;
    for(auto& element : armour_in_use_){
        defending_strength += element->value_;
    }
    return defending_strength;
}

// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) : Player(std::move(name)) {}

Fighter::~Fighter() {}

bool Fighter::attack(Player& other) {
    if(health_ <= 0){
        throw std::logic_error("Player is already dead!");
    }
    if(other.getHealth() <= 0){
        throw std::logic_error("Stop! " + other.getName() + " is already dead.");
    }
    if(stamina_ < 10){
        return false;
    }

    stamina_ -= 10;
    int attack_strength = 10;
    if(weapon_in_use_ != nullptr){
        attack_strength += weapon_in_use_->getValue();
    }

    if(attack_strength <= other.getDefendingStrength()){
        return false;
    }

    other.setHealth(other.getHealth() - (attack_strength - other.getDefendingStrength()));
	return true;
}

string Fighter::print() const {
    string out_string = Player::print();
    out_string += "\nWeapon in use: ";
    if(weapon_in_use_ != nullptr){
        out_string += weapon_in_use_->getName();
    }
    else{
        out_string += "none";
    }
    out_string += "\n" + getArmourInfo();
    return out_string;
}

string Fighter::getPlayerType() const {
    return "Fighter";
}

// ------------------- Healer class ----------------------

Healer::Healer(string name) : Player(std::move(name)){}

Healer::~Healer() {}

bool Healer::heal(Player& other) {
    if(health_ <= 0 || other.getHealth() <= 0){
        throw std::logic_error("Player is already dead!");
    }
    if(stamina_ < 10){
        return false;
    }

    stamina_ -= 10;

    if(other.getHealth() == 100){
        return false;
    }

    other.setHealth(other.getHealth() + 20);

	return true;
}

string Healer::print() const {
    return (Player::print() + "\n" + getArmourInfo());
}

string Healer::getPlayerType() const {
    return "Healer";
}
