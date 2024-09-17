#include "BitcoinExchange.hpp"
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdexcept>

/*============================================================================*/
/*       Constructor / destructor / Copy assignment operator                  */
/*============================================================================*/

BitcoinExchange::BitcoinExchange(const std::string &inputFile,
                                 const std::string &dataFile)
    : _inputFile(inputFile), _databaseFile(dataFile) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
    : _inputFile(rhs._inputFile), _databaseFile(rhs._databaseFile),
      _databaseMap(rhs._databaseMap), _inputMap(rhs._inputMap) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
  if (this != &rhs) {
    _inputFile = rhs._inputFile;
    _databaseFile = rhs._databaseFile;
    _databaseMap = rhs._databaseMap;
    _inputMap = rhs._inputMap;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/*============================================================================*/
/*       getter */
/*============================================================================*/

BitcoinExchange::map &BitcoinExchange::getDatabaseMap() { return _databaseMap; }

BitcoinExchange::map &BitcoinExchange::getInputbaseMap() {
  return _inputMap;
}

std::string &BitcoinExchange::getInputFile() { return _inputFile; }

std::string &BitcoinExchange::getDataFile() { return _databaseFile; }


/*============================================================================*/
/*       operator overload */
/*============================================================================*/

std::ostream &operator<<(std::ostream &stream, BitcoinExchange &bitcoinExchange) {
	BitcoinExchange::map &inputMap = bitcoinExchange.getInputbaseMap();

	stream << "\t\t\n Input map:\n";
	for (BitcoinExchange::map::iterator it = inputMap.begin(); it != inputMap.end(); ++it) {
		const std::string &date = it->first;
		const std::vector<float> &values = it->second;

		stream << "Key for input map: " << date << " => Values: ";
		for (std::vector<float>::const_iterator valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
			stream << *valueIt << " ";
		}
		stream << std::endl;
	}

	return stream;
}

/*============================================================================*/
/*      Public  member functions */
/*============================================================================*/

void BitcoinExchange::open_file(const char *filename, std::ifstream &infile) {
  infile.open(filename);
  if (!infile.is_open()) {
    std::cerr << BAD_OPENING_ERROR_MESSAGE << filename << std::endl;
    exit(EXIT_FAILURE);
  }
}

/*============================================================================*/
/*       Private member functions                                             */
/*============================================================================*/

bool BitcoinExchange::checkDate(std::string const &date) {
	if (date.empty()) {
		std::cerr << "Error: Bad input - empty date => " << date << std::endl;
		return false;
	}

	if (date > getTodayDate()) {
		std::cerr << "Error: Bad input - date is upper than today! Date: " << date
				  << std::endl;
		return false;
	}

	std::istringstream iss(date);
	int year, month, day;
	char delimiter;

	if (!(iss >> year >> delimiter >> month >> delimiter >> day)) {
		std::cerr << "Error: Bad input - invalid format for date. Date: " << date
				  << std::endl;
		return false;
	}

	if (delimiter != '-') {
		std::cerr << "Error: Bad input - invalid delimiter. Date: " << date
				  << std::endl;
		return false;
	}

	if (month < 1 || month > 12 || day < 1 || day > 31) {
		std::cerr << "Error: Bad input - invalid date values. Date: " << date
				  << std::endl;
		return false;
	}

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		std::cerr << "Error: Bad input - invalid day for the month. Date: " << date
				  << std::endl;
		return false;
	}

	if (month == 2) {
		bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > (leapYear ? 29 : 28)) {
			std::cerr << "Error: Bad input for February. Date: " << date << std::endl;
			return false;
		}
	}
	return true;
}


bool BitcoinExchange::checkAmount(std::string const &amount) {
  char *end;
  float num;
  errno = 0;

  double tmp = std::strtod(amount.c_str(), &end);
  if (amount.empty()) {
    std::cerr << "Error: Bad input - amount is empty. "
              << std::endl;
	  return (false);
  }
  if (errno == EINVAL) {
    std::cerr << "Error: Bad input - amount is not a valid number. Amount: "
              << amount << std::endl;
	  return (false);
  }
  num = static_cast<float>(tmp);
  if (num < 0.0) {
    std::cerr << "Error: Bad input - Not a positive number. Amount: " << amount
              << std::endl;
	  return (false);
  }
  if (num >= INT8_MAX) {
    std::cerr << "Error: Bad input - Amount exceeds maximum value. Amount: "
              << amount << std::endl;
	  return (false);
  }
	return (true);
}

bool BitcoinExchange::parseLine(const std::string &line, std::string &key,
								float &value, bool isInputFile) {
	std::istringstream iss(line);
	std::string valueStr;
	char separator = isInputFile ? DASH_SEPARATOR : COMA_SEPARATOR;

	if (!std::getline(iss, key, separator) || !std::getline(iss, valueStr)) {
		return false;
	}

	if (isInputFile) {
		if (!checkDate(key)) return false;
		if (!checkAmount(valueStr)) return false;
	}

	try {
		value = std::stof(valueStr);
	} catch (const std::invalid_argument &) {
		return false;
	}

	return true;
}


void BitcoinExchange::processFile(std::ifstream &infile, std::map<std::string, std::vector<float>> &myMap,
								  std::string &fileName) {
	std::string line;
	std::string key;
	float value;

	std::getline(infile, line); // ignore the header line
	while (std::getline(infile, line)) {
		if (parseLine(line, key, value, fileName == _inputFile)) {
			myMap[key].push_back(value);  // Ajoute chaque valeur dans le vecteur associé à la date
		} else {
			std::cerr << "Error: Skipping invalid line => " << line << std::endl << std::endl;
		}
	}
}


bool BitcoinExchange::extractFile(std::string &fileName, map &myMap) {
	try {
		std::ifstream data_infile;
		open_file(fileName.c_str(), data_infile);
		processFile(data_infile, myMap, fileName);
		data_infile.close();
		return true;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return false;
	}
}

float BitcoinExchange::calculateRate(const std::string &date, float price) {


	BitcoinExchange::map::iterator  mapIt = _databaseMap.lower_bound(date);

	// Si la date trouvée est exactement égale à celle donnée
	if (mapIt != _databaseMap.end() && mapIt->first == date) {
		return price * mapIt->second[0];  // On utilise directement ce taux
	}

	// Si `it` est au début de la map, cela signifie qu'il n'y a pas de date antérieure
	if (mapIt == _databaseMap.begin()) {
		std::cerr << "Error: No earlier date found in the database for " << date << std::endl;
		return -1;  // Indiquer qu'aucun taux valide n'a été trouvé
	}

	// Sinon, on recule d'un itérateur pour obtenir la date immédiatement inférieure
	--mapIt;  // On passe à la date précédente (qui est forcément < à `date`)

	// Maintenant, on retourne le taux de la date la plus proche inférieure
	return price * mapIt->second[0];
}


/*============================================================================*/
/*       Public member functions                                             */
/*============================================================================*/

void BitcoinExchange::findRate() {
	if (!extractFile(_inputFile, _inputMap) || !extractFile(_databaseFile, _databaseMap)) {
		std::cerr << "Error: could not extract input or data file." << std::endl;
		return;
	}

	for (BitcoinExchange::map::iterator mapIt = _inputMap.begin(); mapIt != _inputMap.end(); ++mapIt) {
		const std::string &date = mapIt->first;
		const std::vector<float> &values = mapIt->second;

		for (std::vector<float>::const_iterator valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
			float price = *valueIt;
			float rate = calculateRate(date, price);  // Passe la date et le prix à `calculateRate`

			if (rate != -1) {
				std::cout << date << " => " << price << " = " << rate << std::endl;
			} else {
				std::cerr << "Warning: No exchange rate found for date: " << date << std::endl;
			}
		}
	}
}


/*============================================================================*/
/*       Non member functions                                             */
/*============================================================================*/

std::string getTodayDate() {
  std::time_t now = std::time(0);
  std::tm *now_tm = std::localtime(&now);
  std::ostringstream oss;
  oss << (now_tm->tm_year + 1900) << "-" << (now_tm->tm_mon + 1) << "-"
      << now_tm->tm_mday;

  return oss.str();
}