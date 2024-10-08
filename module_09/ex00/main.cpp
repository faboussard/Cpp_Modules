#include "BitcoinExchange.hpp"
#include <cstdlib>

void check_args(int argc) {
  if (argc != 2) {
    std::cerr << WRONG_ARGS_ERROR_MESSAGE << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv) {
  check_args(argc);

  std::string inputFile = std::string("Data/") + std::string(argv[1]);
  std::string dataFile(DATABASE);

  BitcoinExchange exchange(inputFile, dataFile);


  try {
    exchange.findRate();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
