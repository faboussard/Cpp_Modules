#include "Bureaucrat.hpp"

/*============================================================================*/
/*       Constructors */
/*============================================================================*/

Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : _name(name), _grade(grade) {
  if (grade < HIGHEST_GRADE)
    throw GradeTooHighException();
  if (grade > LOWEST_GRADE)
    throw GradeTooLowException();
  CONSTRUCTOR_MESSAGE;
}

Bureaucrat::~Bureaucrat() { DESTRUCTOR_MESSAGE; }

Bureaucrat::Bureaucrat(const Bureaucrat &src)
    : _name(src._name), _grade(src._grade) {
  COPY_CONSTRUCTOR_MESSAGE;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src) {
  COPY_ASSIGNMENT_MESSAGE;
  if (this != &src) {
    _grade = src._grade;
  }
  return *this;
}

/*============================================================================*/
/*       Accesors                                                             */
/*============================================================================*/

const std::string &Bureaucrat::getName() const { return _name; }

int Bureaucrat::getGrade() const { return _grade; }

/*============================================================================*/
/*       Exceptions */
/*============================================================================*/

const char *Bureaucrat::GradeTooHighException::what() const throw() {
  return "TooHighException";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
  return "TooLowException";
}

/*============================================================================*/
/*       member functions */
/*============================================================================*/

void Bureaucrat::incrementGrade() {

  if (_grade > HIGHEST_GRADE) {
    _grade -= 1;
    std::cout << "increment of one for" << this->getName() << " grade is now "
              << _grade << std::endl;

  } else
    throw GradeTooHighException();
}

void Bureaucrat::decrementGrade() {

  if (_grade < LOWEST_GRADE) {
    _grade += 1;
    std::cout << "decrement of one for" << this->getName() << " grade is now "
              << _grade << std::endl;
  } else
    throw GradeTooLowException();
}

void Bureaucrat::signForm(Form &form) const {
  try {
    form.beSigned(*this);
    std::cout << _name << " signed " << form.getName() << std::endl;
  } catch (std::exception &e) {
    std::cout << _name << " could not sign " << form.getName() << " because "
              << e.what() << std::endl;
  }
}

/*============================================================================*/
/*  			     Class overload */
/*============================================================================*/

std::ostream &operator<<(std::ostream &stream, Bureaucrat const &bureaucrat) {
  stream << bureaucrat.getName() << " , grade : " << bureaucrat.getGrade();
  return stream;
}