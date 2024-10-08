#ifndef WRONGCAT_H
#define WRONGCAT_H

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
  public:
      WrongCat();
      WrongCat(const WrongCat &copy);
      WrongCat &operator=(const WrongCat &src);
      virtual ~WrongCat();

      void makeSound(void) const;
};

#endif
