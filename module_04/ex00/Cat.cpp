#include "Cat.hpp"
#include "Animal.hpp"
#include "utils.hpp"

/*============================================================================*/
/*       Constructors */
/*============================================================================*/

Cat::Cat() : Animal() {
  std::cout << "Cat : ";
  _type = "Cat";
  DEFAULT_CONSTRUCTOR_MESSAGE;
}

Cat::Cat(const Cat &src) : Animal(src) {
  std::cout << "Cat : ";
  *this = src;
  COPY_CONSTRUCTOR_MESSAGE;
}

Cat &Cat::operator=(const Cat &src) {
  if (this != &src) {
    std::cout << "Cat : ";
    COPY_ASSIGNMENT_MESSAGE;
    _type = src._type;
  }
  return *this;
}

Cat::~Cat(void) {
  std::cout << "Cat : ";
  DESTRUCTOR_MESSAGE;
}

/*============================================================================*/
/*       member functions */
/*============================================================================*/

void Cat::makeSound(void) const { CAT_MESSAGE; }