#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include "Animal.hpp"

#define CAT_MESSAGE \
	std::cout << "Meow 🐱" << std::endl;

class Cat : public Animal
{
public:

	Cat();
	virtual ~Cat();
	Cat(const Cat &cpy);
	Cat &operator=(const Cat &src);

	void makeSound() const;
};

#endif
