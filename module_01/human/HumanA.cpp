
#include "HumanA.hpp"

HumanA::HumanA(const std::string &name, Weapon &weapon)
    : _name(name), _weapon(weapon) {
  if (_weapon.getType().empty()) {
    throw std::invalid_argument("Weapon type cannot be empty for human A.");
  }
  std::cout << "Human A " << _name << " entered the game" << std::endl;
}

HumanA::~HumanA() { std::cout << _name << " died" << std::endl; }

void HumanA::attack() {
  std::cout << _name << " attacks with " << _weapon.getType() << std::endl;
}