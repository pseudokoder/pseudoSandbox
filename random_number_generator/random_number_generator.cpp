// file random_number_generator.cpp
// Wes Leiter
// Sandbox Project
// Creates a file containing a list of size "n" random numbers in the specified
// range.  File is labelled random_numbers.txt and is delimited by '/n'
//
// Citation: Many thanks to www.cplusplus.com for examples and references
// source: (various pages) http://www.cplusplus.com/
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
#include <string>     // string, stoi()
#include <random>     // uniform_int_distribution, random_device, mt19937
#include <error.h>    // perror()


int main(int argc, char* argv[])
{
  int listSize;
  int lowRange;
  int highRange;

  if (argc == 4)
  {
    bool errFlag = false;

    /* Validate Argument-1 */
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

    /* Validate Argument-2 */
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

    /* Validate Argument-3 */
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

  /* Generate Unique Filename */
  std::string fname = "uni_rnums_";
  std::string fileExt = ".txt";
  std::ostringstream oss;
  oss << lowRange << '_' << highRange << '_' << listSize;
  std::string filename(fname + oss.str());
  filename += fileExt;

  /* Construct File-Stream Object */
  std::ofstream ofs(filename);
  if (!ofs) {
    ofs.close();
    std::cerr<< "Error: Opening output file.\n";
    exit(1);
  }
  else
  {
    /* Generate Random Numbers */
    std::random_device rd;
    std::mt19937 engine(rd());  /* generator engine with rd as seed */
    std::uniform_int_distribution<int> dist(lowRange,highRange);

    for (int n=0; n<listSize; ++n) {
      ofs << dist(engine) << '\n';
    }

    ofs.close();
  }

  return 0;
}
