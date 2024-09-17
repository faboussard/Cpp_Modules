#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define DATABASE "Data/data.csv"
#define WRONG_ARGS_ERROR_MESSAGE "Error: Please enter an input file as argument"
#define BAD_OPENING_ERROR_MESSAGE "Error: FILE COULD NOT OPEN "

#define COMA_SEPARATOR ','
#define DASH_SEPARATOR '|'
#define DELIMITER_DATE '-'

class BitcoinExchange {

private:
	typedef std::map<std::string, float> map;

  bool extractFile(std::string &fileName, map &myMap);

  void open_file(const char *filename, std::ifstream &infile);

  bool parseLine(const std::string &line, std::string &key, float &value,
                 bool isInputFile);

	void processFile(std::ifstream &infile, map &myMap,
			std::string &fileName);

  float calculateRate(const std::string &date, float price);

	bool checkDate(std::string const &date);
	bool checkAmount(std::string const &amount);

  std::string _inputFile;
  std::string _databaseFile;
  map _databaseMap;
  map _inputMap;

public:
	typedef std::map<std::string, float> map;
  BitcoinExchange(const std::string &inputFile, const std::string &dataFile);
  BitcoinExchange(const BitcoinExchange &rhs);
  BitcoinExchange &operator=(const BitcoinExchange &rhs);
  ~BitcoinExchange();

  map &getDatabaseMap();
  map &getInputbaseMap();
  std::string &getInputFile();
  std::string &getDataFile();

  //	bool format_data();
  void findRate();
};

std::ostream &operator<<(std::ostream &stream,
                         BitcoinExchange &bitcoinExchange);

std::string getTodayDate();