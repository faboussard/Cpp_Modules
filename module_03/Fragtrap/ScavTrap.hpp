#ifndef SCAVTRAP_H
#define  SCAVTRAP_H

#include <string>
#include <iostream>
#include "ClapTrap.hpp"


#define SCAVTRAP_ATTACK_MESSAGE(name, target, damage) \
    std::cout << "Scavtrap " << (name) << " attacks " << (target) << " causing " << (damage) << " points of damage!" << std::endl;

class ScavTrap : public ClapTrap
{
  public:
      ScavTrap(const std::string &name);
      ScavTrap(const ScavTrap &src);
      ScavTrap &operator=(const ScavTrap &rhs);
      ~ScavTrap();

      void attack(const std::string &target);
      void guardGate();

};

#endif