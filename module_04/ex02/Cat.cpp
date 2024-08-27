#include "Cat.hpp"
#include "AAnimal.hpp"
#include "general.hpp"

/*============================================================================*/
/*       Constructors */
/*============================================================================*/

Cat::Cat() : AAnimal() {
  _type = "Cat";
  _brain = new Brain();
  std::cout << "Cat : ";
  DEFAULT_CONSTRUCTOR_MESSAGE;
}

Cat::Cat(const Cat &src) : AAnimal(src) {
  _type = src._type;
  _brain = new Brain(*src._brain);
  std::cout << "Cat : ";
  COPY_CONSTRUCTOR_MESSAGE;
}

Cat &Cat::operator=(const Cat &src) {
  if (this != &src) {
    _type = src._type;
    delete _brain;
    _brain = new Brain(*src._brain);
    std::cout << "Cat : ";
    COPY_ASSIGNMENT_MESSAGE;
  }

  return *this;
}

Cat::~Cat(void) {
  delete _brain;
  std::cout << "Cat : ";
  DESTRUCTOR_MESSAGE;
}

/*============================================================================*/
/*       member functions */
/*============================================================================*/

void Cat::makeSound(void) const { CAT_MESSAGE; }

Brain &Cat::getBrain() const { return (*_brain); }