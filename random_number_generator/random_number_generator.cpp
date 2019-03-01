// file random_number_generator.cpp
// Wes Leiter
// Sandbox Project
// Creates a file containing a list of size "n" random numbers in the specified
// range.  File is labelled random_numbers.txt and is delimited by '/n'
//
// Citation: For help reading in an "int" from command-line arguments
// source: https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
//
// Citation: For help incrementing the filename if original already exists
// source: https://stackoverflow.com/questions/26697129/how-can-i-increment-a-number-in-a-string-form-in-c
//
// Citation: For help generating random numbers with negative range
// source: https://stackoverflow.com/questions/19825841/how-to-generate-negative-random-integer-in-c

#include <stdexcept>  // try, catch, invalid_argument
#include <iostream>   // cerr
#include <sstream>    // istringstream, ostringstream
#include <fstream>    // ofstream
#include <iomanip>    // setw(), setfill()
#include <string>     // string, stoi()
#include <random>     // uniform_int_distribution, random_device, mt19937
#include <locale>     // isdigit()
#include <error.h>    // perror()

double increment_filename()
{
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0')
}

int main(int argc, char* argv[])
{
  int listSize;
  int lowRange;
  int highRange;

  if (argc == 4)
  {
    bool errFlag = false;
    std::string arg1 = argv[1];
    try {
      std::size_t pos;
      listSize = std::stoi(arg1, &pos);
      if (pos < arg1.size()) {
        std::cerr << "Trailing characters after number: " << arg1 << '\n';
      }
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg1 << '\n';
      errFlag = true;
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg1 << '\n';
      errFlag = true;
    }

    std::string arg2 = argv[2];
    try {
      std::size_t pos;
      lowRange = std::stoi(arg2, &pos);
      if (pos < arg2.size()) {
        std::cerr << "Trailing characters after number: " << arg2 << '\n';
      }
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg2 << '\n';
      errFlag = true;
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg2 << '\n';
      errFlag = true;
    }

    std::string arg3 = argv[3];
    try {
      std::size_t pos;
      highRange = std::stoi(arg3, &pos);
      if (pos < arg3.size()) {
        std::cerr << "Trailing characters after number: " << arg3 << '\n';
      }
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg3 << '\n';
      errFlag = true;
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg3 << '\n';
      errFlag = true;
    }

    if (errFlag) {
      std::cerr << argv[0] << " : Exiting with input errors.\n";
      exit(1);
    }
  }
  else {
    std::cerr << "Usage: "<< argv[0]<< " <listSize> <lowRange> <highRange>\n";
    exit(1);
  }

  std::ofstream of ("random_numbers.txt");
  if (of.is_open())
  {
    /*
       std::locale loc;
       int listSize = 0;
       if (isdigit(argv[1],loc)) listSize = atol(argv[1]);
       else { perror("listSize"); exit(1); }

       int lowRange = 0;
       if (isdigit(argv[2],loc)) lowRange = atol(argv[2]);
       else { perror("lowRange"); exit(1); }

       int highRange = 0;
       if (isdigit(argv[3],loc)) highRange = atol(argv[3]);
       else { perror("highRange"); exit(1); }
       */

    std::random_device rd;
    std::mt19937 engine(rd());  /* generator engine with rd as seed */
    std::uniform_int_distribution<int> dist(lowRange,highRange);

    for (int n=0; n<listSize; ++n) {
      of << dist(engine) << '\n';
    }

    of.close();
  }
  else
  {
    perror("Opening random_numbers.txt");
    exit(1);
  }

  return 0;
}
