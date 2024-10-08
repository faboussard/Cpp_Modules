#include "Base.hpp"
#include <cstdlib>

Base::~Base() {}

Base *generate(void) {
  srand(time(0));
  int random = rand() % 3;

  if (random == 0)
    return (new A());
  else if (random == 1)
    return (new B());
  else if (random == 2)
    return (new C());
  return NULL;
}

void identify(Base *p) {
  if (p == NULL)
    std::cout << "NULL pointer" << std::endl;
  else if (dynamic_cast<A *>(p))
    std::cout << "A pointer" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "B pointer" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "C pointer" << std::endl;
  else
    std::cout << "Unknow pointer" << std::endl;
}

void identify(Base &p) {
  try {
    A &a = dynamic_cast<A &>(p);
    std::cout << "A pointer" << std::endl;
    (void)a;
    return;
  } catch (const std::exception &e) {
  }

  try {
    B &b = dynamic_cast<B &>(p);
    std::cout << "B pointer" << std::endl;
    (void)b;
    return;
  } catch (const std::exception &e) {
  }
  try {
    C &c = dynamic_cast<C &>(p);
    std::cout << "C pointer" << std::endl;
    (void)c;
    return;
  } catch (const std::exception &e) {
  }

  std::cout << "unknown pointer" << std::endl;
}