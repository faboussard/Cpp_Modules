#include <ctime>
#include <iomanip>
#include <iostream>

#include "Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/* Constructor */
Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0),
      _nbWithdrawals(0) {
  _displayTimestamp();
  _totalAmount += initial_deposit;
  std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";created"
            << std::endl;
  _nbAccounts++;
}

/* Destructor */
Account::~Account() {
  _displayTimestamp();
  std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";closed"
            << std::endl;
  _nbAccounts--;
}

void Account::makeDeposit(int deposit) {
  _displayTimestamp();
  _nbDeposits++;
  _totalNbDeposits++;
  _amount += deposit;
  _totalAmount += deposit;
  std::cout << " index:" << _accountIndex << ";p_amount:" << _amount - deposit
            << ";deposit:" << deposit << ";amount:" << _amount
            << ";nb_deposits:" << _nbDeposits << std::endl;
}

int Account::checkAmount() const { return _amount; }

bool Account::makeWithdrawal(int withdrawal) {
  _displayTimestamp();
  if (withdrawal > _amount) {
    std::cout << " index:" << _accountIndex << ";p_amount:" << _amount
              << ";withdrawal:refused" << std::endl;
    return false;
  }
  _amount -= withdrawal;
  _totalAmount -= withdrawal;
  _nbWithdrawals++;
  _totalNbWithdrawals++;
  std::cout << " index:" << _accountIndex
            << ";p_amount:" << _amount + withdrawal
            << ";withdrawal:" << withdrawal << ";amount:" << _amount
            << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
  return true;
}

void Account::displayStatus() const {
  _displayTimestamp();
  std::cout << " index:" << _accountIndex << ";amount:" << _amount
            << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals
            << std::endl;
}

void Account::displayAccountsInfos() {
  _displayTimestamp();
  std::cout << " accounts:" << Account::getNbAccounts()
            << ";total:" << Account::getTotalAmount()
            << ";deposits:" << Account::getNbDeposits()
            << ";withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

void Account::_displayTimestamp() {
  std::time_t now = std::time(NULL);
  std::tm *timeInfo = std::localtime(&now);

  std::cout << "[" << (timeInfo->tm_year + 1900) << std::setw(2)
            << std::setfill('0') << (timeInfo->tm_mon + 1) << std::setw(2)
            << std::setfill('0') << timeInfo->tm_mday << "_" << std::setw(2)
            << std::setfill('0') << timeInfo->tm_hour << std::setw(2)
            << std::setfill('0') << timeInfo->tm_min << std::setw(2)
            << std::setfill('0') << timeInfo->tm_sec << "] ";
}

/* Static Methods */
int Account::getNbAccounts() { return _nbAccounts; }
int Account::getTotalAmount() { return _totalAmount; }
int Account::getNbDeposits() { return _totalNbDeposits; }
int Account::getNbWithdrawals() { return _totalNbWithdrawals; }
